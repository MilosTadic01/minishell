#include "../../includes/minishell.h"

// static int  does_close(char *str, char c)
// {
//     int i;

//     i = -1;
//     while (str[++i])
//     {
//         if str[i] == c
//             return (1);
//     }
//     return (0);
// }

// NOTE: we're assuming that the quotes do close, bc parsing
static void print_str_with_specials(char *str, int *i)
{
    int j;
    // increment the i to update the while loop positionin echo_one_arg
}

static void print_str_without_specials(char *str, int *i, char c)
{
    int j;
}

static void echo_one_arg(char *str)
{
    int i;

    i = -1;
    while (str[++i])
    {
        if (str[i] == '$' && str[i + 1] == '\'') // && does_close(&str[i + 2], '\''
            print_str_with_specials(&str[i], &i);
        else if (str[i] == '\'')
            print_str_without_specials(&str[i], &i, '\'');
        else if (str[i] == '\"')
            print_str_without_specials(&str[i], &i, '\"');
        else
            ft_putchar(str[i]);
    }
}

void    ft_echo(char **cmdarr)
{
    int i;

    if (!cmdarr && !*cmdarr)
        return ;
    i = 0;
    while (cmdarr[++i])
    {
        echo_one_arg(cmdarr[i]);
        ft_putstr_fd(" ", STDOUT_FILENO);
    }
    if (i > 1 && )
}

// NOTES:
// echo -nnnnnnnnnnnnnnn works as just the flag

// TODO:
// echo $$ Should parsing do this?
// echo $? Parsing should do this.