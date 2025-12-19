/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_glob.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:05:19 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/19 09:51:33 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execsh.h"

t_list	*taken_files(t_list *lst, t_segment *seg_lst);

char	*glob_exp_new(t_token_word *token)
{
	int		type;
	t_list	*files;
	t_list	*files_t;
	char	*rtn;

	if (!token)
		return (NULL);
	type = (ft_strncmp(token->seg_lst->text, ".",1) != 0);
	files = all_files(type);
	if (!files)
		return (NULL);
	files_t = taken_files(files, token->seg_lst);
	if (!files_t)
		return (NULL);
	rtn = ft_joinlst(files_t);
	printf("\n%s\n", rtn);
	return (rtn);
}

t_list	*taken_files(t_list *lst, t_segment *seg_lst)
{
	t_list	*head;
	t_list	*aux;

	if (!lst)
		return (NULL);
	head = NULL;
	while (lst)
	{
		if (!aux_taken_files(seg_lst, lst->content))
		{
			aux = lst;
			lst = lst->next;
			aux->next = NULL;
			ft_lstadd_back(&head, aux);
		}
		else
			lst = lst->next;
	}
	return (head);
}

int	aux_taken_files(t_segment *seg_lst, char *content)
{
	t_segment	*aux_seg;
	int			jump;
	int			i;

	i = 0;
	aux_seg = seg_lst;
	while (content[i])
	{
		jump = 0;
		if (aux_seg->type == LITERAL)
		{
			jump = aux_aux_taken_files(aux_seg, content, i);
			if (jump)
				i += ft_strlen(aux_seg->text);
			else if (!aux_seg->next || aux_seg == seg_lst)
				return (1);
		}
		if (!jump && aux_seg->type == LITERAL)
			i++;
		else
			aux_seg = aux_seg->next;
		if (!aux_seg)
			return (0);
	}
	return (1);
}

int	aux_aux_taken_files(t_segment *aux_seg, char *content, int i)
{
	if (aux_seg->type == LITERAL)
	{
		if (!aux_seg->next && (ft_strlen(content)
				- ft_strlen(aux_seg->text)) >= i)
			i = ft_strlen(content) - ft_strlen(aux_seg->text);
		if (i >= 0 && !ft_strncmp(&content[i], aux_seg->text,
				ft_strlen(aux_seg->text)))
			return (1);
	}
	return (0);
}

// t_list	*taken_files(t_list *lst, t_segment *seg_lst)
// {
// 	t_segment	*aux_seg;
// 	int			i;
// 	int			jump;

// 	if (!lst)
// 		return (1);
// 	while (lst)
// 	{
// 		aux_seg = seg_lst;
// 		i = 0;
// 		while (((char *)lst->content)[i])
// 		{
// 			jump = 0;
// 			if (aux_seg->type == LITERAL)
// 			{
// 				if (!aux_seg->next && (ft_strlen(lst->content)
// 						- ft_strlen(aux_seg->text)) >= i)
// 					i = ft_strlen(lst->content) - ft_strlen(aux_seg->text);
// 				if (i >= 0 && !ft_strncmp(&lst->content[i], aux_seg->text,
// 						ft_strlen(aux_seg->text)))
// 				{
// 					jump = 1;
// 					i += ft_strlen(aux_seg->text);
// 				}
// 				else if (!aux_seg->next || aux_seg == seg_lst)
// 					break ;
// 			}
// 			if (!jump && aux_seg->type == LITERAL)
// 				i++;
// 			else
// 			{
// 				aux_seg = aux_seg->next;
// 				if (aux_seg && aux_seg->type != LITERAL)
// 					aux_seg = aux_seg->next;
// 			}
// 			if (!aux_seg)
// 			{
// 				printf("\n%s\n", lst->content);
// 				break ;
// 			}
// 		}
// 		lst = lst->next;
// 	}
// 	return (lst);
// }

// int	verify_glob(t_segment *aux_seg, char *proc, int index, int next)
// {
// 	int	jump;

// 	if (aux_seg->type == LITERAL)
// 	{
// 		if (next == 0 && (ft_strlen(proc) - ft_strlen(aux_seg->text)) >= index)
// 			index = ft_strlen(proc) - ft_strlen(aux_seg->text);
// 		if (index >= 0 && !ft_strncmp(&proc[index], aux_seg->text,
// 				ft_strlen(aux_seg->text)))
// 			return (0);
// 		else if (next == 0)
// 			return (1);
// 	}
// }

t_list	*all_files(int type)
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
		if (i++ > 1 && save_files(ent, type, &files))
		{
			closedir(o_dir);
			return (NULL);
		}
	}
	closedir(o_dir);
	return (files);
}

int	save_files(struct dirent *ent, int type, t_list **head)
{
	t_list	*files;
	char	*file;
	int		cmp;

	cmp = (ft_strncmp(ent->d_name, ".", 1) != 0);
	if (cmp != type)
		return (0);
	file = ft_gcfct_register(ft_strdup(ent->d_name), GC_DATA)->content;
	if (!file)
		return (1);
	files = ft_gcfct_register(ft_lstnew(file), GC_DATA)->content;
	if (!files)
		return (1);
	ft_lstadd_back(head, files);
	return (0);
}
