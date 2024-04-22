/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:13:47 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/22 14:23:50 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*int	main(void)
{
	t_token *token = malloc(sizeof(t_token));
	token->value = "echo";
	token->token_type = 201;
	t_token *new_token = malloc(sizeof(t_token));
	new_token->value = ">>";
	new_token->token_type = APPEND_OUT;
	t_redir_item *item = malloc(sizeof(t_redir_item));
	item->filename = "outfile";
	item->type = OUT_FILE;
	t_list *new = NULL;
	ft_lstadd_back(&new, ft_lstnew(&(t_type){.as_token = token}, AS_TOKEN));
	ft_lstadd_back(&new, ft_lstnew(&(t_type){.as_token = new_token}, AS_TOKEN));
	ft_lstadd_back(&new, ft_lstnew(&(t_type){.as_item = item}, AS_ITEM));
	printf("%s\n", new->as_token->value);
	printf("%d\n", new->as_token->token_type);
	printf("%s\n", new->next->as_token->value);
	printf("%d\n", new->next->as_token->token_type);
	printf("%s\n", new->next->next->as_item->filename);
	free(token);
	free(new);
	return (0);
}*/

t_list	*ft_lstnew(t_type *data, int type)
{
	t_list	*new_node;

	if (type < AS_TOKEN || type > AS_STR)
		return (NULL);
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
