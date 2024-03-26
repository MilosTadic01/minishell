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

// Inaccurate depiction, what we'd pass here is the row info of the Command Table,
// so we'd use something like 'berta->tokens[2]->path', but my C-fu isn't fresh
// STDIN_FILENO: no. STDOUT_FILENO: no.
void	ft_cd(t_berta *berta)
{
	if (!berta->tokens->path)
		return ;
	if (berta->tokens->path[0] == '.')
		chdir(ft_strjoin(berta->envp->PWD, berta->tokens->&path[2]));
	else
		chdir(berta->tokens->path);
}


// STDIN_FILENO: no. STDOUT_FILENO: yes.
void	ft_pwd(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (!strncmp(envp[i], "PWD=", 4))
			ft_putstr_fd(&envp[i][4], STDOUT_FILENO);
	}
}

// if u 'export PWD=<newpath>' shit goes a little haywire in bash
// Authorized: getenv. Unauthorized: putenv, setenv, unsetenv.
// STDIN_FILENO: no. STDOUT_FILENO: no.
void	ft_export(void)
{
}
