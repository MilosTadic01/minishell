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
# include "../../includes/minishell.h"

typedef struct  s_lst
{
    struct s_lst   *next;
    void    *content;
}               t_lst;


char	*ft_pwd(void);
void	ft_cd(char *dest);
void	ft_echo(char **strarr);

t_list  *init_env(char **envp);
void    extract_entire_env(t_data *data, char **envp);
void    ft_env(t_list *env);
char    *ft_getenv(t_list *env, char *key);
void    ft_printenv(t_list *env, char **varkeys);
void    ft_export(t_data *data, char **kv_pairs);

#endif
