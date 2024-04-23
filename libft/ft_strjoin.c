/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:05:07 by dzubkova          #+#    #+#             */
/*   Updated: 2023/11/17 13:23:07 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2);

/*int	main(void)
{
	printf("%s\n", ft_strjoin("string", "join"));
	return (0);
}*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	int		total_len;
	char	*res;

	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_str = malloc(sizeof(char) * total_len);
	res = new_str;
	if (!new_str)
		return (new_str);
	while (*s1)
	{
		*new_str = *s1;
		new_str++;
		s1++;
	}
	while (*s2)
	{
		*new_str = *s2;
		new_str++;
		s2++;
	}
	*new_str = '\0';
	return (res);
}
