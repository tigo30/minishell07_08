/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsargs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrunho- <tgrunho-@student.42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 00:11:53 by macampos          #+#    #+#             */
/*   Updated: 2024/08/07 18:01:40 by tgrunho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*set_comands(char *argv, char **envp, t_cmd *cmd, t_main *main)
{
	int		i;
	int		j;
	int		*place;
	char	**path2;
	t_cmd	*cmd2;
	t_cmd	*begin;

	i = 0;
	cmd2 = NULL;
	path2 = ft_calloc(sizeof(char *), 2);
	path2[0] = ft_strdup("PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	(void)envp;
	if (cmd)
		free_cmd_args(cmd);
	cmd2 = ft_calloc(sizeof(t_cmd), sizeof(t_cmd));
	cmd2->argv2 = ft_split(argv, '\4');
	while (cmd2->argv2[i])
	{
		j = 0;
		cmd2->args = ft_split3(cmd2->argv2[i], '\3');
		cmd2->realarg = ft_split2(cmd2->argv2[i], '\3');
		cmd2->redirection = ft_calloc(sizeof(int),
				count_redirections(cmd2->args));
		cmd2->redirectionpos = ft_calloc(sizeof(int),
				count_redirections(cmd2->args));
		cmd2->redirectionoverall = count_dif_redirections(cmd2->args);
		while (cmd2->args[j])
		{
			check_redirections(cmd2, cmd2->args[j], j);
			j++;
		}
		place = check_paired("PATH=", main->env, main->export, 5);
		if (place[1] == -1)
			cmd2->path = get_paths(cmd2->args[0], path2);
		else
			cmd2->path = get_paths(cmd2->args[0], envp);
		free(place);
		if (i == 0)
			begin = cmd2;
		cmd2->begining = begin;
		set_comands2(cmd2);
		if (cmd2->argv2[i + 1])
		{
			cmd2->next = ft_calloc(sizeof(t_cmd), sizeof(t_cmd));
			cmd2->next->argv2 = ft_split(argv, '\4');
			cmd2 = cmd2->next;
		}
		i++;
	}
	free(path2[0]);
	free(path2);
	free(argv);
	return (cmd2->begining);
}

void	process_charact(const char *user_input, char *argv, int *flag, int *j)
{
	int	i;

	i = 0;
	while (user_input[i])
	{
		if ((user_input[i] == '"' || user_input[i] == 39) && *flag == -1)
			*j = i;
		if ((user_input[i] == '"' || user_input[i] == 39)
			&& user_input[i] == user_input[*j])
		{
			*j = i;
			*flag *= -1;
		}
		if (*flag == -1 && user_input[i] == '|')
			argv[i] = '\4';
		else if (*flag == -1 && user_input[i] == ' ')
			argv[i] = '\3';
		else if ((*flag == -1 && (user_input[i] == '"' || user_input[i] == 39))
			|| ((user_input[i] == '"' || user_input[i] == 39) && *j == i))
			argv[i] = '\5';
		else if ((*flag == -1 && user_input[i] != ' ') || *flag == 1)
			argv[i] = user_input[i];
		i++;
	}
}

t_cmd	*initiate_args(char *user_input, char **envp, t_cmd *cmd, t_main *main)
{
	int		flag;
	int		j;
	char	*argv;

	flag = -1;
	j = 0;
	argv = ft_calloc(sizeof(char), ft_strlen(user_input) + 1);
	process_charact(user_input, argv, &flag, &j);
	if (flag == 1)
	{
		printf("unclosed argument\n");
		free(argv);
		return (NULL);
	}
	return (set_comands(argv, envp, cmd, main));
}
//argv = "echo\5Hello\3|\5test\3|\4grep\3test"
