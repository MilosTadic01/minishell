/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:56:32 by dzubkova          #+#    #+#             */
/*   Updated: 2023/11/17 13:22:00 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd);

/*int	main(void)
{
	char *fd = malloc(sizeof(char) * 1);
	ft_putchar_fd('9', *fd);
	printf("%i\n", *fd);
	return (0);
}*/

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
