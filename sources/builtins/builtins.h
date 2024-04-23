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
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# include <stdlib.h>
# include "../../libft/libft.h"

typedef struct s_data
{
    char    **env;
}       t_data;

char	*ft_pwd(void);
void	ft_cd(char *dest);
void	ft_echo(char **strarr);

void    env_init(char *line, char **envp);
void    extract_entire_env(t_data *data, char **envp);
void    ft_env(t_list *env);
char    *ft_getenv(t_list *env, char *key);
void    ft_printenv(t_list *env, char **varkeys);
void    ft_export(t_data *data, char **kv_pairs);

#endif
