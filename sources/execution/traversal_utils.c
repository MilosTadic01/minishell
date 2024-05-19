#include "../../includes/minishell.h"

int	which_builtin(char *str)
{
	if (!str)
		return (0);
	if (!ft_strcmp(str, "echo"))
		return (ECHO);
	if (!ft_strcmp(str, "cd"))
		return (CD);
	if (!ft_strcmp(str, "pwd"))
		return (PWD);
	if (!ft_strcmp(str, "export"))
		return (EXPORT);
	if (!ft_strcmp(str, "unset"))
		return (UNSET);
	if (!ft_strcmp(str, "env"))
		return (ENV);
	if (!ft_strcmp(str, "exit"))
		return (EXIT);
	return (0);
}

void	close_pipes_and_wait_and_reset_pipeline(t_exe *b)
{
	pipe_closer(b);
	go_wait(b);
	// if (b->is_subshell == 0)
	b->is_pipeline = 0;
	b->ppl_cmd_count = 0;
}

void	increment_hd_idx(t_ast *s, t_exe *b)
{
	t_list	*ins_cpy;

	if (!s || !b)
		return ;
	ins_cpy = s->command->ins;
	while (ins_cpy)
	{
		if (ins_cpy->as_item->type == REDIRECT_IN_IN)
			(b->hd_idx)++;
		ins_cpy = ins_cpy->next;
	}
}
