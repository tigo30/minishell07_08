/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrunho- <tgrunho-@student.42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:38:36 by macampos          #+#    #+#             */
/*   Updated: 2024/08/07 23:42:47 by tgrunho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <linux/fs.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/wait.h>

#define IS_ALPHA(c) (((c) >= 'A' && (c) <= 'Z') || ((c) >= 'a' && (c) <= 'z'))
#define IS_DIGIT(c) ((c) >= '0' && (c) <= '9')
#define IS_VALID_CHAR(c) (IS_ALPHA(c) || IS_DIGIT(c) || (c) == '_')

typedef struct s_main
{
	char			**env;
	char			**export;
	int				status;
	int				spaces;
	struct s_main	*next;
}					t_main;

typedef struct s_cmd
{
	int				*redirection;
	int				*redirectionpos;
	int				redirectionoverall;
	char			*path;
	char			**args;
	char			**argv2;
	char			**realarg;
	int				*spaces;
	int				fd[2];
	int				numb;
	pid_t			pid;
	struct s_cmd	*next;
	struct s_cmd	*begining;
	int				check;
}					t_cmd;

char				**ft_split3(char const *s, char c);
void				free_every_thing(t_cmd *cmd, t_main *main, int *check);
void				redirection3(t_cmd *cmd, int i, int file);
void				redirection4(t_cmd *cmd, int i, int file, t_main *main);
void				alloc_heredoc(t_cmd *cmd, char *alocated);
int					check_last_redirection(t_cmd *cmd, int i);
int					check_last_redirection2(t_cmd *cmd, int i);
void				redirection2(t_cmd *cmd, int i, int file, t_main *main);
void				redirection_1(t_cmd *cmd, int file, int i, t_main *main);
int					count_redirections(char **argv);
void				free_cmd_args(t_cmd *cmd);
char				**ft_split2(char const *s, char c);
void				closepipes(t_cmd *cmd);
void				set_comands2(t_cmd *cmd);
t_main				*execute_function(char *user_input, char **envp, t_cmd *cmd,
						t_main *main);
int					pars_args(char **cmds);
t_main				*check_builtins(t_cmd *cmd, char **envp, t_main *main,
						char *user_input);
void				cd(t_cmd *cmd, char **envp, t_main *main);
void				echo(t_cmd *cmd, t_main *main, int i, char *user_input);
void				env(t_cmd *cmd, char **envp);
t_main				*exitt(t_cmd *cmd, char **envp, t_main *main);
t_main				*export(t_cmd *cmd, char **envp, t_main *main);
void				pwd(t_cmd *cmd, char **envp);
t_main				*unset(t_cmd *cmd, t_main *main, char **envp);
t_cmd				*initiate_args(char *user_input, char **envp, t_cmd *cmd,
						t_main *main);
char				*get_paths(char *argv, char **envp);
int					check_pipes(char *user_input);
void				print_env(char **envp);
int					check_builtins2(t_cmd *cmd, char **envp, t_main *main);
int					matrixlen(char **envp);
void				free_env_and_export(t_main *main);
t_main				*set_main2(t_main *main, char **envp, char **envp2,
						char *exported);
int					*check_paired(char *exported, char **envp, char **envp2,
						int len);
int					strlenup(char *str);
int					find_equal(char *arg);
void				print_export(t_main *main);
t_main				*set_main3(t_main *main, char **envp, char **envp2,
						char *exported);
t_main				*set_main(t_main *main, char **envp);
void				signal_main(void);
int					check_equal(char *value);
char				*get_home_path(void);
int					ind_equal(char *arg);
void				free_env_and_export(t_main *main);
void				print_env_var(t_main *main, char *var);
void				print_dolar(t_main *main, char *arg);
char				*word_aloc(char const *str, char c);
char				*word_aloc3(char const *str, char c);
int					count_dif_redirections(char **argv);
void				check_redirections(t_cmd *cmd, char *arg, int j);
void				closeallpipes(t_cmd *cmd);
int					matrixlen(char **envp);
void				child_process(char *user_input, char **envp, t_cmd *cmd, t_main *main);

#endif