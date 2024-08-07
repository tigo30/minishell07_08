/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrunho- <tgrunho-@student.42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:41:30 by macampos          #+#    #+#             */
/*   Updated: 2024/08/06 08:46:50 by tgrunho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirection_1(t_cmd *cmd, int file, int i, t_main *main)
{
	if (ft_strlen(cmd->args[cmd->redirectionpos[i]]) > 1)
		file = open(&cmd->args[cmd->redirectionpos[i]][1],
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		file = open(cmd->args[cmd->redirectionpos[i] + 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
	{
		perror("Error opening file");
		main->status = 1;
		exit(main->status);
	}
	if (check_last_redirection(cmd, i) == 1)
		dup2(file, STDOUT_FILENO);
	close(file);
}

void	redirection2(t_cmd *cmd, int i, int file, t_main *main)
{
	if (ft_strncmp(cmd->args[0], "echo", 4) != 0)
	{
		if (ft_strlen(cmd->args[cmd->redirectionpos[i]]) > 1)
			file = open(&cmd->args[cmd->redirectionpos[i]][1], O_RDONLY, 0777);
		else
			file = open(cmd->args[cmd->redirectionpos[i] + 1], O_RDONLY, 0777);
		if (file == -1)
		{
			perror("Error opening file");
			main->status = 1;
			exit(main->status);
		}
	}
	if (ft_strlen(cmd->args[cmd->redirectionpos[i]])
		> 1 && check_last_redirection2(cmd, i) == 0)
		alloc_heredoc(cmd, &cmd->args[cmd->redirectionpos[i]][1]);
	else if (check_last_redirection2(cmd, i) == 0)
		alloc_heredoc(cmd, cmd->args[cmd->redirectionpos[i] + 1]);
}

void	redirection3(t_cmd *cmd, int i, int file)
{
	char	*input;
	char	*delimiter;
	int		len;

	input = readline("heredoc> ");
	file = open("temporary", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);
	if (file == -1)
	{
		perror("Error opening temporary file");
		exit(1);
	}
	if (ft_strlen(cmd->args[cmd->redirectionpos[i]]) > 2)
		delimiter = &cmd->args[cmd->redirectionpos[i]][2];
	else
		delimiter = cmd->args[cmd->redirectionpos[i] + 1];
	len = ft_strlen(delimiter);
	while (ft_strncmp(input, delimiter, len) != 0)
	{
		write(file, input, ft_strlen(input));
		write(file, "\n", 1);
		input = readline("heredoc> ");
	}
	close(file);
	if (check_last_redirection2(cmd, i) == 0)
		alloc_heredoc(cmd, "temporary");
}

void	process_redirection_args(t_cmd *cmd, int i, int j)
{
	while (cmd->args[cmd->redirectionpos[i] + j]
		&& cmd->args[cmd->redirectionpos[i + 1]]
		!= cmd->args[cmd->redirectionpos[i] + j])
	{
		alloc_heredoc(cmd, cmd->args[cmd->redirectionpos[i] + j]);
		j++;
	}
}

void	redirection4(t_cmd *cmd, int i, int file, t_main *main)
{
	int	j;

	if (ft_strlen(cmd->args[cmd->redirectionpos[i]])
		< 3 && cmd->args[cmd->redirectionpos[i] + 2])
		j = 2;
	else
		j = 1;
	process_redirection_args(cmd, i, j);
	if (ft_strlen(cmd->args[cmd->redirectionpos[i]]) > 2)
		file = open(&cmd->args[cmd->redirectionpos[i]][2],
				O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		file = open(cmd->args[cmd->redirectionpos[i] + 1],
				O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (file == -1)
	{
		perror("Error opening file");
		main->status = 1;
		exit(main->status);
	}
	dup2(file, STDOUT_FILENO);
	close(file);
}
