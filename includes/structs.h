/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:10:44 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/12 14:08:00 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_token
{
	char	*value;
	int		token_type;
}	t_token;

typedef struct s_redir_item
{
	int				type;
	char			*filename;
}	t_redir_item;

typedef union u_type
{
	t_token			*as_token;
	t_redir_item	*as_item;
	char			*as_str;
}	t_type;

enum e_data_types
{
	AS_TOKEN,
	AS_ITEM,
	AS_STR
}	;

typedef struct s_list
{
	enum e_data_types	type;
	struct s_list		*next;
	union
	{
		t_token			*as_token;
		t_redir_item	*as_item;
		char			*as_str;
	}	;
}	t_list;

#endif