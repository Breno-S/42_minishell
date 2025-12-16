/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:42:00 by brensant          #+#    #+#             */
/*   Updated: 2025/12/16 16:10:45 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "libft.h"
# include "types.h"

void	expand_token(t_token_word *t);
void	expand_token_list(t_token *token_list);
char	*expanded_token_text(t_token_word *t);

#endif
