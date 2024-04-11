/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:37:57 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/08 12:22:53 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char **ft_strappend(char **str_arr, char *str, int size)
{
	char	**new_str_arr;
	int		idx;

	new_str_arr = malloc(sizeof(char *) * (size + 1));
	if (!new_str_arr)
		return (NULL);
	idx = 0;
	while (idx < size)
	{
		new_str_arr[idx] = malloc(sizeof(char) * (ft_strlen(str_arr[idx]) + 1));
		if (!new_str_arr[idx])
			return (NULL);
		ft_strlcpy(new_str_arr[idx], str_arr[idx], ft_strlen(str_arr[idx]) + 1);
		idx++;
	}
	new_str_arr[idx] = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!new_str_arr[idx])
			return (NULL);
	ft_strlcpy(new_str_arr[idx], str, ft_strlen(str) + 1);
	return (new_str_arr);
}
