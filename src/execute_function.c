/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrunho- <tgrunho-@student.42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:53:21 by macampos          #+#    #+#             */
/*   Updated: 2024/08/07 23:57:01 by tgrunho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	last_reversed(t_cmd *cmd, int flag)
{
	int	i;
	int	j;

	j = -2;
	i = 0;
	{
		while (i < count_redirections(cmd->args))
		{
			if (cmd->redirection[i] == 3 || cmd->redirection[i] == 2)
			{
				j = i;
				if (cmd->redirection[i] == 3 && i > flag)
					return (j);
			}
			i++;
		}
	}
	return (j);
}

t_main	*execute_function(char *user_input, char **envp, t_cmd *cmd, t_main *main)
{
	pid_t	id;

	if (!cmd->args[0] || cmd->args[0][0] == '$')
	{
		write(2, "command not found\n", 19);
		main->status = 127;
		return (main);
	}
	if (cmd->next || check_builtins2(cmd, envp, main) == 1
		|| cmd->redirectionoverall != 0)
	{
		while (cmd)
		{
			if (cmd->next == NULL && ft_strncmp(cmd->args[0], "export", 6) == 0)
			{
				closepipes(cmd);
				return (export(cmd, envp, main));
			}
			else if (cmd->next == NULL && ft_strncmp(cmd->args[0], "unset", 5) == 0)
			{
				closepipes(cmd);
				return (unset(cmd, main, envp));
			}
			else if (cmd->next == NULL && ft_strncmp(cmd->args[0], "exit", 4) == 0)
			{
				closepipes(cmd);
				return (exitt(cmd, envp, main));
			}
			else
			{
				id = fork();
				if (id == -1)
					return (main);
				if (id == 0)
				{
					child_process(user_input, envp, cmd, main);
				}
				if (cmd->redirectionoverall == 2)
					waitpid(id, &main->status, 0);
				closepipes(cmd);
			}
			cmd = cmd->next;
		}
	}
	else
		main = check_builtins(cmd, envp, main, user_input);
	while (waitpid(-1, &main->status, 0) != -1)
		;
	if (WIFEXITED(main->status))
		main->status = WEXITSTATUS(main->status);
	return (main);
}

// t_main	*execute_function(char *user_input, char **envp, t_cmd *cmd,
// 		t_main *main)
// {
// 	pid_t	id;

// 	if (cmd->next || check_builtins2(cmd, envp, main) == 1
// 		|| cmd->redirectionoverall != 0)
// 	{
// 		while (cmd)
// 		{
// 			if (cmd->next == NULL && ft_strncmp(cmd->args[0], "export", 6) == 0)
// 			{
// 				closepipes(cmd);
// 				return (export(cmd, envp, main));
// 			}
// 			else if (cmd->next == NULL && ft_strncmp(cmd->args[0], "unset",
// 					5) == 0)
// 			{
// 				closepipes(cmd);
// 				return (unset(cmd, main, envp));
// 			}
// 			else if (cmd->next == NULL && ft_strncmp(cmd->args[0], "exit",
// 					4) == 0)
// 			{
// 				closepipes(cmd);
// 				return (exitt(cmd, envp, main));
// 			}
// 			else
// 			{
// 				id = fork();
// 				if (id == -1)
// 					return (main);
// 				if (id == 0)
// 					child_process(user_input, envp, cmd, main);
// 				if (cmd->redirectionoverall == 2)
// 				{
// 					while (waitpid(id, &main->status, 0) != -1)
// 						;
// 				}
// 				closepipes(cmd);
// 			}
// 			cmd = cmd->next;
// 		}
// 	}
// 	else
// 		main = check_builtins(cmd, envp, main, user_input);
// 	while (waitpid(-1, &main->status, 0) != -1)
// 		;
// 	if (WIFEXITED(main->status))
// 		main->status = WEXITSTATUS(main->status);
// 	return (main);
// }