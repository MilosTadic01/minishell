/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:08:11 by mitadic           #+#    #+#             */
/*   Updated: 2024/02/01 14:16:55 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*set_line(int fd, char **rest, char *buff)
{
	char	*line;
	int		br;

	line = ftm_strjoin("", &(**rest));
	free_if_extant(&(*rest), NULL);
	if (!line)
		return (NULL);
	while (1)
	{
		br = read(fd, buff, BUFFER_SIZE);
		if (br < 0)
		{
			free_if_extant(&(*rest), &line);
			return (NULL);
		}
		buff[br] = 0;
		(*rest) = line;
		line = ftm_strjoin(&(**rest), &(*buff));
		free_if_extant(&(*rest), NULL);
		if (line == NULL)
			return (NULL);
		if (br == 0 || ft_chrwhere(line, 10) != -1)
			break ;
	}
	return (line);
}

int	set_rest_purge(char **rest, char **line)
{
	free_if_extant(&(*rest), &(*line));
	return (-1);
}

int	set_rest(char **rest, char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while ((*line)[i] != '\n' && (*line)[i] != 0)
		i++;
	if ((*line)[i] == 10)
		i++;
	tmp = ftm_substr(&(**line), 0, i);
	if (!tmp)
		return (set_rest_purge(&(*rest), &(*line)));
	if ((*line)[i - 1] == '\n' && (*line)[i] != 0)
	{
		(*rest) = ftm_substr((*line), i, (ftm_strlen(*line) - i));
		if (!rest && !(*rest))
			return (set_rest_purge(&(*rest), &(*line)));
	}
	free_if_extant(&(*line), NULL);
	(*line) = tmp;
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*rest[MAX_FD];
	char		*line;
	char		*buff;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff || fd < 0 || BUFFER_SIZE < 1 || (read(fd, 0, 0) < 0))
	{
		if (fd >= 0)
			free_if_extant(&rest[fd], &buff);
		else
			free_if_extant(&buff, NULL);
		return (NULL);
	}
	line = set_line(fd, &rest[fd], buff);
	free_if_extant(&buff, NULL);
	if (!line)
		return (NULL);
	if ((set_rest(&rest[fd], &line)) < 0)
		return (NULL);
	if (line != NULL && *line == 0)
		free_if_extant(&rest[fd], &line);
	return (line);
}
