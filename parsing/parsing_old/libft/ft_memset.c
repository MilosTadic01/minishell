/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:52:10 by dzubkova          #+#    #+#             */
/*   Updated: 2023/11/17 13:21:20 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	*ft_memset(void *s, int c, size_t n);

// int	main(void)
// {
// 	return (0);
// }

void	*ft_memset(void *s, int c, size_t n)
{
	void	*res;

	res = s;
	while (n)
	{
		*((char *)s) = c;
		s++;
		n--;
	}
	return (res);
}
