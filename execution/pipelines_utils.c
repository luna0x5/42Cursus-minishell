/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:35:37 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/10 06:48:24 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_redirections_in_process(t_minishell *mini, t_parser *node)
{
	if (!multiple_in_redirections(mini, node))
		return (0);
	if (!multiple_out_redirections(mini, node))
		return (0);
	find_execute_cmd(mini, node);
	return (1);
}

int	setup_pipe(int pfds[2])
{
	if (pipe(pfds) == -1)
	{
		perror("SHELL: pipe");
		return (-1);
	}
	return (0);
}

void	wait_for_children(int pid_left, int pid_right, unsigned char *exit)
{
	int	status;

	status = 0;
	waitpid(pid_left, &status, 0);
	waitpid(pid_right, &status, 0);
	*exit = get_exit_status(status);
}

void	handle_fork(int pid, t_minishell *mini, t_parser *node, int j)
{
	int		status;

	status = 0;
	if (pid == 0)
	{
		if (!handle_heredoc(node, mini->exp))
			exit(1);
		if (node->left && node->left->id->id_type == CMD && !j)
			handle_exec_simple_cmd(mini, node->left, 1);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		get_exit_status(status);
		mini->exp->exit_s = status;
	}
}

void	traverse_and_handle_heredocs(int *j, t_minishell *mini, t_parser *node)
{
	pid_t	pid;

	if (!node)
		return ;
	if (node->id->id_type == REDIRECTION && node->io_type == HEREDOC)
	{
		(*j)--;
		printf("======= %d\n", *j);
		pid = fork();
		if (pid == -1)
		{
			perror("SHELL: heredoc: Failed to fork");
			return ;
		}
		handle_fork(pid, mini, node, *j);
	}
	traverse_and_handle_heredocs(j, mini, node->left);
	traverse_and_handle_heredocs(j, mini, node->right);
}
