/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrunho- <tgrunho-@student.42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:51:11 by macampos          #+#    #+#             */
/*   Updated: 2024/08/06 09:38:32 by tgrunho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrlc_signal(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_main(void)
{
	signal(SIGINT, ctrlc_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	free_every_thing(t_cmd *cmd, t_main *main, int *check)
{
	free_cmd_args(cmd);
	free_env_and_export(main);
	free(main);
	free(check);
}
