#include "../../includes/minishell.h"

static int count_heredocs(t_ast *s, t_exe *b)
{
	t_ast   *subsh_ast;
	t_list  *ins_cpy;

	if (!s || !b)
		return (ERROR);
	subsh_ast = NULL;
	if (s->tag == COMMAND && s->command->ins)
	{
		ins_cpy = s->command->ins;
		while (ins_cpy)
		{
			if (ins_cpy->as_item->type == REDIRECT_IN_IN)
				b->hd_count++;
			ins_cpy = ins_cpy->next;
		}
	}
	else if (s->tag == SUBSHELL || s->tag == RECCALL)
	{
		subsh_ast = parse(s->subshell_cmd, b->env);
		if (!subsh_ast)
			return (PARSING_ERROR);
		if (subsh_ast)
			count_heredocs(subsh_ast, b);
		free_ast(subsh_ast);
		subsh_ast = NULL;
	}
	if (s->left)
		count_heredocs(s->left, b);
	if (s->right)
		count_heredocs(s->right, b);
	return (SUCCESS);
}

static void fetch_hd_delimiters(t_ast *s, t_exe *b)
{
	t_ast   *subsh_ast;
	t_list  *ins_cpy;

	subsh_ast = NULL;
	if (s->tag == COMMAND && s->command->ins)
	{
		ins_cpy = s->command->ins;
		while (ins_cpy)
		{
			if (ins_cpy->as_item->type == REDIRECT_IN_IN)
				b->hd_delimiters[++(b->i)] = ft_strdup(ins_cpy->as_item->filename);
			ins_cpy = ins_cpy->next;
		}
	}
	if (s->tag == SUBSHELL || s->tag == RECCALL)
	{
		subsh_ast = parse(s->subshell_cmd, b->env);
		if (!subsh_ast)
			ft_putstr_fd("fetch_hd_delimiters: recursive parsing fail\n", 2);
		else if (subsh_ast)
			fetch_hd_delimiters(subsh_ast, b);
		free_ast(subsh_ast);
	}
	if (s->left)
		fetch_hd_delimiters(s->left, b);
	if (s->right)
		fetch_hd_delimiters(s->right, b);
}

static void open_files_for_heredocs(t_exe *exe_bus)
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
		exe_bus->hd_fds[i] = open(path, O_WRONLY| O_CREAT | O_TRUNC, 0644);
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

/*static void	sigint_handler(int signum)
{
	(void)signum;
	exit(130);
}*/


static void prompt_for_one_heredoc(t_exe *exe_bus, char *limiter, int i)
{
	char	*line;
	// char	*line_n;

	while (1)
	{
		line = NULL;
		// line_n = NULL;
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

static void prompt_for_all_heredocs(t_exe *exe_bus)
{
	int		i;
	char	*limiter;
	pid_t	pid;
	int		status;

	i = -1;
	pid = fork();
	//receive_signals_noninteractive();
	if (pid == 0)
	{
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
				ft_putstr_fd("heredoc after writing: close fail\n", STDERR_FILENO);
			free(limiter);
		}
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
}

int	exec_heredocs(t_exe *exe_bus)
{
	// count heredocs
	if (count_heredocs(exe_bus->s, exe_bus))
		return (PARSING_ERROR);
	if (exe_bus->hd_count == 0)
		return (SUCCESS);
	// malloc
	exe_bus->hd_delimiters = malloc((exe_bus->hd_count) * sizeof(char *));
	fetch_hd_delimiters(exe_bus->s, exe_bus);
	// exe_bus->hd_delimiters[exe_bus->hd_count] = NULL; changed my mind, no need to NULL-terminate
	exe_bus->hd_fds = malloc(exe_bus->hd_count * sizeof(int));
	// open files
	open_files_for_heredocs(exe_bus);
	// run prompts
	prompt_for_all_heredocs(exe_bus);
	return (SUCCESS);
	// reopen_hd_files_for_reading(exe_bus);
	// free
	// free_heredocs(exe_bus); // just for leak control now, will actually be needed in redir
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