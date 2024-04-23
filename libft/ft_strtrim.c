/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:51:28 by dzubkova          #+#    #+#             */
/*   Updated: 2023/11/30 13:38:08 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_idx_start(const char *str, char const *set);
static int	get_idx_end(const char *str, char const *set);
char		*ft_strtrim(char const *s1, char const *set);
static void	copy_str(char *new_str, const char *str, const char *set);
static int	in(char ch, char const *set);

/*int	main(void)
{
	char *s = ft_strtrim("", "");
	printf("%s\n", s);
}*/

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new_str;
	char	*res;
	int		start;
	int		end;

	if (!s1 || !set)
		return (NULL);
	start = get_idx_start(s1, set);
	end = get_idx_end(s1, set);
	if (end == -1 && start == -1)
	{
		res = malloc(sizeof(char));
		if (!res)
			return (NULL);
		ft_strlcpy(res, "\0", 1);
		return (res);
	}
	new_str = malloc(end - start + 2);
	res = new_str;
	if (!new_str)
		return (NULL);
	copy_str(new_str, s1, set);
	return (res);
}

static void	copy_str(char *new_str, const char *str, const char *set)
{
	int	idx;
	int	start_idx;
	int	end_idx;

	idx = 0;
	start_idx = get_idx_start(str, set);
	end_idx = get_idx_end(str, set);
	while (*str)
	{
		if (idx >= start_idx && idx <= end_idx)
		{
			*new_str = *str;
			new_str++;
		}
		str++;
		idx++;
	}
	*new_str = '\0';
}

static int	in(char ch, char const *set)
{
	while (*set)
	{
		if (*set == ch)
			return (1);
		set++;
	}
	return (0);
}

static int	get_idx_start(const char *str, char const *set)
{
	int	idx;

	idx = 0;
	while (*str)
	{
		if (!(in(*str, set)))
			return (idx);
		idx++;
		str++;
	}
	return (-1);
}

static int	get_idx_end(const char *str, char const *set)
{
	size_t	len;
	int		idx;

	len = ft_strlen(str);
	idx = len - 1;
	while (idx >= 0)
	{
		if (!in(str[idx], set))
			return (idx);
		idx--;
	}
	return (-1);
}
