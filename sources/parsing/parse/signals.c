/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daria <daria@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:26:52 by daria             #+#    #+#             */
/*   Updated: 2024/05/19 16:45:29 by daria            ###   ########.fr       */
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
	sigaction(SIGQUIT, &sa, NULL);
}

void receive_signals_noninteractive(void)
{
	struct sigaction	sa;

	sa.sa_handler = sighandler_noninteractive;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void sighandler_noninteractive(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		g_exit = 130;
	}
}

/*void	receive_signals_prompt(int child)
{
	struct sigaction	sa;

	if (child)
		sa.sa_handler = sighandler_prompt_child;
	else
		sa.sa_handler = sighandler_prompt_parent;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}*/

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

/*void	sighandler_prompt_child(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		exit(130);
	}
	else if (signum == SIGQUIT)
	{
		write(1, "\n", 1);
		exit(131);
	}
}

void	sighandler_prompt_parent(int signum)
{
	return ;
}*/