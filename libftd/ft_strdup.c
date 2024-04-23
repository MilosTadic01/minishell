/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:30:20 by dzubkova          #+#    #+#             */
/*   Updated: 2023/11/23 14:36:44 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s);

/*int	main(void)
{
	char *s = "mess it up";
	printf("%s\n", ft_strdup(s));
	return (0);
}*/

char	*ft_strdup(const char *s)
{
	char	*copy;
	int		len;

	len = ft_strlen(s);
	copy = malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (copy);
	while (*s)
		*copy++ = *s++;
	*copy = '\0';
	return (copy - len);
}
