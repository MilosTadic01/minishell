/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:53:26 by daria             #+#    #+#             */
/*   Updated: 2024/04/22 17:09:07 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_concat(char *str1, char *str2)
{
	char	*res;
	char	*copy;
	size_t	space;

	space = ft_strlen(str1) + ft_strlen(str2) + 1;
	res = malloc(space);
	if (!res)
		return (NULL);
	copy = res;
	while (str1 && *str1)
		*res++ = *str1++;
	while (str2 && *str2)
		*res++ = *str2++;
	*res = '\0';
	return (copy);
}
