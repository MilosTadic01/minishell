/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:13:47 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/25 11:50:24 by dzubkova         ###   ########.fr       */
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
		new_node->as_token = data->as_token;
	else if (type == AS_ITEM)
		new_node->as_item = data->as_item;
	else if (type == AS_STR)
	{
		printf("%s\n", data->as_str);
		new_node->as_str = ft_strdup(data->as_str);
	}
	return (new_node);
}
