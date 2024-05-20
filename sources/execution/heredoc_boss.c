/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_boss.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:02:38 by mitadic           #+#    #+#             */
/*   Updated: 2024/05/18 11:21:08 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	open_files_for_heredocs(t_exe *exe_bus)
{
	int		i;
	char	*num;
	char	*path;

	i = -1;
	while (++i < exe_bus->hd_count)
	{
		num = ft_itoa(i);
		path = ft_strjoin("/tmp/heredoc", num);
		free(num);
		exe_bus->hd_fds[i] = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (exe_bus->hd_fds[i] < 0)
			perror("heredoc: ");
		free(path);
	}
}

// static void reopen_hd_files_for_reading(t_exe *exe_bus)
// {
//   int   i;
//   char *num;
//   char *path;

//   i = -1;
//   while (++i < exe_bus->hd_count)
//   {
//	 num = ft_itoa(i);
//	 path = ft_strjoin("/tmp/heredoc", num);
//	 free(num);
//	 exe_bus->hd_fds[i] = open(path, O_RDONLY, 0644);
//	 if (exe_bus->hd_fds[i] < 0)
//	   perror("heredoc: ");
//	 free(path);
//   }
// }

// count heredocs
// malloc
// open files
// run prompts
int	exec_heredocs(t_exe *exe_bus)
{
	if (count_heredocs(exe_bus->s, exe_bus))
		return (PARSING_ERROR);
	if (exe_bus->hd_count == 0)
		return (SUCCESS);
	exe_bus->hd_delimiters = malloc((exe_bus->hd_count) * sizeof(char *));
	fetch_hd_delimiters(exe_bus->s, exe_bus);
	exe_bus->hd_fds = malloc(exe_bus->hd_count * sizeof(int));
	open_files_for_heredocs(exe_bus);
	prompt_for_all_heredocs(exe_bus);
	return (SUCCESS);
}

void	free_heredocs(t_exe *exe_bus)
{
	int		i;
	char	*num;
	char	*path;

	i = -1;
	if (exe_bus->hd_count == 0)
		return ;
	while (++i < exe_bus->hd_count)
	{
		num = ft_itoa(i);
		path = ft_strjoin("/tmp/heredoc", num);
		free(num);
		// close(exe_bus->hd_fds[i]);
		unlink(path);
		free(path);
		free(exe_bus->hd_delimiters[i]);
	}
	free(exe_bus->hd_fds);
	free(exe_bus->hd_delimiters);
}
