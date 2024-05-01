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

char	*ft_pwd(void);
void	ft_cd(t_list *env, char *dest);
void	ft_echo(char **strarr);

t_list  *init_env(char **envp);

void    ft_unset(t_list **env, char *str);

void    ft_export(t_list **env, char *kv_str);

void    ft_printenv(t_list *env);
char    *ft_getenv(t_list *env, char *key);

char    **ft_prepenv(t_list *env);

#endif