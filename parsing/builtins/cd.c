/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrunho- <tgrunho-@student.42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:03:45 by macampos          #+#    #+#             */
/*   Updated: 2024/08/05 09:30:08 by tgrunho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	validate_arguments(t_cmd *cmd)
{
	if (cmd->args[2])
	{
		write(2, "too many arguments\n", 20);
		return (1);
	}
	return (0);
}

char	*get_directory(t_cmd *cmd)
{
	char	*dir;

	if (!cmd->args[1] || ft_strncmp(cmd->args[1], "~", 1) == 0)
		dir = get_home_path();
	else if (cmd->args[1][0] == '$')
	{
		dir = getenv(cmd->args[1] + 1);
		if (!dir)
		{
			write(2, "no such file or directory\n", 27);
			return (NULL);
		}
	}
	else
		dir = cmd->args[1];
	return (dir);
}

void	update_env_pwd(char *cwd, t_main *main)
{
	int	i;

	i = 0;
	while (main->env[i])
	{
		if (strncmp(main->env[i], "PWD=", 4) == 0)
		{
			free(main->env[i]);
			main->env[i] = malloc(strlen("PWD=") + strlen(cwd) + 1);
			sprintf(main->env[i], "PWD=%s", cwd);
			break ;
		}
		i++;
	}
}

void	change_directory_and_update_env(char *dir, t_main *main)
{
	char	cwd[1024];

	if (chdir(dir) == -1)
	{
		main->status = 1;
		write(2, "no such file or directory\n", 27);
	}
	else
	{
		main->status = 0;
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			update_env_pwd(cwd, main);
	}
}

void	cd(t_cmd *cmd, char **envp, t_main *main)
{
	char	*dir;

	(void)envp;
	if (validate_arguments(cmd))
	{
		main->status = 1;
		return ;
	}
	dir = get_directory(cmd);
	if (!dir)
	{
		main->status = 1;
		return ;
	}
	change_directory_and_update_env(dir, main);
}
