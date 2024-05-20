/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:26:52 by daria             #+#    #+#             */
/*   Updated: 2024/05/20 16:58:49 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	receive_signals_interactive(void)
{
	struct sigaction	sa;

	sa.sa_handler = sighandler_interactive;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	receive_signals_noninteractive(void)
{
	struct sigaction	sa;

	sa.sa_handler = sighandler_noninteractive;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

void	sighandler_noninteractive(int signum)
{
	g_exit = 128 + signum;
	write(1, "\n", 1);
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
}
