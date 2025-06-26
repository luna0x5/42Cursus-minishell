/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 23:46:37 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/10 01:37:22 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	type_redirection(t_minishell *mini, t_parser *node, t_red_type type)
{
	if (type == INPUT)
	{
		if (!handle_input(node))
			return (0);
	}
	else if (type == OUTPUT)
	{
		if (!handle_output(node))
			return (0);
	}
	else if (type == APPEND)
	{
		if (!handle_append(node))
			return (0);
	}
	else if (type == HEREDOC)
	{
		if (!handle_heredoc(node, mini->exp))
			return (0);
	}
	return (1);
}

void	find_execute_cmd(t_minishell *mini, t_parser *node)
{
	if (node->left && node->left->id->id_type == CMD)
		handle_exec_simple_cmd(mini, node->left, 1);
	else if (node->left)
		find_execute_cmd(mini, node->left);
}

int	open_in_files(t_minishell *mini, t_parser *node)
{
	int	fd;

	if (!node)
		return (0);
	if (node->id->id_type == REDIRECTION)
	{
		if (node->io_type == INPUT)
		{
			fd = open(node->right->id->ident, O_RDONLY);
			if (fd < 0)
			{
				perror("SHELL: fd");
				return (0);
			}
			close(fd);
		}
		else if (node->io_type == HEREDOC)
		{
			if (!handle_heredoc(node, mini->exp))
				return (0);
			open_in_files(mini, node->left);
		}
	}
	return (1);
}

int	open_out_files(t_minishell *mini, t_parser *node)
{
	if (!node)
		return (0);
	if (node->id->id_type == REDIRECTION)
	{
		if (node->io_type == OUTPUT)
		{
			if (!open_out(node))
				return (0);
		}
		else if (node->io_type == APPEND)
		{
			if (!open_append(node))
				return (0);
		}
		open_out_files(mini, node->left);
	}
	return (1);
}
