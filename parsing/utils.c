/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrunho- <tgrunho-@student.42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 23:35:51 by macampos          #+#    #+#             */
/*   Updated: 2024/08/06 09:38:38 by tgrunho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_builtins2(t_cmd *cmd, char **envp, t_main *main)
{
	(void)main;
	(void)envp;
	if (ft_strncmp(cmd->args[0], "cd", 2) == 0 || ft_strncmp(cmd->args[0],
			"export", 6) == 0 || ft_strncmp(cmd->args[0], "pwd", 3) == 0
		|| ft_strncmp(cmd->args[0], "env", 3) == 0 || ft_strncmp(cmd->args[0],
			"exit", 4) == 0 || ft_strncmp(cmd->args[0], "echo", 4) == 0
		|| ft_strncmp(cmd->args[0], "unset", 5) == 0)
		return (0);
	else
		return (1);
}

int	check_last(t_main *main)
{
	int	i;
	int	n;
	int	z;

	n = 0;
	i = 0;
	while (main->export[i])
	{
		if (strlenup(main->export[i])
			> strlenup(main->export[n]))
			z = strlenup(main->export[n]);
		else
			z = strlenup(main->export[i]);
		if (ft_strncmp(main->export[i], main -> export[n], z) > 0)
			n = i;
		i++;
	}
	return (n);
}

int	find_next_export(t_main *main, int a, int c)
{
	int	i;
	int	n;
	int	z;

	i = 0;
	n = check_last(main);
	while (main->export[i])
	{
		if (strlenup(main->export[i]) > strlenup(main->export[n]))
			z = strlenup(main->export[n]);
		else
			z = strlenup(main->export[i]);
		if (a == 0 && ft_strncmp(main->export[i], main->export[n], z) < 0)
			n = i;
		else if (a > 0 && ft_strncmp(main->export[i],
				main->export[c], strlenup(main->export[i])) > 0)
		{
			if (ft_strncmp(main->export[i], main->export[n], z) < 0
				|| (ft_strncmp(main->export[i], main->export[n], z) == 0
					&& strlenup(main->export[i]) != strlenup(main->export[n])))
				n = i;
		}
		i++;
	}
	return (n);
}

void	print_export(t_main *main)
{
	int	a;
	int	c;
	int	n;

	a = 0;
	c = 0;
	while (matrixlen(main->export) > a + 1)
	{
		n = find_next_export(main, a, c);
		printf("declare -x %s\n", main->export[n]);
		c = n;
		a++;
	}
}

char	*word_aloc3(char const *str, char c)
{
	char	*word;
	int		word_len;
	int		ctd;
	int		ctd2;
	int		i;

	i = 0;
	ctd = 0;
	ctd2 = 0;
	word_len = 0;
	while (str[i] && str[i] != c)
	{
		if (str[i] != '\5')
			word_len++;
		i++;
	}
	word = (char *)malloc(word_len + 1);
	while (ctd < word_len)
	{
		while (str[ctd2] == '\5')
			ctd2++;
		word[ctd++] = str[ctd2++];
	}
	word[ctd] = '\0';
	return (word);
}
