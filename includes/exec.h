#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

typedef struct  s_exe {
    t_ast   *s;
    t_list  **env;
    int     *heredoc_fds;
    int     heredoc_count;
    pid_t   *pids;
    int     log_op;
}               t_exe;

enum    e_bltn
{
    ECHO = 1,
    CD,
    PWD,
    EXPORT,
    UNSET,
    ENV,
    EXIT
}   ;

void        exec(t_ast *s, t_list **env);
int         traverse_ast_to_exec(t_ast *s, t_exe *b);
void        exec_heredocs(t_exe *exe_bus);
void        exec_builtin(t_ast *s, t_list **env);
void        exec_bin(t_ast *ast, t_list **env);

#endif