/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 04:37:15 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/01 17:41:05 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenizer.h"

int	check_redir(t_token_type type)
{
	if (type == LESS || type == D_LESS || type == GREAT || type == D_GREAT)
		return (1);
	return (0);
}

int	check_redir_beg(t_token *tokens)
{
	if (tokens && check_redir(tokens->token_type)
		&& ((tokens->next && ft_isoperator(tokens->next->token))
			|| !tokens->next))
	{
		write(2, "SHELL: SYNTAX ERROR: Redirection File\n", 38);
		return (0);
	}
	return (1);
}

int	check_pipe_beg(t_token *tokens)
{
	if (tokens && *(tokens->token) == '|' && !tokens->next)
	{
		write(2, "SHELL: SYNTAX ERROR: Pipeline without command\n", 46);
		return (0);
	}
	return (1);
}

int	check_syntax(t_token **list)
{
	t_token	*tmp;

	tmp = *list;
	if (tmp->token_type == PIPE)
	{
		write(2, "SHELL: SYNTAX ERROR: Pipeline without command\n", 46);
		token_clear(list);
		return (0);
	}
	while (tmp)
	{
		if (tmp && !check_redir_beg(tmp))
		{
			token_clear(list);
			return (0);
		}
		if (tmp && !check_pipe_beg(tmp))
		{
			token_clear(list);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
