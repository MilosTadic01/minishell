/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:27:30 by dzubkova          #+#    #+#             */
/*   Updated: 2023/11/23 14:37:14 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size);

/*int	main(void)
{
	char src[] = "coucou";
	char dst[10];
	char dst1[10];
	memset(dst, 'A', 10);
	memset(dst1, 'A', 10);
	size_t res = ft_strlcpy(dst, src, 0);
	size_t res1 = strlcpy(dst1, src, 0);
	printf("%s\n", dst1);
	printf("%s\n", dst);
	printf("%lu\n", res1);
	printf("%lu\n", res);
	return (0);
}*/

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	idx;
	size_t			res;

	idx = 0;
	res = ft_strlen(src);
	while (*src != '\0' && idx < (size - 1) && size != 0)
	{
		*dst++ = *src++;
		idx++;
	}
	if (size)
		*dst = '\0';
	return (res);
}
