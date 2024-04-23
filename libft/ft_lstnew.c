/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:13:47 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/22 17:07:35 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(t_type *data, int type)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	if (type == AS_TOKEN)
	{
		new_node->as_token = malloc(sizeof(t_token));
		if (!new_node->as_token)
			return (NULL);
		new_node->as_token->token_type = data->as_token->token_type;
		new_node->as_token->value = ft_strdup(data->as_token->value);
	}
	else if (type == AS_ITEM)
	{
		new_node->as_item = malloc(sizeof(t_redir_item));
		if (!new_node->as_token)
			return (NULL);
		ft_memcpy(&(new_node->as_item), data, sizeof(t_type));
	}
	else if (type == AS_STR)
		new_node->as_str = ft_strdup((char *)data);
	return (new_node);
}
