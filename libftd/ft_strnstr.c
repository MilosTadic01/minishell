/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:29:38 by dzubkova          #+#    #+#             */
/*   Updated: 2023/11/29 15:54:50 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len);

/*int	main(void)
{
	char haystack[30] = "aaabcabcd";
	//char needle[10] = "aabc";
	//char * empty = (char*)"";
	printf("%s\n", ft_strnstr(haystack, "abcd", 9));
}*/

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t				len_little;
	int					res;
	char				*temp_b;
	unsigned int		pos;

	len_little = ft_strlen(little);
	pos = 0;
	if (!len_little)
		return ((char *)big);
	while (*big && pos <= len)
	{
		if (*big == *little)
		{
			temp_b = (char *)big;
			if (pos + len_little <= len)
			{
				res = ft_strncmp(temp_b, little, len_little);
				if (!res)
					return ((char *)big);
			}
		}
		big++;
		pos++;
	}
	return (NULL);
}
