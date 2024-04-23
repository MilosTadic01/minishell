/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:42:44 by dzubkova          #+#    #+#             */
/*   Updated: 2023/12/04 15:44:07 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_split(char const *s, char c);
static int	count_delims(char const *s, char c);
static void	parse(const char *s, char **res, char c, int *idx);
static void	free_arr(char **array, int *idx);
static void	write_substring(char **res, const char *s,
				int current_len, int *idx);

/*int	main(void)
{
	char **res = ft_split("", 'a');
	int i = 0;
	while (res[i])
	{
		printf("%s\n", res[i++]);
	}
	return 0;
}*/

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		delim;
	int		idx;

	if (!ft_strncmp(s, "", 1))
	{
		res = malloc(sizeof(char *) * 1);
		if (!res)
			return (NULL);
		*res = NULL;
		return (res);
	}
	delim = count_delims(s, c);
	idx = 0;
	res = malloc(sizeof(char *) * (delim + 1));
	if (!res)
		return (NULL);
	parse(s, res, c, &idx);
	res[idx] = NULL;
	return (res);
}

static void	parse(const char *s, char **res, char c, int *idx)
{
	int		delim;
	size_t	current_len;

	current_len = 0;
	delim = 1;
	while (*s)
	{
		if (*s != c)
		{
			current_len++;
			delim = 0;
		}
		else if (*s == c && !delim)
		{
			write_substring(res, s, current_len, idx);
			current_len = 0;
			delim = 1;
		}
		s++;
	}
	if (current_len)
		write_substring(res, s, current_len, idx);
}

static void	write_substring(char **res, const char *s,
				int current_len, int *idx)
{
	res[*idx] = malloc(current_len + 1);
	if (!res[*idx])
	{
		free_arr(res, idx);
		return ;
	}
	ft_strlcpy(res[(*idx)++], s - current_len,
		sizeof(char) * (current_len + 1));
}

static int	count_delims(char const *s, char c)
{
	int	delim;
	int	count;

	delim = 1;
	count = 1;
	while (*s)
	{
		if (*s == c && !delim)
		{
			count++;
			delim = 1;
		}
		else if (*s != c)
			delim = 0;
		else
			delim = 1;
		s++;
	}
	if (*(s - 1) == c)
		count -= 1;
	return (count);
}

static void	free_arr(char **array, int *idx)
{
	int	i;

	i = 0;
	while (i <= *idx)
		free(array[i++]);
	free(array);
}
