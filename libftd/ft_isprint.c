/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:29:09 by dzubkova          #+#    #+#             */
/*   Updated: 2023/11/17 13:19:56 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c);

/*int	main(void)
{
	printf("%d\n", ft_isprint('\n'));
	return (0);
}*/

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
