/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 17:34:00 by dzubkova          #+#    #+#             */
/*   Updated: 2024/03/31 17:39:53 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(char ch)
{
	if (ch == ' ' || (ch >= '\t' && ch <= '\r'))
		return (1);
	return (0);
}