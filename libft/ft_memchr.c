/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:09:06 by dzubkova          #+#    #+#             */
/*   Updated: 2023/11/23 14:35:53 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n);

/*int	main(void)
{
	char s[] = {0, 1, 2, 3 ,4 , 5};

	printf("%d\n", ft_memchr(s, 258, 3) == s + 2);
	printf("%d\n", memchr(s, 258, 3) == s + 2);
	//printf("%c\n", *(s + 6));
	return (0);
}*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*chs;

	if (n <= 0)
		return (NULL);
	chs = (char *)s;
	while (n--)
	{
		if ((unsigned char)*chs == (unsigned char)c)
			return (chs);
		chs++;
	}
	if (!chs)
		return (chs);
	return (NULL);
}
