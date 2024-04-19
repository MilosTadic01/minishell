/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:58:34 by mitadic           #+#    #+#             */
/*   Updated: 2024/03/26 17:43:51 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// STDIN_FILENO: no. STDOUT_FILENO: yes.
char	*ft_pwd(void)
{
	char	buff[PATH_MAX];
	char	*pwd;

	pwd = getcwd(buff, PATH_MAX);
	if (pwd == NULL)
	{
		ft_putstr_fd(strerror(errno), 2);
		return ;
	}
	return (pwd);
}

// This assumes that the parser will store the only possible option -n in the 2nd column
// Else if no option, then the argument will be in the 2nd column (strarr[1])?
// STDIN_FILENO: no. STDOUT_FILENO: yes.
void	ft_echo(char **strarr)
{
	if (!ft_strcmp(strarr[1], "-n"))
		ft_putstr_fd(strarr[2], STDOUT_FILENO);
	else
		ft_putstr_fd(strarr[1], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
}

static char *ft_cd_get_fullpath(char *dest)
{
	if (dest[0] == '.')
		if (dest[1] == '/')
			return (ft_strjoin(ft_pwd(), berta->tokens->&path[2]));
	else if (dest[0] == '/')
		;
}

// Inaccurate depiction, what we'd pass here is the row info of the Command Table,
// so we'd use something like 'berta->tokens[2]->path', but my C-fu isn't fresh
// STDIN_FILENO: no. STDOUT_FILENO: no.
void	ft_cd(char *dest)
{
	char	*fullpath;

	if (!dest)
	{
		if (getenv(HOME) < 0)
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		else if (chdir(getenv(HOME)) < 0)
			ft_putstr_fd(strerror(errno), 2);
		return ;
	}
	fullpath = ft_cd_get_fullpath(dest);
	if (chdir(fullpath) < 0)
		ft_putstr_fd(strerror(errno), 2);
}



// if u 'export PWD=<newpath>' shit goes a little haywire in bash
// Authorized: getenv. Unauthorized: putenv, setenv, unsetenv.
// STDIN_FILENO: no. STDOUT_FILENO: no.
void	ft_export(void)
{
	;
}

int	main(void)
{
	ft_putstr_fd(ft_pwd(), 2);
}