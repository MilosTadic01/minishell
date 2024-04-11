/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:59:34 by dzubkova          #+#    #+#             */
/*   Updated: 2023/12/01 12:47:39 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c);

/*int	main(void)
{
	char s[] = "tripouille";
	printf("%s\n", ft_strchr(s, 't' + 256));
	printf("%s\n", strrchr(s, 't' + 256));
	printf("%d\n", ft_strchr(s, 't' + 256) == s);
	return (0);
}*/

char	*ft_strrchr(const char *s, int c)
{
	char	*res;

	res = NULL;
	while (*s)
	{
		if (*s == (unsigned char)c)
		{
			res = (char *)s;
		}
		s++;
	}
	if (*s == (unsigned char)c)
		res = (char *)s;
	return (res);
}
