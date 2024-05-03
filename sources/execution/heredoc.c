#include "../../includes/minishell.h"

static void open_files_for_heredocs(t_exe *exe_bus)
{
    int i;

    i = -1;
    while (++i < exe_bus->heredoc_count)
    {
        exe_bus->heredoc_fds[i] = open("/tmp/", O_RDWR | O_TMPFILE | O_APPEND, 0644);
        if (exe_bus->heredoc_fds[i] < 0)
            perror("heredoc: ");
    }
}

static void prompt_for_heredocs(t_exe *exe_bus)
{
    int     i;
    char    *line;
    char    *limiter;

    i = -1;
    while (++i < exe_bus->heredoc_count)
    {
        line = NULL;
        limiter = ft_strjoin(exe_bus->s->command->ins->as_item->filename, "\n");
        if (!limiter)
        {
            ft_putstr_fd("heredoc limiter: malloc fail\n", STDERR_FILENO);
            continue ;
        }
        while (line != limiter)
        {
            line = readline("> ");
            if (!line)
                ft_putstr_fd("readline error\n", STDERR_FILENO);
            ft_putstr_fd(line, exe_bus->heredoc_fds[i]);
        }
        free(limiter);
        free(line);
    }
}

void    exec_heredocs(t_exe *exe_bus)
{
    t_list	*tmp;

    tmp = exe_bus->s->command->ins;
    // count heredocs
    while (tmp)
    {
        if (tmp->as_item->type == REDIRECT_IN_IN)
            exe_bus->heredoc_count++;
        tmp = tmp->next;
    }
    // malloc
    exe_bus->heredoc_fds = malloc(exe_bus->heredoc_count * sizeof(int));
    // open files
    open_files_for_heredocs(exe_bus);
    // run prompts
    prompt_for_heredocs(exe_bus);
}