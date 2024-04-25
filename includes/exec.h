#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

typedef struct  s_exe {
    t_ast   *s;
    t_list  *env;
    int     *heredoc_fds;
    int     heredoc_count;
}               t_exe;

enum e_bltn
{
    ECHO,
    CD,
    PWD,
    EXPORT,
    UNSET,
    ENV,
    EXIT
}

#endif