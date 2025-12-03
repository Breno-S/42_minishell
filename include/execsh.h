/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execsh.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:10:33 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/12/02 23:51:42 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECSH_H
# define EXECSH_H

# include "libft.h"
# include "types.h"
# include <readline/history.h>
# include <readline/readline.h>

int		ft_main_loop(t_msh *msh);
char	**ft_trim_env(char *envp, char sep);
int	ft_export(const char *var);
int export_env(char **arr);
int ft_env(int fd);
int	ft_unset(const char *var);

#endif // EXECSH_H
