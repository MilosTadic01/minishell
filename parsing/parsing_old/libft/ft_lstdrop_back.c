/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdrop_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:44:51 by dzubkova          #+#    #+#             */
/*   Updated: 2024/02/15 12:15:38 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdrop_back(t_list **lst)
{
	t_list	*prev;
	t_list	*current;

	if (!lst || !(*lst))
		return ;
	current = *lst;
	prev = NULL;
	while (current->next)
	{
		prev = current;
		current = current->next;
	}
	if (prev)
	{
		free(current);
		prev->next = NULL;
	}
	else
	{
		free(*lst);
		*lst = NULL;
	}
}
