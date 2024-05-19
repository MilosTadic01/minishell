/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:01:34 by mitadic           #+#    #+#             */
/*   Updated: 2024/05/18 17:43:51 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// if *prev then bypass nodecopy, else head->next becomes head.
// then free the nodecopy.
static void	deloneenv(t_list **last, t_list *current, t_list *headcopy)
{
	if (!last || !(*last) || !current)
		return ;
	if (*last != current)
	{
		(*last)->next = current->next;
		*last = headcopy;
	}
	else
		*last = current->next;
	free(current->as_str);
	ft_lstdelone(current);
	return ;
}

void	ft_unset(char *key, t_list **env)
{
	int		len;
	t_list	*headcopy;
	t_list	*current;

	if (!key || !env || !(*env))
		return ;
	len = ft_strlen(key);
	headcopy = *env;
	current = *env;
	while (current)
	{
		if (strncmp(current->as_str, key, len) == 0 && \
			current->as_str[len] == '=')
		{
			deloneenv(env, current, headcopy);
			return ;
		}
		*env = current;
		current = current->next;
	}
	*env = headcopy;
}

// cmdarr[0] == "unset"
int	unset_cmdarr(int size, char **cmdarr, t_list **env)
{
	int	i;

	if (!cmdarr || !(*cmdarr) || !env || !(*env))
		return (1);
	i = 0;
	while (++i < size)
	{
		ft_unset(cmdarr[i], env);
	}
	return (SUCCESS);
}
