/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:06:27 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/10 06:50:34 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	make_args(t_minishell *node, t_parser *ast)
{
	t_parser	*current;
	int			i;

	current = ast;
	i = 0;
	node->args = malloc(sizeof(char *) * (count_arg(ast) + 1));
	if (!node->args)
		return (0);
	while (current)
	{
		node->args[i] = ft_strdup(current->id->ident);
		if (!node->args[i])
		{
			free(node->args[i]);
			return (0);
		}
		current = current->right;
		i++;
	}
	node->args[i] = NULL;
	return (1);
}

void	handle_exec_simple_cmd(t_minishell *node, t_parser *ast, int check)
{
	char	*path;
	char	**env_2d;

	if (!make_args(node, ast))
		return ;
	env_2d = make_env_2d(node->exp->env);
	path = NULL;
	if (!check)
	{
		if (!execute_builtins(node))
			node->exp->exit_s = exec_simple_cmd(node, env_2d);
	}
	else
		exec_no_fork(node, env_2d, path);
	free_args(env_2d);
}
