/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 08:46:43 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/30 17:49:03 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

static bool	handle_redirection(t_token **tokens, t_parser **left)
{
	t_token	*operator;

	operator = *tokens;
	if (!check_redir(operator->token_type))
		return (true);
	if (!handle_redir(left, tokens))
		return (false);
	return (true);
}

static t_parser	*parse_operator(t_parser *left, t_token *op, t_token **tokens)
{
	t_parser	*right;

	*tokens = (*tokens)->next;
	right = parse_expression(assign_prec(op) + 1, tokens);
	left = create_node(op, left, right);
	return (left);
}

t_parser	*parse_expression(int prec_level, t_token **tokens)
{
	t_parser	*left;
	t_token		*operator;

	left = parse_primary(tokens);
	if (!left)
	{
		if (!handle_redirection(tokens, &left))
			return (NULL);
	}
	while (*tokens && assign_prec(*tokens) >= prec_level)
	{
		operator = *tokens;
		if (check_redir(operator->token_type))
		{
			if (!handle_redirection(tokens, &left))
				return (NULL);
		}
		else
		{
			left = parse_operator(left, operator, tokens);
			if (!left)
				return (NULL);
		}
	}
	return (left);
}

t_parser	*make_ast(t_token *tokens)
{
	t_parser	*ast;

	if (!tokens)
		return (NULL);
	ast = parse_expression(1, &tokens);
	return (ast);
}
