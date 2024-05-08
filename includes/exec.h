#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

typedef struct  s_exe {
    t_ast   *s;
    t_list  **env;
    int     i;
    int     hd_count;
    int     *hd_fds;
    char    **hd_delimiters;
    int     is_pipeline;
    int     ppl_cmd_count;
    int     *ppl_fds;
    pid_t   *ppl_pids;
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

void        exec(t_ast *s, char *subcmd, t_list **env);
int         traverse_ast_to_exec(t_ast *s, t_exe *b);
void        exec_heredocs(t_exe *exe_bus);
void        free_heredocs(t_exe *exe_bus);
int         exec_builtin(int builtin, t_ast *s, t_exe *b);
int         exec_bin(t_ast *ast, t_list **env);

#endif