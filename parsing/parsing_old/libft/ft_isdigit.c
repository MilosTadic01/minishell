/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:14:40 by dzubkova          #+#    #+#             */
/*   Updated: 2023/11/17 13:19:52 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c);

/*int	main(void)
{
	return (0);
}*/

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}