/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:29:02 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/10 06:54:35 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	heredoc_counter(t_parser *node)
{
	int	i;

	i = 0;
	if (!node)
		return (i);
	if (node->id->id_type == HEREDOC && node->io_type == HEREDOC)
		i++;
	i += heredoc_counter(node->left);
	i += heredoc_counter(node->right);
	return (i);
}

void	executer(t_minishell *mini)
{
	int	j;

	j = heredoc_counter(mini->ast);
	if (mini->ast->id->id_type == PIPELINE)
	{
		traverse_and_handle_heredocs(&j, mini, mini->ast);
		ft_pipelines(mini, mini->ast);
		return ;
	}
	else if (mini->ast->id->id_type == REDIRECTION)
	{
		handle_exec_redirections(mini, mini->ast);
		return ;
	}
	else if (mini->ast->id->id_type == CMD)
		handle_exec_simple_cmd(mini, mini->ast, 0);
	free_args(mini->args);
}
