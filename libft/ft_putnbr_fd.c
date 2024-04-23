/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:15:51 by dzubkova          #+#    #+#             */
/*   Updated: 2023/12/04 15:32:16 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define STRING_SIZE 12
#define MIN_INT -2147483648

void	ft_putnbr_fd(int n, int fd);

/*int	main(void)
{
	int fd = 1;
	ft_putnr_fd(-2147483647 -1, fd);
	return (0);
}*/

void	ft_putnbr_fd(int n, int fd)
{
	int		rem;
	char	st[STRING_SIZE];
	int		idx;

	idx = 0;
	if (n != 0 && n != MIN_INT)
	{
		if (n < 0 && idx <= 11)
		{
			write(fd, "-", 1);
			n *= -1;
		}
		while (n > 0)
		{
			rem = n % 10;
			n /= 10;
			st[idx++] = rem + '0';
		}
		while (--idx >= 0)
			write(fd, &st[idx], 1);
	}
	else if (n == 0)
		write(fd, "0", 1);
	else if (n == MIN_INT)
		write(fd, "-2147483648", 11);
}
