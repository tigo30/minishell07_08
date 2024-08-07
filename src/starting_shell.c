/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrunho- <tgrunho-@student.42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:53:21 by macampos          #+#    #+#             */
/*   Updated: 2024/08/08 00:03:12 by tgrunho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_last_redirection2(t_cmd *cmd, int i)
{
	i += 1;
	if (i < count_redirections(cmd->args))
	{
		while (i < count_redirections(cmd->args))
		{
			if (cmd->redirection[i] && (cmd->redirection[i] == 2
					|| cmd->redirection[i] == 3))
				return (1);
			i++;
		}
	}
	return (0);
}

int	check_last_redirection(t_cmd *cmd, int i)
{
	int	j;

	j = i + 1;
	if (j < count_redirections(cmd->args))
	{
		while (j < count_redirections(cmd->args))
		{
			if (cmd->redirection[j] == 1 || cmd->redirection[j] == 4)
				return (-1);
			j++;
		}
	}
	return (1);
}

void	aplly_redirections(t_cmd *cmd, t_main *main)
{
	int	file;
	int	i;

	i = 0;
	file = 0;
	while (i < count_redirections(cmd->args))
	{
		if (cmd->redirection[i] == 2)
			redirection2(cmd, i, file, main);
		else if (cmd->redirection[i] == 3)
			redirection3(cmd, i, file);
		i++;
	}
	i = 0;
	while (i < count_redirections(cmd->args))
	{
		if (cmd->redirection[i] == 1)
			redirection_1(cmd, file, i, main);
		else if (cmd->redirection[i] == 4)
			redirection4(cmd, i, file, main);
		i++;
	}
}

char	*get_full_path(char *cmd, char **paths)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths && paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(full_path, cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

void	child_process(char *user_input, char **envp, t_cmd *cmd, t_main *main)
{
	int		status;
	char	**a;
	char	*b;
	int		*check;
	int		*check2;

	check2 = check_paired(&cmd->args[0][1], main->env, main->export,
			ft_strlen(&cmd->args[0][1]));
	check = check_paired("PATH=", main->env, main->export, 5);
	b = NULL;
	a = NULL;
	if (cmd->argv2[1])
	{
		if (cmd == cmd->begining)
		{
			dup2(cmd->next->fd[1], STDOUT_FILENO);
			aplly_redirections(cmd, main);
			closepipes(cmd);
		}
		else if (cmd->next == NULL)
		{
			dup2(cmd->fd[0], STDIN_FILENO);
			aplly_redirections(cmd, main);
			closepipes(cmd);
		}
		else if (cmd->next && cmd != cmd->begining)
		{
			dup2(cmd->fd[0], STDIN_FILENO);
			dup2(cmd->next->fd[1], STDOUT_FILENO);
			aplly_redirections(cmd, main);
			closepipes(cmd);
		}
	}
	else
		aplly_redirections(cmd, main);
	if (cmd->args[0][0] == '$' && check2[0] != -1)
	{
		if (get_paths(&main->env[check2[0]][find_equal(main->env[check2[0]])
				+ 1], main->env))
		{
			execve(get_paths(&main->env[check2[0]][find_equal(main->env[check2[0]])
					+ 1], main->env),
				ft_split(&main->env[check2[0]][find_equal(main->env[check2[0]])
					+ 1], ' '), main->env);
		}
		if (check2[0] != -1)
		{
			printf("command not found: %s\n",
				&main->env[check2[0]][find_equal(main->env[check2[0]]) + 1]);
			free_every_thing(cmd, main, check);
			free(check2);
			exit(-1);
		}
	}
	free(check2);
	if (check_builtins2(cmd, envp, main) == 1 && check[0] == -1)
	{
		execve(b, cmd->realarg, envp);
		write(2, " No such file or directory\n", 28);
		status = 127;
		free_every_thing(cmd, main, check);
	}
	if (check_builtins2(cmd, envp, main) == 1 && check[0] != -1)
	{
		if (ft_strncmp(cmd->args[0], "./minishell", 11) != 0)
		{
			if (cmd->realarg[0][0] == '/')
				execve(cmd->realarg[0], cmd->realarg, envp);
			execve(cmd->path, cmd->realarg, envp);
			if (ft_strncmp(cmd->args[0], "./", 2) == 0)
			{
				write(2, " No such file or directory\n", 28);
				status = 126;
				free_every_thing(cmd, main, check);
				exit(status);
			}
			if (ft_strncmp(cmd->args[0], "/", 1) == 0)
				write(2, " No such file or directory\n", 28);
			else if (cmd->args[0][0] == '$' && cmd->args[1]
				&& check_paired(cmd->args[0], main->env, main->export,
					ft_strlen(cmd->args[0]) - 1)[0] == -1)
				execve(cmd->path, &cmd->args[1], envp);
			else
				write(2, " command not found\n", 19);
			status = 127;
			free_every_thing(cmd, main, check);
			exit(status);
		}
		else
		{
			execve("./minishell", a, envp);
			printf("%s\n", strerror(errno));
		}
	}
	check_builtins(cmd, envp, main, user_input);
	free_every_thing(cmd, main, check);
	exit(0);
}
