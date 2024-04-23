/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:37:16 by dzubkova          #+#    #+#             */
/*   Updated: 2023/11/17 13:24:13 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c);

/*int	main(void)
{
	printf("%c\n", ft_toupper('3'));
	return (0);
}*/

int	ft_toupper(int c)
{
	int	delta;

	delta = 'a' - 'A';
	if (c >= 'a' && c <= 'z')
		return (c - delta);
	return (c);
}
