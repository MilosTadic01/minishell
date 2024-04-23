/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:42:20 by dzubkova          #+#    #+#             */
/*   Updated: 2023/12/01 12:47:25 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dst, const char *src, size_t size);
static size_t	min(size_t a, size_t b);

/*int	main(void)
{

 	//size_t res1 = ft_strlcat("pqrstuvwxyz", "abcd", 20);
 	size_t res2 = ft_strlcat("pqrstuvwxyz", "abcd", 20);

	printf("%lu\n", res2);

	return (0);
}*/

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t					res;
	size_t					dest_len;
	size_t					src_len;
	unsigned long int		space;

	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	space = (unsigned long int)size - dest_len;
	res = src_len + dest_len;
	if (size < dest_len)
		return (min(res, size + src_len));
	dst += dest_len;
	while (*src && space > 1)
	{
		*dst++ = *src++;
		space--;
	}
	*dst = '\0';
	res = src_len + dest_len;
	return (res);
}

static size_t	min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	else
		return (b);
}
