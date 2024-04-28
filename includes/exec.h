#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

typedef struct  s_exe {
    t_ast   *s;
    t_list  *env;
    int     *heredoc_fds;
    int     heredoc_count;
    pid_t   *pids;
}               t_exe;

enum e_bltn
{
    ECHO = 1,
    CD,
    PWD,
    EXPORT,
    UNSET,
    ENV,
    EXIT
};

void        exec(t_ast *s, t_list *env);
void        exec_heredocs(t_exe *exe_bus);

#endif