/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:08:39 by hmoukit          #+#    #+#             */
/*   Updated: 2024/11/30 18:41:25 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <signal.h>
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../includes/expander.h"

// the main structure of the program
typedef struct s_minishell
{
	char		*pwd;
	char		*oldpwd;
	char		*home;
	char		**args;
	t_exp		*exp;
	t_parser	*ast;
	t_token		*tokens;
}				t_minishell;

// execution of commands functions
void	handle_exec_simple_cmd(t_minishell *node, t_parser *ast, int check);
int		execute_builtins(t_minishell *mini);
int		fork_and_exec(char *path, char **args, char **env_2d);
int		exec_simple_cmd(t_minishell *node, char **env_2d);
void	exec_no_fork(t_minishell *node, char **env_2d, char *path);
char	*get_path(char *cmd, t_minishell *mini);
int		get_exit_status(int status);
t_env	*make_env(void);
int		count_arg(t_parser *ast);
char	**make_env_2d(t_env *env);

// Builtins functions
int		ft_env(t_minishell *mini);
int		ft_echo(t_minishell *mini);
int		ft_exit(t_minishell *mini);
int		ft_pwd(t_minishell *mini);
int		ft_export(t_minishell *mini);
int		is_valid_id(char *key);
int		ft_cd(t_minishell *mini);
void	update_env(t_minishell *mini, char *key, char *new_value);
int		ft_unset(t_minishell *mini);
t_env	*ft_lstnew(void *content);
void	ft_lstadd_back(t_env **lst, t_env *new);
char	*extract_env_key(char *data);
int		is_in_env(char *key, t_env *env);
int		check_long(char *str);
int		is_str_nbr(char *str);

// redirections functions
void	handle_exec_redirections(t_minishell *mini, t_parser *node);
int		handle_input(t_parser *node);
int		handle_output(t_parser *node);
int		handle_append(t_parser *node);
int		handle_heredoc(t_parser *node, t_exp *exp);
int		open_out(t_parser *n);
int		open_append(t_parser *n);
int		type_redirection(t_minishell *mini, t_parser *node, t_red_type type);
void	find_execute_cmd(t_minishell *mini, t_parser *node);
int		open_in_files(t_minishell *mini, t_parser *node);
int		open_out_files(t_minishell *mini, t_parser *node);
int		multiple_in_redirections(t_minishell *mini, t_parser *node);
int		multiple_out_redirections(t_minishell *mini, t_parser *node);

// execution of pipelines functions
void	ft_pipelines(t_minishell *mini, t_parser *ast);
void	traverse_and_handle_heredocs(int *j, t_minishell *mini, t_parser *node);
int		handle_redirections_in_process(t_minishell *mini, t_parser *node);
int		setup_pipe(int pfds[2]);
void	wait_for_children(int pid_left, int pid_right, unsigned char *exit);

// the signal handlers
void	ft_sigint_handler_heredoc(int num);
void	ft_sigint_handler(int num);
void	ft_sigquit_handler(int num);
void	ft_eof_handler(void);

// the main function of the executer
void	executer(t_minishell *mini);

// Cleanup functions
void	free_tree(t_parser *ast);
void	free_env(t_env **env);
void	cleanup_mini(t_minishell *mini);
void	free_line(char **line);
void	free_env_node(t_env *env);

#endif