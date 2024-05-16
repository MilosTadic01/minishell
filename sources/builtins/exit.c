#include "../../includes/minishell.h"

static int  too_many_args(int size)
{
    if (size > 2)
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
        if (!ft_isdigit(cmdarr[1][i]) || i > 9)
        {
            ft_putstr_fd("minishell: exit: ", 2);
            ft_putstr_fd(cmdarr[1], 2);
            ft_putstr_fd(": numeric argument required\n", 2);
            return (0);
        }
    }
    return (1);
}

// if just 'exit' it actually carries the errno when no args. See: bbbb || exit
int    ft_exit(int size, char **cmdarr)
{
    if (!cmdarr && !cmdarr[0])
        return (1);
    ft_putstr_fd("exit\n", 2); //but not when in ()? How?
    if (size == 1)
        exit(errno); 
    if (too_many_args(size)) // hold on, if this is the case it WILL NOT EXIT?? but will still print 'exit', wth?
        return (1);
    if (!is_numeric_arg(cmdarr))
        exit(2);
    exit((unsigned char)ft_atoi(cmdarr[1]));
    return (SUCCESS); // futile?
}