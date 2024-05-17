/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:08:40 by mitadic           #+#    #+#             */
/*   Updated: 2024/02/01 17:30:39 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif
# ifndef MAX_FD
#  define MAX_FD 1024
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*set_line(int fd, char **rest, char *buff);
int		set_rest(char **rest, char **line);
int		set_rest_purge(char **rest, char **line);

char	*ftm_substr(const char *s, size_t start, size_t len);
char	*ftm_strjoin(char *s1, char *s2);
int		ft_chrwhere(char *s, int c);
int		ftm_strlen(char *s);
void	free_if_extant(char **s1, char **s2);

#endif
