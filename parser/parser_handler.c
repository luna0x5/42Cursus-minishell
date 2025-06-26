/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 05:50:28 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/27 10:54:12 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

static int	handle_arg(t_token **tokens, t_parser *cmd_node)
{
	t_parser	*current;
	t_parser	*tmp;

	current = cmd_node;
	while (*tokens && (*tokens)->token_type == WORD)
	{
		tmp = create_node(*tokens, NULL, NULL);
		if (!tmp)
			return (0);
		tmp->id->id_type = ARG;
		tmp->id->ident = ft_strdup((*tokens)->token);
		while (current->right)
			current = current->right;
		current->right = tmp;
		*tokens = (*tokens)->next;
	}
	return (1);
}

t_parser	*parse_primary(t_token **tokens)
{
	t_parser	*cmd_node;

	cmd_node = NULL;
	if (*tokens && (*tokens)->token_type == WORD)
	{
		cmd_node = create_node(*tokens, NULL, NULL);
		if (!cmd_node)
			return (NULL);
		cmd_node->id->id_type = CMD;
		cmd_node->id->ident = ft_strdup((*tokens)->token);
		*tokens = (*tokens)->next;
		if (!handle_arg(tokens, cmd_node))
			return (NULL);
	}
	return (cmd_node);
}

static int	handle_rfile(t_token **tokens, t_parser *redir_node)
{
	*tokens = (*tokens)->next;
	if (*tokens && (*tokens)->token_type == WORD)
	{
		redir_node->right = create_node(*tokens, NULL, NULL);
		if (!redir_node->right)
			return (0);
		redir_node->right->id->id_type = RFILE;
		redir_node->right->id->ident = ft_strdup((*tokens)->token);
		*tokens = (*tokens)->next;
	}
	return (1);
}

static int	first_red_make(t_parser *first_red, t_token **tokens)
{
	if (!first_red->left && *tokens && (*tokens)->token_type == WORD)
	{
		first_red->left = parse_primary(tokens);
		if (!first_red->left)
			return (0);
	}
	else if (*tokens && (*tokens)->token_type == WORD)
	{
		if (!handle_arg(tokens, first_red->left))
			return (0);
	}
	return (1);
}

int	handle_redir(t_parser **ast, t_token **tokens)
{
	t_parser	*redir_node;
	t_parser	*first_red;

	first_red = NULL;
	while (*tokens && check_redir((*tokens)->token_type))
	{
		redir_node = create_node(*tokens, NULL, NULL);
		if (!redir_node)
			return (0);
		if (!handle_rfile(tokens, redir_node))
			return (0);
		if (!first_red)
			first_red = redir_node;
		redir_node->left = *ast;
		*ast = redir_node;
		if (first_red)
		{
			if (!first_red_make(first_red, tokens))
				return (0);
		}
	}
	return (1);
}
