
#include "../../includes/minishell.h"

void	prep(t_exe *b, int (*fds)[2], pid_t **children)
{
	*children = NULL;
	*children = (pid_t *)malloc(b->ppl_cmd_count * sizeof(pid_t));
	if (!(*children))
		// fail "malloc"
	if (pipe(fds[0]) < 0 || pipe(fds[1]) < 0)
		; // fail "open pipes"
}

void	fork_one(t_exe *b, int i, pid_t *children)
{
	children[i] = fork();
	if (children[i] < 0)
		; // fail
}

void	go_exec(t_exe *b)
{
	int	fds[2][2];
	int	i;
	pid_t	*children;

	prep(b, fds, &children);
	// ch_1st_prc(data, fds, children)
	i = 0;
	while (++i < (b->ppl_cmd_count - 1))
	{
		if (reuse_pipe(i, b->ppl_cmd_count, fds) < 0)
			// fail <- could do this inside 'reuse_pipe'
		fork_one(b, i, children);
		if (!children[i])
		{
			// ch_mid_prc(data, fds, i)
			// fail
		}
	}
	fork_one(b, i, children);
	if (!children[i])
		// ch_last_prc
	pipe_closer(i, fds);
	go_wait(b, children);
	free(children);
}

// ideal clean comprehensive go_exec blueprint, where the ctrls fork
void	set_up_pipeline(t_exe *b)
{
	int	i;

	prep(b);
	// ch_1st_ctrl(data)
	i = 0;
	while (++i < (b->ppl_cmd_count - 1))
	{
		reuse_pipe(b, i);
		// ch_mid_ctrl(data, i)
	}
	// ch_last_ctrl(data, i);
	pipe_closer(b, i);
	go_wait(b);
	free(b->ppl_pids);
}