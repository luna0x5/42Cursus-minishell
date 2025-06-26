/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 08:46:27 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/04 13:10:53 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	assign_prec(t_token *tokens)
{
	if (tokens)
	{
		if (tokens->token_type == PIPE)
			return (1);
		else if (check_redir(tokens->token_type))
			return (2);
	}
	return (0);
}

static void	assign_io_type(t_parser *node, t_token *tokens)
{
	if (tokens->token_type == LESS)
		node->io_type = INPUT;
	else if (tokens->token_type == D_LESS)
		node->io_type = HEREDOC;
	else if (tokens->token_type == GREAT)
		node->io_type = OUTPUT;
	else if (tokens->token_type == D_GREAT)
		node->io_type = APPEND;
}

t_parser	*node_new(t_token *tokens)
{
	t_parser	*node;

	node = (t_parser *)malloc(sizeof(t_parser));
	if (!node)
		return (NULL);
	node->id = (t_build_id *)malloc(sizeof(t_build_id));
	if (!node->id)
		return (NULL);
	if (tokens->token_type == PIPE)
	{
		node->id->id_type = PIPELINE;
		node->id->ident = NULL;
	}
	else if (check_redir(tokens->token_type))
	{
		node->id->id_type = REDIRECTION;
		assign_io_type(node, tokens);
		node->id->ident = NULL;
	}
	return (node);
}

t_parser	*create_node(t_token *operator, t_parser *left, t_parser *right)
{
	t_parser	*node;

	node = node_new(operator);
	if (!node)
		return (NULL);
	node->left = left;
	node->right = right;
	return (node);
}
