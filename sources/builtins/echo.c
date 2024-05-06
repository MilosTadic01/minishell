#include "../../includes/minishell.h"

static void echo_one_arg(char *str)
{
    int i;

    i = -1;
    while (str[++i])
    {
        ft_putchar_fd(str[i], STDOUT_FILENO);
    }
}

static int  is_n_flag(char *str)
{
    int i;

    i = 0;
    if (!str || ft_strlen(str) < 2 || str[0] != '-' || str[1] != 'n')
        return (0);
    while (str[++i])
    {
        if (str[i] != 'n')
            return (0);
    }
    return (1);
}

int ft_echo(int size, char **cmdarr)
{
    int i;
    int n_flag;

    if (!cmdarr && !*cmdarr)
        return (1);
    i = 0;
    n_flag = is_n_flag(cmdarr[1]);
    while (++i < size)
    {
        if (i == 1 && n_flag == 1)
            continue ;
        echo_one_arg(cmdarr[i]);
        if (i + 1 != size)
            ft_putstr_fd(" ", STDOUT_FILENO);
    }
    if (!n_flag)
        ft_putstr_fd("\n", STDOUT_FILENO);
    return (SUCCESS);
}

// NOTES:
// echo -nnnnnnnnnnnnnnn works as just the flag

// TODO:
// echo $$ Should parsing do this?
// echo $? Parsing should do this.