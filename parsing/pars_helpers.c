/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrunho- <tgrunho-@student.42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 00:59:17 by macampos          #+#    #+#             */
/*   Updated: 2024/08/06 23:43:12 by tgrunho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_comands2(t_cmd *cmd)
{
	if (pipe(cmd->fd) == -1)
		return ;
}

void	set_env(t_main *mainn, char **envp, int *place, char *exported)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	mainn->env = ft_calloc(matrixlen(envp) + 2, sizeof(char *));
	while (envp[j])
	{
		if (j != place[0] || find_equal(exported) == -1)
		{
			mainn->env[i] = ft_strdup(envp[j]);
			i++;
		}
		else if (j == place[0] && find_equal(exported) > 0)
		{
			mainn->env[i] = ft_strdup(exported);
			i++;
		}
		j++;
	}
	if (find_equal(exported) > 0 && place[0] == -1)
		mainn->env[i] = ft_strdup(exported);
}

void	set_export(t_main *mainn, char **envp2, int *place, char *exported)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	mainn->export = ft_calloc(matrixlen(envp2) + 2, sizeof(char *));
	while (envp2[j])
	{
		if (j != place[1])
		{
			mainn->export[i] = ft_strdup(envp2[j]);
			i++;
		}
		else
		{
			mainn->export[i] = ft_strdup(exported);
			i++;
		}
		j++;
	}
	if (place[1] == -1)
		mainn->export[i] = ft_strdup(exported);
}

t_main	*set_main2(t_main *main, char **envp, char **envp2, char *exported)
{
	int		*place;
	t_main	*mainn;

	place = check_paired(exported, envp, envp2, strlenup(exported));
	mainn = ft_calloc(1, sizeof(t_main));
	set_env(mainn, envp, place, exported);
	set_export(mainn, envp2, place, exported);
	free(main->env);
	free(main->export);
	free(main);
	free(place);
	return (mainn);
}

t_main	*set_main3(t_main *main, char **envp, char **envp2, char *exported)
{
	int		*place;
	t_main	*mainn;

	place = check_paired(exported, envp, envp2, strlenup(exported));
	mainn = ft_calloc(1, sizeof(t_main));
	set_env(mainn, envp, place, exported);
	set_export(mainn, envp2, place, exported);
	if (place[0] != -1)
		free(main->env[place[0]]);
	if (place[1] != -1)
		free(main->export[place[1]]);
	free(main->env);
	free(main->export);
	free(main);
	free(place);
	return (mainn);
}
