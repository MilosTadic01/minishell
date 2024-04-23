/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:02:03 by dzubkova          #+#    #+#             */
/*   Updated: 2024/03/31 17:42:28 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_parse_digits(const char *nptr, char *tmp, int *idx);
int			ft_atoi(const char *nptr);

int	ft_atoi(const char *nptr)
{
	int		sign;
	char	tmp[20];
	int		idx;
	int		res;

	sign = 1;
	res = 0;
	while ((nptr && *nptr >= 9 && *nptr <= 13 && *nptr)
		|| (ft_isspace(*nptr)))
		nptr++;
	if (!(ft_strncmp(INT_MIN_STR, nptr, 11)))
		return (-2147483648);
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	idx = 0;
	ft_parse_digits(nptr, tmp, &idx);
	tmp[idx] = '\0';
	idx = 0;
	while (tmp[idx])
		res = (res * 10) + (tmp[idx++] - '0');
	return (res * sign);
}

static void	ft_parse_digits(const char *nptr, char *tmp, int *idx)
{
	int	start;

	start = 0;
	while (ft_isdigit(*(nptr)))
	{
		if (*nptr == '0' && !start)
			nptr++;
		else
		{
			tmp[(*idx)++] = *nptr++;
			start = 1;
		}
	}
}
