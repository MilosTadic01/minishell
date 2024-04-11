/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:03:51 by dzubkova          #+#    #+#             */
/*   Updated: 2023/12/01 12:46:30 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n);
static int	set_sign(int *n);
static int	ft_remainder(int *n);
static char	*allocate_space(char *tmp);
static char	*edge_cases(int n);

/*int	main(void)
{
	char *s = ft_itoa(0);
	printf("%s\n", s);
	free(s);
}*/

char	*ft_itoa(int n)
{
	char	tmp[12];
	char	*res;
	int		idx;
	int		minus;
	char	*start;

	res = edge_cases(n);
	if (res)
		return (res);
	free(res);
	idx = 0;
	minus = set_sign(&n);
	while (n)
		tmp[idx++] = ft_remainder(&n);
	if (minus)
		tmp[idx++] = '-';
	tmp[idx] = '\0';
	res = allocate_space(tmp);
	if (!res)
		return (NULL);
	start = res;
	while (--idx >= 0)
		*res++ = tmp[idx];
	*res = '\0';
	return (start);
}

static char	*edge_cases(int n)
{
	char	*res;

	if (n == MIN_INT)
	{
		res = malloc(12);
		if (!res)
			return (NULL);
		ft_strlcpy(res, "-2147483648", 12);
		return (res);
	}
	if (n == 0)
	{
		res = malloc(2);
		if (!res)
			return (NULL);
		ft_strlcpy(res, "0", 2);
		return (res);
	}
	else
		return (NULL);
}

static char	*allocate_space(char *tmp)
{
	char	*result;
	size_t	len;

	len = ft_strlen(tmp);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	return (result);
}

static int	set_sign(int *n)
{
	if (*n < 0)
	{
		*n *= -1;
		return (1);
	}
	return (0);
}

static int	ft_remainder(int *n)
{
	int	rem;

	rem = (*n % 10) + '0';
	*n = *n / 10;
	return (rem);
}
