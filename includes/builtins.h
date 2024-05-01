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
# include "minishell.h"

// pwd.c
void    ft_pwd(void);
char	*ft_getcwd(void);

// cd.c
void	ft_cd(t_list *env, char *dest);

// echo.c
void	ft_echo(char **strarr);

// init_env.c
t_list  *init_env(char **envp);

// unset.c
void    ft_unset(t_list **env, char *str);

// export.c
void    ft_export(t_list **env, char *kv_str);


// printnget_env.c
void    ft_printenv(t_list *env);
char    *ft_getenv(t_list *env, char *key);

// convert_env4execve.c
char    **convert_env(t_list *env);

// exit.c
void    ft_exit(char **strarr);

#endif