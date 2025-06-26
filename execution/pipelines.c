/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:23:59 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/01 11:05:22 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_left_child(t_minishell *mini, int pfds[2], t_parser *left)
{
	close(pfds[0]);
	if (dup2(pfds[1], STDOUT_FILENO) == -1)
	{
		perror("SHELL: dup2 left");
		exit(1);
	}
	close(pfds[1]);
	mini->ast = left;
	if (mini->ast->id->id_type == REDIRECTION && mini->ast->io_type != HEREDOC)
	{
		if (!handle_redirections_in_process(mini, mini->ast))
			exit(1);
	}
	else if (mini->ast && mini->ast->id->id_type == CMD)
		handle_exec_simple_cmd(mini, mini->ast, 1);
	else if (mini->ast->id->id_type == PIPELINE)
		ft_pipelines(mini, mini->ast);
	exit(mini->exp->exit_s);
}

void	execute_right_child(t_minishell *mini, int pfds[2], t_parser *right)
{
	close(pfds[1]);
	if (dup2(pfds[0], STDIN_FILENO) == -1)
	{
		perror("SHELL: dup2 right");
		exit(1);
	}
	close(pfds[0]);
	mini->ast = right;
	if (mini->ast->id->id_type == REDIRECTION && mini->ast->io_type != HEREDOC)
	{
		if (!handle_redirections_in_process(mini, mini->ast))
			exit(1);
	}
	else if (mini->ast && mini->ast->id->id_type == CMD)
		handle_exec_simple_cmd(mini, mini->ast, 1);
	exit(mini->exp->exit_s);
}

static int	handle_left_child(t_minishell *mini, int pfds[2], t_parser *left)
{
	int	pid_left;

	pid_left = fork();
	if (pid_left < 0)
	{
		perror("SHELL: fork");
		return (-1);
	}
	if (pid_left == 0 && left)
		execute_left_child(mini, pfds, left);
	return (pid_left);
}

static int	handle_right_child(t_minishell *mini, int pfds[2], t_parser *right)
{
	int	pid_right;

	pid_right = fork();
	if (pid_right < 0)
	{
		perror("SHELL: fork");
		return (-1);
	}
	if (pid_right == 0 && right)
		execute_right_child(mini, pfds, right);
	return (pid_right);
}

void	ft_pipelines(t_minishell *mini, t_parser *ast)
{
	int	pfds[2];
	int	pid_left;
	int	pid_right;

	if (!ast || ast->id->id_type != PIPELINE)
		return ;
	if (setup_pipe(pfds) == -1)
		return ;
	pid_left = handle_left_child(mini, pfds, ast->left);
	if (pid_left == -1)
		return ;
	pid_right = handle_right_child(mini, pfds, ast->right);
	if (pid_right == -1)
		return ;
	close(pfds[0]);
	close(pfds[1]);
	wait_for_children(pid_left, pid_right, &mini->exp->exit_s);
}
