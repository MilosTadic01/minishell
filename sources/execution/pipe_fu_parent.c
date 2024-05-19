#include "../../includes/minishell.h"

// static void    close_all_pipeends(t_exe *b)
// {
//     int     i;

//     i = -1;
//     while (++i < 2)
//     {
//         if (close(b->pp_fds[i][0]) < 0)
//             perror("close");
//         b->pp_fds[i][0] = -1;
//         if (close(b->pp_fds[i][1]) < 0)
//             perror("close");
//         b->pp_fds[i][1] = -1;
//     }
// }

// Seemingly obsolete note:
// 'else' == the read end of the pipe leading into 'last' is already closed
// From the bottom of the function:
// if last then close the open read end, but unfortunately it messes all up
	// and exits minishell
		// if (b->i == (b->ppl_cmd_count - 1) && 
		//     close(b->pp_fds[1 - (b->i % 2)][0] < 0))
		//     return (-1);
	// if (close(STDIN_FILENO) < 0)
	//     perror("close");
	// if (close(STDOUT_FILENO) < 0)
	//     perror("close");
void	pipe_closer(t_exe *b)
{
	if (b->pp_fds[b->i % 2][0] > -1)
	{
		if (close(b->pp_fds[b->i % 2][0]) < 0)
			perror("close");
		b->pp_fds[b->i % 2][0] = -1;
	}
	if (b->pp_fds[b->i % 2][1] > -1)
	{
		if (close(b->pp_fds[b->i % 2][1]) < 0)
			perror("close");
		b->pp_fds[b->i % 2][1] = -1;
	}
	if (b->pp_fds[1 - (b->i % 2)][0] > -1)
	{
		if (close(b->pp_fds[1 - (b->i % 2)][0]) < 0)
			perror("close");
		b->pp_fds[1 - (b->i % 2)][0] = -1;
	}
	if (b->pp_fds[1 - (b->i % 2)][1] > -1)
	{
		if (close(b->pp_fds[1 - (b->i % 2)][1]) < 0)
			perror("close");
		b->pp_fds[1 - (b->i % 2)][1] = -1;
	}
}

/* The 'if' checks whether we even need any reopening, i.e. more pipes
Then the pipe which is not leading into child is reopened and points OUT.
1 if: no closing for 1st cmd
2 else if: check if exactly 2nd cmd in ppln
3 else if: all others
...
if (b->i != (b->ppl_cmd_count ...) if not last && reopen pipe. && as in "then"
*/
int	reuse_pipe_in_parent(t_exe *b)
{
	if (b->i == 0)
		;
	else if (b->i == 1)
	{
		if (close(b->pp_fds[1 - (b->i % 2)][1]) < 0)
			return (-1);
		b->pp_fds[1 - (b->i % 2)][1] = -1;
	}
	else if (b->i > 1)
	{
		if (b->pp_fds[b->i % 2][0] > -1 && b->pp_fds[1 - (b->i % 2)][1] > -1 \
			&& (close(b->pp_fds[b->i % 2][0]) < 0 \
			|| close(b->pp_fds[1 - (b->i % 2)][1]) < 0))
			return (-1);
		b->pp_fds[b->i % 2][0] = -1;
		b->pp_fds[1 - (b->i % 2)][1] = -1;
		if (b->i != (b->ppl_cmd_count - 1) && \
			pipe(b->pp_fds[b->i % 2]) < 0)
			return (-1);
	}
	return (0);
}
