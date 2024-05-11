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
    int     pp_fds[2][2];
    pid_t   smpl_cmd_pid;
    pid_t   *ppl_pids;
    int     smpl_wstatus;
    int     *ppl_wstatuses;
    char    **my_paths;
    char    *execve_path;
    char    **execve_argv;
    char    **execve_envp;
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

// exec_main.c
void        exec(t_ast *s, char *subcmd, t_list **env);
// traversal.c
int         traverse_ast_to_exec(t_ast *s, t_exe *b);
// heredoc.c
void        exec_heredocs(t_exe *exe_bus);
void        free_heredocs(t_exe *exe_bus);
// exec_builtin.c
int         exec_builtin(int builtin, t_ast *s, t_exe *b);
// exec_bin.c
int         exec_bin(t_ast *s, t_exe *b);
// bin_prep_execve_args.c
void        prep_execve_args(t_ast *s, t_exe *b);
// bin_path_setup.c
void        seek_path(t_exe *b);
// pipeline_setup.c
void	    set_up_pipeline(t_ast *s, t_exe *b);
// pipe_switching.c
int         reuse_pipe_in_parent(t_exe *b);
void        lay_child_pipes(t_exe *b);
// wait_pipeline.c
void        go_wait(t_exe *b);
// exec_utils.c
void	    fork_one_for_simple_cmd(t_exe *b);
void        fork_one_in_ppl(t_exe *b);
void        free_strarr(char **strarr);

#endif