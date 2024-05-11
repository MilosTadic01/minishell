
#include "../../includes/minishell.h"

// void	fork_one(t_exe *b, int i, pid_t *children)
// {
// 	children[i] = fork();
// 	if (children[i] < 0)
// 		; // fail
// }

// void	go_exec(t_exe *b)
// {
// 	int	fds[2][2];
// 	int	i;
// 	pid_t	*children;

// 	prep(b, fds, &children);
// 	// ch_1st_prc(data, fds, children)
// 	i = 0;
// 	while (++i < (b->ppl_cmd_count - 1))
// 	{
// 		if (reuse_pipe(i, b->ppl_cmd_count, fds) < 0)
// 			// fail <- could do this inside 'reuse_pipe'
// 		fork_one(b, i, children);
// 		if (!children[i])
// 		{
// 			// ch_mid_prc(data, fds, i)
// 			// fail
// 		}
// 	}
// 	fork_one(b, i, children);
// 	if (!children[i])
// 		// ch_last_prc
// 	pipe_closer(i, fds);
// 	go_wait(b, children);
// 	free(children);
// }

////////////////////////////////////////////////

static void update_pipe_info(t_ast *s, t_exe *b)
{
    b->is_pipeline = 1;
    if (s->tag == PIPE)
    {
        b->ppl_cmd_count++;
        if (s->right)
            update_pipe_info(s->right, b);
    }
}

static void	prep_pipes_n_pids(t_exe *b)
{
	b->i = -1;
	b->ppl_pids = (pid_t *)malloc(b->ppl_cmd_count * sizeof(pid_t));
	if (!(b->ppl_pids))
		; // fail "malloc"
	if (pipe(b->pp_fds[0]) < 0 || pipe(b->pp_fds[1]) < 0)
		; // fail "open pipes"
}

void	set_up_pipeline(t_ast *s, t_exe *b)
{
	update_pipe_info(s, b);
	prep_pipes_n_pids(b);
}