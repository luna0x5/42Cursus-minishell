/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:01:34 by hmoukit           #+#    #+#             */
/*   Updated: 2024/10/14 23:23:15 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenizer.h"

static t_token	*token_last(t_token *token)
{
	t_token	*current;
	t_token	*last;

	if (!token)
		return (NULL);
	current = token;
	last = NULL;
	while (current != NULL)
	{
		last = current;
		current = current -> next;
	}
	return (last);
}

void	token_add_back(t_token **token, t_token *new)
{
	t_token	*last;

	if (token == NULL)
		return ;
	if (*token == NULL)
	{
		*token = new;
		return ;
	}
	last = token_last(*token);
	last -> next = new;
}

t_token	*token_new(void *content)
{
	t_token	*list;

	list = (t_token *)malloc(sizeof(t_token));
	if (list == NULL)
		return (NULL);
	list -> token = content;
	list -> next = NULL;
	return (list);
}

void	token_clear(t_token **token)
{
	t_token	*current;
	t_token	*tmp;

	if (!token || !*token)
		return ;
	current = *token;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp->token);
		free(tmp);
	}
	*token = NULL;
}
