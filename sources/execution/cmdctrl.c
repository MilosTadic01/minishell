/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdctrl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:25:10 by mitadic           #+#    #+#             */
/*   Updated: 2024/04/16 13:07:19 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include

void	prep(t_data *data, int (*fds)[2], pid_t **children)
{
	*children = NULL;
	*children = (pid_t *)malloc(data->prcs_count * sizeof(pid_t));
	if (!(*children))
		// fail "malloc"
	if (pipe(fds[0]) < 0 || pipe(fds[1]) < 0)
		// fail "open pipes"
}

void	fork_one(t_data *data, int i, pid_t *children)
{
	children[i] = fork();
	if (children[i] < 0)
		// fail
}

void	go_exec(t_data *data)
{
	int	fds[2][2];
	int	i;
	pid_t	*children;

	prep(data, fds, &children);
	// ch_1st_prc(data, fds, children)
	i = 0;
	while (++i < (data->prcs_count - 1))
	{
		if (reuse_pipe(i, data->prcs_count, fds) < 0)
			// fail <- could do this inside 'reuse_pipe'
		fork_one(data, i, children);
		if (!children[i])
		{
			// ch_mid_prc(data, fds, i)
			// fail
		}
	}
	fork_one(data, i, children);
	if (!children[i])
		// ch_last_prc
	pipe_closer(i, fds);
	go_wait(data, children);
	free(children);
}

// ideal clean comprehensive go_exec blueprint, where the ctrls fork
void	go_exec(t_data *data)
{
	int	i;

	prep(data);
	// ch_1st_ctrl(data)
	i = 0;
	while (++i < (data->prcs_count - 1))
	{
		reuse_pipe(data, i);
		// ch_mid_ctrl(data, i)
	}
	// ch_last_ctrl(data, i);
	pipe_closer(data, i);
	go_wait(data);
	free(data->exec->children);
}
