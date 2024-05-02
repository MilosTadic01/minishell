#include "../../includes/minishell.h"

static int  too_many_args(char **cmdarr)
{
    if (cmdarr[1] && cmdarr[2])
    {
        ft_putstr_fd("minishell: exit: too many arguments\n", 2);
        return (1);
    }
    return (0);
}

static int  is_numeric_arg(char **cmdarr)
{
    int i;

    i = -1;
    if (ft_isplusminus(cmdarr[1][0]))
        ++i;
    while (cmdarr[1][++i])
    {
        if (!ft_isdigit(cmdarr[1][i]))
        {
            ft_putstr_fd("minishell: exit: ", 2);
            ft_putstr_fd(cmdarr[1], 2);
            ft_putstr_fd(": numeric argument required\n", 2);
            return (0);
        }
    }
    return (1);
}

void    ft_exit(char **cmdarr)
{
    if (!cmdarr && !cmdarr[0])
        return ;
    ft_putstr_fd("exit\n", 2); //but not when in ()? How?
    if (!cmdarr[1]) // segfault? nah, should be NULL terminated
        exit(errno); // if just 'exit' it doesn't use errno, it just exits clean, right? Nope, actually carries the errno when no arguments. See: bbbb || exit
    if (too_many_args(cmdarr)) // hold on, if this is the case it WILL NOT EXIT?? but will still print 'exit', wth?
        return ;
    if (!is_numeric_arg(cmdarr))
        exit(2);
    exit((unsigned char)ft_atoi(cmdarr[1]));
}