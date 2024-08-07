/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrunho- <tgrunho-@student.42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:04:24 by macampos          #+#    #+#             */
/*   Updated: 2024/08/05 11:01:44 by tgrunho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	*check_paired(char *exported, char **envp, char **envp2, int len)
{
	int	*place;
	int	i;

	i = 0;
	place = ft_calloc(3, sizeof(int));
	place[0] = -1;
	place[1] = -1;
	while (envp[i] || envp2[i])
	{
		if (envp[i] && place[0] == -1 && ft_strncmp(envp[i],
				exported, len) == 0)
			place[0] = i;
		if (envp2[i] && place[1] == -1 && ft_strncmp(envp2[i],
				exported, len) == 0)
			place[1] = i;
		++i;
	}
	return (place);
}

int	check_invalid(char *arg)
{
	int	i;

	i = 1;
	if (!(IS_ALPHA(arg[0]) || arg[0] == '_'))
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (!IS_VALID_CHAR(arg[i]))
			return (i);
		i++;
	}
	return (-1);
}

t_main	*export(t_cmd *cmd, char **envp, t_main *main)
{
	t_main	*next;
	int		i;

	i = 1;
	(void)envp;
	next = main;
	if (!cmd->args[1])
	{
		print_export(main);
		return (main);
	}
	while (cmd->args[i])
	{
		if (check_invalid(cmd->args[i]) != -1 || cmd->args[i][0] == '=')
		{
			write(2, "not a valid identifier\n", 24);
			main->status = 1;
			return (next);
		}
		else if (check_invalid(cmd->args[i]) == -1)
			next = set_main2(next, next->env, next->export, cmd->args[i]);
		i++;
	}
	return (next);
}
