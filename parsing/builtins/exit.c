/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrunho- <tgrunho-@student.42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:04:19 by macampos          #+#    #+#             */
/*   Updated: 2024/08/05 11:23:04 by tgrunho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"//

void	free_args(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
}

void	handle_invalid_argument(t_cmd *cmd, t_main *main, char *truearg)
{
	int	exit_status;

	free(truearg);
	if (!ft_atoi(cmd->args[1]) && !cmd->args[2])
	{
		main->status = 2;
		write(2, "numeric argument required\n", 27);
	}
	else if (cmd->args[1] && ft_strchr(cmd->args[1], '-'))
	{
		main->status = -100;
		write(2, "numeric argument required\n", 27);
	}
	else if (cmd->args[1])
	{
		main->status = 100;
		write(2, "numeric argument required\n", 27);
	}
	exit_status = main->status;
	free_env_and_export(main);
	free(main);
	free_cmd_args(cmd);
	exit(exit_status);
}

void	handle_too_many_arguments(t_main *main, char *truearg)
{
	main->status = 1;
	write(2, "too many arguments\n", 20);
	free(truearg);
}

void	handle_valid_argument(t_cmd *cmd, t_main *main, char *truearg)
{
	int	exit_status;

	if (cmd->args[1])
		free(truearg);
	free_env_and_export(main);
	exit_status = 0;
	if (cmd->args[1])
		exit_status = (unsigned char)ft_atoi(cmd->args[1]);
	free(main);
	free_cmd_args(cmd);
	exit(exit_status);
}

t_main	*exitt(t_cmd *cmd, char **envp, t_main *main)
{
	char	*truearg;

	(void)envp;
	if (cmd->args[1])
		truearg = ft_itoa(ft_atoi(cmd->args[1]));
	if (!cmd->args[1] || ft_strncmp(truearg, cmd->args[1],
			ft_strlen(cmd->args[1])) == 0)
	{
		if (cmd->args[1] && cmd->args[2])
		{
			handle_too_many_arguments(main, truearg);
			return (main);
		}
		handle_valid_argument(cmd, main, truearg);
	}
	else
		handle_invalid_argument(cmd, main, truearg);
	return (main);
}
