/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsargs_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrunho- <tgrunho-@student.42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 00:11:53 by macampos          #+#    #+#             */
/*   Updated: 2024/08/07 13:42:03 by tgrunho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_string_arrays(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
	i = 0;
	while (cmd->realarg[i])
	{
		free(cmd->realarg[i]);
		i++;
	}
	free(cmd->realarg);
	i = 0;
	while (cmd->argv2[i])
	{
		free(cmd->argv2[i]);
		i++;
	}
	free(cmd->argv2);
}

void	free_cmd_fields(t_cmd *cmd)
{
	free(cmd->redirection);
	free(cmd->redirectionpos);
	free(cmd->path);
}

void	free_cmd_args(t_cmd *cmd)
{
	t_cmd	*temporary;

	closeallpipes(cmd->begining);
	temporary = cmd->begining;
	while (temporary)
	{
		cmd = temporary;
		free_string_arrays(cmd);
		free_cmd_fields(cmd);
		temporary = cmd->next;
		free(cmd);
	}
}

int	count_dif_redirections(char **argv)
{
	int	i;
	int	a;
	int	b;

	b = 0;
	a = 0;
	i = 0;
	while (argv[i])
	{
		if (ft_strncmp(argv[i], "<<", 2) == 0 && argv[i][2] != ' ')
			return (2);
		if ((ft_strncmp(argv[i], ">", 1) == 0 && argv[i][1] != ' ')
			|| (ft_strncmp(argv[i], ">>", 2) == 0 && argv[i][2] != ' '))
			a = 1;
		if (ft_strncmp(argv[i], "<", 1) == 0 && argv[i][1] != ' ')
			b = 1;
		i++;
	}
	return (a + b);
}
