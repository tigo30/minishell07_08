/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsargs_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrunho- <tgrunho-@student.42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 00:11:53 by macampos          #+#    #+#             */
/*   Updated: 2024/08/07 13:06:13 by tgrunho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pars_args(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		if (ft_strncmp(cmds[i], "|", 1) == 0)
			return (i);
		i++;
	}
	return (-1);
}

t_main	*check_builtins(t_cmd *cmd, char **envp, t_main *main, char *user_input)
{
	(void)user_input;
	if (ft_strncmp(cmd->args[0], "cd", 2) == 0 && ft_strlen(cmd->args[0]) == 2)
		cd(cmd, envp, main);
	else if (ft_strncmp(cmd->args[0], "export", 6) == 0
		&& ft_strlen(cmd->args[0]) == 6)
		main = export(cmd, envp, main);
	else if (ft_strncmp(cmd->args[0], "unset", 5) == 0
		&& ft_strlen(cmd->args[0]) == 5)
		main = unset(cmd, main, envp);
	else if (ft_strncmp(cmd->args[0], "pwd", 3) == 0
		&& ft_strlen(cmd->args[0]) == 3)
		pwd(cmd, envp);
	else if (ft_strncmp(cmd->args[0], "env", 3) == 0
		&& ft_strlen(cmd->args[0]) == 3)
		env(cmd, envp);
	else if (ft_strncmp(cmd->args[0], "exit", 4) == 0
		&& ft_strlen(cmd->args[0]) == 4)
		main = exitt(cmd, envp, main);
	else if (ft_strncmp(cmd->args[0], "echo", 4) == 0
		&& ft_strlen(cmd->args[0]) == 4)
		echo(cmd, main, 0, user_input);
	return (main);
}

int	check_pipes(char *user_input)
{
	int	i;
	int	flag;
	int	z;

	z = 0;
	flag = 1;
	i = 0;
	while (user_input[i])
	{
		if (user_input[i] == '|' && flag == 1)
			z++;
		if (user_input[i] == '"')
			flag *= -1;
		i++;
	}
	return (z);
}

int	count_redirections(char **argv)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (argv[i])
	{
		if ((ft_strncmp(argv[i], ">", 1) == 0) || (ft_strncmp(argv[i], "<",
					1) == 0) || (ft_strncmp(argv[i], "<<", 2) == 0)
			|| (ft_strncmp(argv[i], ">>", 2) == 0))
			j++;
		i++;
	}
	if (j == 0)
		return (1);
	return (j);
}

void	closeallpipes(t_cmd *cmd)
{
	while (cmd)
	{
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		cmd = cmd->next;
	}
}
