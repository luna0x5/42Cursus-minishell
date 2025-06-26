/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:12:22 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/03 16:32:49 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
	free(args);
}

int	make_argument(t_parser *ast, char **args, t_parser *current, t_parser*tmp )
{
	int			i;

	i = 1;
	while (args[i])
	{
		tmp = (t_parser *)malloc(sizeof(t_parser));
		if (!tmp)
			return (0);
		tmp->id = (t_build_id *)malloc(sizeof(t_build_id));
		if (!tmp->id)
		{
			free(tmp);
			return (0);
		}
		tmp->id->id_type = ARG;
		tmp->id->ident = ft_strdup(args[i]);
		tmp->left = NULL;
		tmp->right = NULL;
		current = ast;
		while (current->right)
			current = current->right;
		current->right = tmp;
		i++;
	}
	return (1);
}

int	cmd_not_found(t_exp *exp)
{
	write(2, "SHELL: command not found\n", 25);
	exp->exit_s = 127;
	return (0);
}

int	handle_cmd_ex(t_parser *ast, t_exp *exp)
{
	char		**args;
	t_parser	*current;
	t_parser	*tmp;

	if (ast->id && ast->id->ident)
		process_string(ast, exp);
	args = ft_split(ast->id->ident, ' ');
	if (!args)
		return (0);
	if (args[0] && args[1])
	{
		free(ast->id->ident);
		ast->id->ident = ft_strdup(args[0]);
		if (!ast->id->ident)
			return (0);
		ast->left = NULL;
		ast->right = NULL;
		current = NULL;
		tmp = NULL;
		make_argument(ast, args, current, tmp);
	}
	free_args(args);
	if (ast->id->ident[0] == '\0')
		return (cmd_not_found(exp));
	return (1);
}

int	expand_ast(t_parser *ast, t_exp *exp)
{
	if (!ast)
		return (0);
	if (ast->id->id_type == CMD)
		if (!handle_cmd_ex(ast, exp))
			return (0);
	if (ast->id->id_type == REDIRECTION && ast->io_type == HEREDOC)
	{
		handle_heredoc_ex(ast, exp);
		return (1);
	}
	if (ast->id->id_type == ARG || ast->id->id_type == RFILE)
	{
		if (ast->id->ident)
			process_string(ast, exp);
	}
	expand_ast(ast->left, exp);
	expand_ast(ast->right, exp);
	return (1);
}
