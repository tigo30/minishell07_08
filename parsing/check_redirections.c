/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrunho- <tgrunho-@student.42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 00:11:53 by macampos          #+#    #+#             */
/*   Updated: 2024/08/07 13:19:10 by tgrunho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_redirection_greater(t_cmd *cmd, int j)
{
	int	i;

	i = 0;
	while (i < count_redirections(cmd->args))
	{
		if (cmd->redirection[i] == 0)
		{
			cmd->redirection[i] = 1;
			break ;
		}
		i++;
	}
	cmd->redirectionpos[i] = j;
}

void	handle_redirection_less(t_cmd *cmd, int j)
{
	int	i;

	i = 0;
	while (i < count_redirections(cmd->args))
	{
		if (cmd->redirection[i] == 0)
		{
			cmd->redirection[i] = 2;
			break ;
		}
		i++;
	}
	cmd->redirectionpos[i] = j;
}

void	handle_redirection_heredoc(t_cmd *cmd, int j)
{
	int	i;

	i = 0;
	while (i < count_redirections(cmd->args))
	{
		if (cmd->redirection[i] == 0)
		{
			cmd->redirection[i] = 3;
			break ;
		}
		i++;
	}
	cmd->redirectionpos[i] = j;
}

void	handle_redirection_append(t_cmd *cmd, int j)
{
	int	i;

	i = 0;
	while (i < count_redirections(cmd->args))
	{
		if (cmd->redirection[i] == 0)
		{
			cmd->redirection[i] = 4;
			break ;
		}
		i++;
	}
	cmd->redirectionpos[i] = j;
}

void	check_redirections(t_cmd *cmd, char *arg, int j)
{
	if (ft_strncmp(arg, ">", 1) == 0 && arg[1] != '>')
	{
		handle_redirection_greater(cmd, j);
	}
	else if (ft_strncmp(arg, "<", 1) == 0 && arg[1] != '<')
	{
		handle_redirection_less(cmd, j);
	}
	else if (ft_strncmp(arg, "<<", 2) == 0)
	{
		handle_redirection_heredoc(cmd, j);
	}
	else if (ft_strncmp(arg, ">>", 2) == 0)
	{
		handle_redirection_append(cmd, j);
	}
}
