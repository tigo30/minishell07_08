/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrunho- <tgrunho-@student.42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:58:47 by macampos          #+#    #+#             */
/*   Updated: 2024/08/05 12:07:58 by tgrunho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env_var(t_main *main, char *var)
{
	int	i;

	i = 0;
	while (main->env[i])
	{
		if (ft_strncmp(var, main->env[i],
				ft_strlen(var)) == 0 && main->env[i]
			[ft_strlen(var)] == '=' && check_equal(var) == -1)
		{
			printf("%s", &main->env[i][ft_strlen(var) + 1]);
			break ;
		}
		i++;
	}
}

void	print_dolar(t_main *main, char *arg)
{
	int		i;
	char	**value;

	i = 1;
	value = ft_split(arg, ' ');
	if (!arg[0] || arg[0] == ' ')
	{
		printf("$");
		return ;
	}
	if (arg[0] == '?')
	{
		printf("%i", main->status);
		while (arg[i] && arg[i] != ' ')
			printf("%c", arg[i++]);
	}
	else
		print_env_var(main, value[0]);
}
