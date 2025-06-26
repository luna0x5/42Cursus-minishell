/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:44:37 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/10 03:06:18 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	single_redirection(t_minishell *mini, t_parser *node)
{
	if (!type_redirection(mini, node, node->io_type))
		return (0);
	return (1);
}

int	failed_exit_s(t_parser *node, unsigned char *exit)
{
	if (node->io_type == HEREDOC)
		*exit = 0;
	else
		*exit = 1;
	return (0);
}

int	multiple_in_redirections(t_minishell *mini, t_parser *node)
{
	static int	first;

	if (!node)
		return (failed_exit_s(node, &mini->exp->exit_s));
	if (node->id->id_type == REDIRECTION)
	{
		if (node->io_type == INPUT || node->io_type == HEREDOC)
		{
			if (!first)
			{
				if (!single_redirection(mini, node))
					return (failed_exit_s(node, &mini->exp->exit_s));
				first = 1;
			}
			if (first && node->left && node->left->id->id_type == REDIRECTION)
			{
				if (!open_in_files(mini, node->left))
					return (failed_exit_s(node, &mini->exp->exit_s));
			}
			if (!multiple_in_redirections(mini, node->left))
				return (failed_exit_s(node, &mini->exp->exit_s));
		}
		first = 0;
	}
	return (1);
}

int	multiple_out_redirections(t_minishell *mini, t_parser *node)
{
	static int	first;

	if (!node)
		return (failed_exit_s(node, &mini->exp->exit_s));
	if (node->id->id_type == REDIRECTION)
	{
		if (node->io_type == OUTPUT || node->io_type == APPEND)
		{
			if (!first)
			{
				if (!single_redirection(mini, node))
					return (failed_exit_s(node, &mini->exp->exit_s));
				first = 1;
			}
			if (first && node->left && node->left->id->id_type == REDIRECTION)
			{
				if (!open_out_files(mini, node->left))
					return (failed_exit_s(node, &mini->exp->exit_s));
			}
		}
		if (!multiple_out_redirections(mini, node->left))
			return (failed_exit_s(node, &mini->exp->exit_s));
		first = 0;
	}
	return (1);
}

void	handle_exec_redirections(t_minishell *mini, t_parser *node)
{
	int	pid;
	int	status;

	pid = fork();
	status = 0;
	if (pid == -1)
	{
		perror("SHELL: fork");
		return ;
	}
	else if (pid == 0)
	{
		if (!multiple_in_redirections(mini, node))
			exit(1);
		multiple_out_redirections(mini, node);
		find_execute_cmd(mini, node);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		mini->exp->exit_s = WEXITSTATUS(status);
	}
}
