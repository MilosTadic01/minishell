#include "../../includes/minishell.h"

ft_exit(char **strarr)
{
    unsigned char custom_status;

    if (!strarr || !strarr[0]) // segfault?
        exit(errno);
    // check that strarr[0] is a numeric, else perror("minishell: exit: <strarr[0]>: {numeric argument required | 2}") then exit(errno)
    // check that there are no more than 1 args, else perror("minishell: exit: {too many arguments | 1}") then exit(errno)
    if (strarr[0] && !strarr[1]) // segfault @ [1]?
        exit(custom_status);
}