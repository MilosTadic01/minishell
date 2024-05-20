/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_path_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:23:38 by mitadic           #+#    #+#             */
/*   Updated: 2024/05/19 19:35:08 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*crt_cmdpath(char *path, char *cmd)
{
	char	*concat_step1;
	char	*concat_step2;

	concat_step1 = ft_strjoin(path, "/");
	if (!concat_step1)
		return (NULL);
	concat_step2 = ft_strjoin(concat_step1, cmd);
	free(concat_step1);
	if (!concat_step2)
		return (NULL);
	return (concat_step2);
}

static void	loop_thru_path_possibilities(t_exe *b)
{
	int	i;

	i = -1;
	while (b->my_paths && b->my_paths[++i])
	{
		b->execve_path = crt_cmdpath(b->my_paths[i], b->execve_argv[0]);
		if (!b->execve_path)
			free_n_error_n_exit("crt_cmdpath() fail", b);
		if (access(b->execve_path, X_OK) == 0 || !b->my_paths[i + 1])
			break ;
		free(b->execve_path);
		b->execve_path = NULL;
	}
	if (!b->my_paths || !b->my_paths[i + 1])
		b->exit_st = 127;
}

static int	is_directory(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		return (1);
	return (0);
}

// 1st layer check: if rel path or abs path
//		we set path = argv[0] and ret, i.e. omit loop_thru_paths() 
// 2nd layer check:
// 		if no access, 127
//		if abs path but is dir, 126
// if my_paths are set to NULL by ft_split because no PATH,
// loop_thru will set the exit value to 127, cause we let execve do its thing
void	seek_path(t_exe *b)
{
	char	*path_env;

	b->execve_path = NULL;
	path_env = NULL;
	if (b->execve_argv[0] == NULL)
		return ;
	if (ft_strncmp(b->execve_argv[0], "./", 2) == 0 || \
		b->execve_argv[0][0] == 47)
	{
		b->execve_path = b->execve_argv[0];
		if (access(b->execve_path, X_OK) != 0)
			b->exit_st = 127;
		else if (is_directory(b->execve_path))
			b->exit_st = 126;
		return ;
	}
	path_env = ft_getenv("PATH", *(b->env));
	if (path_env)
		b->my_paths = ft_split(path_env, ':');
	loop_thru_path_possibilities(b);
}
