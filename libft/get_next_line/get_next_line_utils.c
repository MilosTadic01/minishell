/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:08:26 by mitadic           #+#    #+#             */
/*   Updated: 2024/02/01 17:29:42 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ftm_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i])
		i++;
	return (i);
}

int	ft_chrwhere(char *s, int c)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	if (s[i] == c)
		return (i);
	return (-1);
}

char	*ftm_strjoin(char *s1, char *s2)
{
	char	*dest;
	int		i;
	int		j;

	dest = malloc((ftm_strlen(s1) + ftm_strlen(s2) + 1));
	if (dest == NULL)
		return (NULL);
	i = -1;
	j = -1;
	if (s1)
	{
		while (s1[++i])
			dest[i] = s1[i];
	}
	if (s2)
	{
		while (s2[++j])
			dest[i++] = s2[j];
	}
	dest[i] = '\0';
	return (dest);
}

char	*ftm_substr(const char *s, size_t start, size_t len)
{
	char	*src;
	char	*dest;
	size_t	i;

	if (!s || len == 0)
		return (NULL);
	src = (char *)s;
	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len && src[start + i] != 0)
	{
		dest[i] = src[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	free_if_extant(char **s1, char **s2)
{
	if (s1 && *s1)
	{
		free (*s1);
		(*s1) = NULL;
	}
	if (s2 && *s2)
	{
		free (*s2);
		(*s2) = NULL;
	}
	return ;
}
