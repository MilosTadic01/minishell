/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:26:52 by daria             #+#    #+#             */
/*   Updated: 2024/05/17 11:39:25 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	receive_signals(int interactive)
{
	struct sigaction	sa;

	if (interactive)
		sa.sa_handler = sighandler_interactive;
	else
		sa.sa_handler = sighandler_prompt;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	sighandler_interactive(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		g_exit = 130;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		write(1, "\n", 1);
		g_exit = 131;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sighandler_prompt(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		g_exit = 130;
	}
	else if (signum == SIGQUIT)
	{
		write(1, "\n", 1);
		g_exit = 131;
	}
}
