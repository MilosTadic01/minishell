/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:27:53 by dzubkova          #+#    #+#             */
/*   Updated: 2023/11/17 13:22:59 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*));

/*int	main(void)
{
	char s[] = "123";
	ft_striteri(s, func);
	printf("%s\n", s);
	return (0);
}*/

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	idx;
	unsigned int	len;

	idx = 0;
	len = ft_strlen(s);
	while (idx < len)
	{
		(f)(idx, &s[idx]);
		idx++;
	}
}
