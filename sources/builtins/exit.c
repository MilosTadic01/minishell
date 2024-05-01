#include "../../includes/minishell.h"

/*if just 'exit', then exit(errno) or exit(0)? What if errno is set to some bullshit from before?*/

static int  too_many_args(char **strarr)
{
    if (strarr[1] && strarr[2])
    {
        ft_putstr_fd("minishell: exit: too many arguments\n", 2);
        return (1);
    }
    return (0);
}

static int  is_numeric_arg(char **strarr)
{
    int i;

    i = -1;
    if (ft_isplusminus(strarr[1][0]))
        ++i;
    while (strarr[1][++i])
    {
        if (!ft_isdigit(strarr[1][i]))
        {
            ft_putstr_fd("minishell: exit: ", 2);
            ft_putstr_fd(strarr[1], 2);
            ft_putstr_fd(": numeric argument required\n", 2);
            return (0);
        }
    }
    return (1);
}

void    ft_exit(char **strarr)
{
    if (!strarr && !strarr[0])
        return ;
    ft_putstr_fd("exit\n", 2); //but not when in ()? How?
    if (!strarr[1]) // segfault? nah, should be NULL terminated
        exit(errno); // if just 'exit' it doesn't use errno, it just exits clean, right? Nope, actually carries the errno when no arguments. See: bbbb || exit
    if (too_many_args(strarr)) // hold on, if this is the case it WILL NOT EXIT?? but will still print 'exit', wth?
        return ;
    if (!is_numeric_arg(strarr))
        exit(2);
    exit((unsigned char)ft_atoi(strarr[1]));
    // check that strarr[1] is a numeric, else perror("minishell: exit: <strarr[0]>: {numeric argument required | 2}") then exit(errno)
}