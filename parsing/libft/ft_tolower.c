/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:49:09 by dzubkova          #+#    #+#             */
/*   Updated: 2023/11/17 13:24:09 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c);

/*int	main(void)
{
	printf("%c\n", ft_tolower('a'));
	return (0);
}*/

int	ft_tolower(int c)
{
	int	delta;

	delta = 'a' - 'A';
	if (c >= 'A' && c <= 'Z')
		return (c + delta);
	return (c);
}
