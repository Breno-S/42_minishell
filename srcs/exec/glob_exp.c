/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:16:04 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/01/17 10:21:22 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

char	*glob_exp(t_token *token_o)
{
	int				type;
	t_list			*files;
	t_token_word	*token;
	t_segment		*aux;
	char			*rtn;

	token = (t_token_word *)token_o;
	if (!token || token_o->class != 2)
		return (NULL);
	aux = token->seg_lst;
	while (aux)
	{
		if (aux->type == WILDCARD)
			break ;
		aux = aux->next;
	}
	if (!aux)
		return (NULL);
	type = (ft_strncmp(token->seg_lst->text, ".", 1) != 0);
	files = all_files(type, token->seg_lst);
	if (!files)
		return (NULL);
	ft_lstsort(files);
	rtn = ft_gcfct_register_root(ft_joinlst(files), "temp");
	return (rtn);
}

int	match_pattern(t_segment *seg_lst, char *content, t_segment *head_seg)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (seg_lst->type == LITERAL)
		{
			if (check_literal_match(seg_lst, content, i))
			{
				i += ft_strlen(seg_lst->text);
				seg_lst = seg_lst->next;
			}
			else if (!seg_lst->next || seg_lst == head_seg)
				return (1);
			else
				i++;
		}
		if (seg_lst && (seg_lst->type != LITERAL))
			seg_lst = seg_lst->next;
		if (!seg_lst)
			return (0);
	}
	return (1);
}

int	check_literal_match(t_segment *aux_seg, char *content, unsigned long i)
{
	int	len_s1;
	int	len_s2;

	if (aux_seg->type == LITERAL)
	{
		len_s1 = ft_strlen(content);
		len_s2 = ft_strlen(aux_seg->text);
		if (!aux_seg->next && (len_s1 - len_s2) >= (int)i)
			i = len_s1 - len_s2;
		if ((long)i >= 0 && !ft_strncmp(&content[i], aux_seg->text, len_s2))
			return (1);
	}
	return (0);
}

t_list	*all_files(int type, t_segment *seg_lst)
{
	DIR				*o_dir;
	t_list			*files;
	struct dirent	*ent;
	int				i;

	files = NULL;
	i = 0;
	o_dir = opendir(".");
	if (!o_dir)
		return (NULL);
	while (1)
	{
		ent = readdir(o_dir);
		if (!ent)
			break ;
		if (!ft_strcmp(ent->d_name, ".") || !ft_strcmp(ent->d_name, ".."))
			i++;
		else if (i++ && save_files(ent, type, &files, seg_lst))
		{
			closedir(o_dir);
			return (NULL);
		}
	}
	closedir(o_dir);
	return (files);
}

int	save_files(struct dirent *ent, int type, t_list **head, t_segment *seg_lst)
{
	t_list	*files;
	char	*file;
	int		cmp;

	cmp = (ft_strncmp(ent->d_name, ".", 1) != 0);
	if (cmp != type)
		return (0);
	if (!match_pattern(seg_lst, ent->d_name, seg_lst))
	{
		file = ft_gcfct_register(ft_strdup(ent->d_name), GC_DATA)->content;
		if (!file)
			return (1);
		files = ft_gcfct_register(ft_lstnew(file), GC_DATA)->content;
		if (!files)
			return (1);
		ft_lstadd_back(head, files);
	}
	return (0);
}
