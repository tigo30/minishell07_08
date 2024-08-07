/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrunho- <tgrunho-@student.42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 00:48:34 by tgrunho-          #+#    #+#             */
/*   Updated: 2024/08/06 09:34:52 by tgrunho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_equal(char *value)
{
	int	i;

	i = 0;
	while (value[i] && i < (int)ft_strlen(value))
	{
		if (value[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_home_path(void)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
		home = "/home";
	return (home);
}

int	strlenup(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

int	find_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	free_env_and_export(t_main *main)
{
	int	i;

	i = 0;
	while (main->env[i])
	{
		free(main->env[i]);
		i++;
	}
	free(main->env);
	i = 0;
	while (main->export[i])
	{
		free(main->export[i]);
		i++;
	}
	free(main->export);
}
