/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_prompting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:02:38 by mitadic           #+#    #+#             */
/*   Updated: 2024/05/20 17:03:25 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*static void	sigint_handler(int signum)
{
	(void)signum;
	exit(130);
}*/

static void	prompt_for_one_heredoc(t_exe *exe_bus, char *limiter, int i)
{
	char	*line;

	while (1)
	{
		line = NULL;
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
		{
			ft_putstr_fd("eof received when delimiter expected\n", 2);
			exit(0);
		}
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, exe_bus->hd_fds[i]);
		free(line);
	}
}

static void	set_a_limiter_and_prompt_for_each_in_a_loop(t_exe *exe_bus)
{
	int		i;
	char	*limiter;

	i = -1;
	limiter = NULL;
	signal(SIGINT, SIG_DFL);
	while (++i < exe_bus->hd_count)
	{
		limiter = ft_strjoin(exe_bus->hd_delimiters[i], "\n");
		if (!limiter)
		{
			ft_putstr_fd("heredoc limiter: malloc fail\n", STDERR_FILENO);
			continue ;
		}
		prompt_for_one_heredoc(exe_bus, limiter, i);
		if (close(exe_bus->hd_fds[i]) < 0)
			perror("heredoc after writing");
		free(limiter);
		limiter = NULL;
	}
	exit(0);
}

void	prompt_for_all_heredocs(t_exe *exe_bus)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		set_a_limiter_and_prompt_for_each_in_a_loop(exe_bus);
	else
		waitpid(pid, &status, 0);
}
