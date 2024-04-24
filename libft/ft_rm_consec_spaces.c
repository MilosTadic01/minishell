/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_consec_spaces.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:33:55 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/24 17:33:23 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_rm_consec_spaces(char *src)
{
	char	*tmp;
	char	*res;
	char	*copy;

	res = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!res)
		return (NULL);
	copy = res;
	while (*src)
	{
		if (!ft_isspace(*src) || (res != copy && !ft_isspace(*(res - 1))))
			*res++ = *src;
		src++;
	}
	*res = '\0';
	tmp = ft_strtrim(copy, " ");
	free(copy);
	return (tmp);
}
