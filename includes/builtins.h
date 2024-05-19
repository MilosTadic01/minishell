/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:05:37 by mitadic           #+#    #+#             */
/*   Updated: 2024/05/03 13:26:45 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

// pwd.c
int		ft_pwd(void);
char	*ft_getcwd(void);

// cd.c
int		ft_cd(int size, char **cmdarr, t_list **env);

// echo.c
int		ft_echo(int size, char **cmdarr);

// init_env.c
t_list	*init_env(char **envp);

// unset.c
int		unset_cmdarr(int size, char **cmdarr, t_list **env);
void	ft_unset(char *key, t_list **env);

// export.c
int		export_cmdarr(int size, char **cmdarr, t_list **env);
int		ft_export(char *kv_str, t_list **env);

// printnget_env.c
int		ft_printenv(t_list *env);
char	*ft_getenv(char *key, t_list *env);

// exit.c
int		ft_exit(int size, char **cmdarr);

#endif