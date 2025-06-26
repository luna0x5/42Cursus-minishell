/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 00:45:20 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/30 03:59:15 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenizer.h"

static int	closer_quote(char **line)
{
	int	check;

	check = ft_isquote(**line);
	(*line)++;
	if (check == 1)
	{
		while (**line && **line != '\'')
			(*line)++;
		if (**line != '\'')
		{
			write(2, "SHELL: SYNTAX ERROR: closing quote\n", 35);
			return (0);
		}
	}
	if (check == 2)
	{
		while (**line && **line != '"')
			(*line)++;
		if (**line != '"')
		{
			write(2, "SHELL: SYNTAX ERROR: closing quote\n", 35);
			return (0);
		}
	}
	return (1);
}

int	handle_quotes(t_token *tokens, char **line, char *beg)
{
	char	*quote;
	int		len;

	quote = *line;
	if (!closer_quote(line))
		return (0);
	(*line)++;
	while (*line && **line && !ft_isoperator(*line) && !ft_isspace(**line))
	{
		if (ft_isquote(**line) && !closer_quote(line))
			return (0);
		(*line)++;
	}
	while (!ft_isoperator(quote) && !ft_isspace(*quote) && quote != beg)
		quote--;
	len = *line - quote;
	tokens->token = ft_strndup(quote, len);
	tokens->token_type = WORD;
	return (1);
}

static void	make_op_token(t_token *tokens, t_token_type type, char *op)
{
	tokens->token_type = type;
	tokens->token = ft_strdup(op);
}

void	handle_operators(t_token *token, char **line)
{
	if (!ft_strncmp(*line, "|", 1))
	{
		make_op_token(token, PIPE, "|");
		(*line)++;
	}
	else if (!ft_strncmp(*line, "<<", 2))
	{
		make_op_token(token, D_LESS, "<<");
		*line += 2;
	}
	else if (!ft_strncmp(*line, ">>", 2))
	{
		make_op_token(token, D_GREAT, ">>");
		*line += 2;
	}
	else if (!ft_strncmp(*line, "<", 1))
	{
		make_op_token(token, LESS, "<");
		(*line)++;
	}
	else if (!ft_strncmp(*line, ">", 1))
	{
		make_op_token(token, GREAT, ">");
		(*line)++;
	}
}

int	handle_words(t_token *tokens, char **line, char *beg)
{
	char	*start;
	size_t	len;

	start = *line;
	while (**line && !ft_isspace(**line)
		&& !ft_isoperator(*line) && !ft_isquote(**line))
		(*line)++;
	if (ft_isquote(**line))
	{
		if (!handle_quotes(tokens, line, beg))
			return (0);
		return (1);
	}
	len = *line - start;
	tokens->token = ft_strndup(start, len);
	tokens->token_type = WORD;
	return (1);
}
