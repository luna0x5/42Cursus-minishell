/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:35:24 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/07 04:49:04 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenizer.h"

static int	free_q_err(t_token **list, t_token **tok, char **line, char **beg)
{
	if (!handle_quotes(*tok, line, *beg))
	{
		free(*tok);
		*tok = NULL;
		token_clear(list);
		return (0);
	}
	return (1);
}

static int	free_w_err(t_token **list, t_token **tok, char **line, char **beg)
{
	if (!handle_words(*tok, line, *beg))
	{
		free(*tok);
		*tok = NULL;
		token_clear(list);
		return (0);
	}
	return (1);
}

static void	append_operator(t_token **list, t_token *token, char **line)
{
	handle_operators(token, line);
	token_add_back(list, token);
}

int	process_tokens(t_token **list, t_token *token, char **line, char *beg)
{
	if (**line && ft_isquote(**line))
	{
		if (!free_q_err(list, &token, line, &beg))
			return (0);
		token_add_back(list, token);
	}
	else if (ft_isoperator(*line) && **line)
		append_operator(list, token, line);
	else if (**line && !ft_isspace(**line) && !ft_isoperator(*line))
	{
		if (!free_w_err(list, &token, line, &beg))
			return (0);
		token_add_back(list, token);
	}
	else
	{
		free(token);
		token = NULL;
	}
	return (1);
}
