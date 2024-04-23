/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:21:45 by dzubkova          #+#    #+#             */
/*   Updated: 2023/11/23 14:36:00 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n);

/*int	main(void)
{
	char s1[] = {-128, 0, 127, 0};
	//char s1c[] = {-128, 0, 127, 0};
	char s2[] = {0, 0, 127, 0};
	//char s3[] = {0, 0, 42, 0};
	printf("%d\n", ft_memcmp(s1, s2, 1));
	printf("%d\n", memcmp(s1, s2, 1));
	return (0);
}*/

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*chs1;
	char	*chs2;

	chs1 = (char *)s1;
	chs2 = (char *)s2;
	while (n--)
	{
		if ((unsigned char)*chs1 > (unsigned char)*chs2)
			return (1);
		else if ((unsigned char)*chs1 < (unsigned char)*chs2)
			return (-1);
		chs1++;
		chs2++;
	}
	return (0);
}
