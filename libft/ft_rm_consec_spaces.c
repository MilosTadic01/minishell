/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_consec_spaces.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:33:55 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/12 13:07:08 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_rm_consec_spaces(char	*src)
{
	char	*res;
	int		flag;
	char	*copy;

	res = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!res)
		return (NULL);
	copy = res;
	flag = 1;
	while (*src)
	{
		if (!ft_isspace(*src))
		{
			*res++ = *src;
			flag = 0;
		}
		else if ((ft_isspace(*src) && !flag))
		{
			*res++ = *src;
			flag = 1;
		}
		src++;
	}
	*res = '\0';
	return (ft_strtrim(copy, " "));
}
