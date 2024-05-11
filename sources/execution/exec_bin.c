#include "../../includes/minishell.h"

static void    convert_env(t_exe *b)
{
    int     size;
    int     i;
    t_list  *envcpy;

    size = ft_lstsize(*(b->env));
    b->execve_envp = malloc((size + 1) * sizeof(char *));
    if (!b->execve_envp)
    {
        perror("minishell: for execve: malloc fail for envp: ");
        return (NULL);
    }
    i = -1;
    envcpy = *(b->env);
    while (envcpy)
    {
        b->execve_envp[++i] = ft_strdup(envcpy->as_str);
        envcpy = envcpy->next;
    }
    b->execve_envp[++i] = NULL;
}

static void prep_execve_args(t_ast *s, t_exe *b)
{
    convert_env(b);
    convert_argv(s, b);
}

int    exec_bin(t_ast *s, t_exe *b)
{
    prep_execve_args(s, b);
    if (b->is_pipeline)
    {
        ++(b->i);
        reuse_pipe_in_parent(b);
        fork_one(b);
        if (b->ppl_pids[b->i] == 0)
        {
            lay_child_pipes(b);
            // slap_on_redirs(s, b);
            execve();
        }
    }
    else
        execve();
    return (0);
}