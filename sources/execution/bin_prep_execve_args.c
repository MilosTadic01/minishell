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
        return ;
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

static void convert_argv(t_ast *s, t_exe *b)
{
    int i;

    i = -1;
    b->execve_argv = malloc((s->command->size + 1) * sizeof(char *));
    while (++i < s->command->size)
    {
        b->execve_argv[i] = ft_strdup(s->command->args[i]);
    }
    b->execve_argv[i] = NULL;
}

void prep_execve_args(t_ast *s, t_exe *b)
{
    if (!s || !b)
        ft_putstr_fd("minishell: exec: unpopulated parameters\n", 2);
    if (b->execve_envp == NULL)
        convert_env(b);
    convert_argv(s, b);
    seek_path(b);
}