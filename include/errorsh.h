/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorsh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brensant <brensant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:14:55 by brensant          #+#    #+#             */
/*   Updated: 2026/01/07 15:42:12 by brensant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORSH_H
# define ERRORSH_H

# include "types.h"

# define STATUS_SUCCESS 0
# define STATUS_ERROR 1
# define STATUS_ERROR_SYNTAX 2
# define STATUS_ERROR_PERMISSION 126
# define STATUS_ERROR_CMD_NOT_FOUND 127

int	log_error(char *error_src, t_error_type error_type);

#endif /* ERRORSH_H */
