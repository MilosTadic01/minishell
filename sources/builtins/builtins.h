/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:05:37 by mitadic           #+#    #+#             */
/*   Updated: 2024/04/19 16:57:47 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <errno.h>
# include <string.h>
# include <limits.h>
# include "../../parsing/libft/libft.h"

char	*ft_pwd(void);
void	ft_cd(char *dest);
void	ft_echo(char **strarr);
void	ft_export(void);

#endif
