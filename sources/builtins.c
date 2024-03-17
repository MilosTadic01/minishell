/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitadic <mitadic@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:58:34 by mitadic           #+#    #+#             */
/*   Updated: 2024/03/17 18:13:31 by mitadic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_cat

// Inaccurate depiction, what we'd pass here is the row info of the Command Table,
// so we'd use something like 'berta->tokens[2]->path', but my C-fu isn't fresh
void	ft_cd(t_berta *berta)
{
	if (!berta->tokens->path)
		return ;
	if (berta->tokens->path[0] == '.')
		chdir(ft_strjoin(berta->envp->PWD, berta->tokens->&path[2]));
	else
		chdir(berta->tokens->path);
}
