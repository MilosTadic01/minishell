/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:11:51 by dzubkova          #+#    #+#             */
/*   Updated: 2023/11/17 13:22:27 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd);

/*int	main(void)
{
	int fd = 1;
	ft_putstr_fd("foo", fd);
}*/

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
