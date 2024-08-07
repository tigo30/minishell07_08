/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting_shell_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrunho- <tgrunho-@student.42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:53:21 by macampos          #+#    #+#             */
/*   Updated: 2024/08/07 20:57:22 by tgrunho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_paths(char **paths, char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	*get_paths(char *argv, char **envp)
{
	int		i;
	char	**paths;
	char	*path;
	char	**cmd;

	if (!envp)
		return (NULL);
	cmd = ft_split(argv, ' ');
	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path, cmd[0]);
		if (access(path, X_OK) == 0)
		{
			free_paths(paths, cmd);
			return (path);
		}
		free(path);
	}
	free_paths(paths, cmd);
	return (NULL);
}

void	closepipes(t_cmd *cmd)
{
	if (cmd->fd[1] != 1 && cmd->fd[1] != 0)
		close(cmd->fd[1]);
	if (cmd->fd[0] != 1 && cmd->fd[0] != 0)
		close(cmd->fd[0]);
}

void	alloc_heredoc(t_cmd *cmd, char *alocated)
{
	char	**new;
	int		i;

	i = 0;
	new = ft_calloc(sizeof(char *), matrixlen(cmd->realarg) + 2);
	while (cmd->realarg[i])
	{
		new[i] = cmd->realarg[i];
		i++;
	}
	new[i] = ft_strdup(alocated);
	free(cmd->realarg);
	cmd->realarg = new;
}

int	matrixlen(char **envp)
{
	int	j;

	j = 0;
	while (envp[j])
	{
		j++;
	}
	return (j);
}
