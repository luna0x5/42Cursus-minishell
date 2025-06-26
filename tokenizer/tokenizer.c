/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:14:17 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/26 19:40:34 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenizer.h"

static void	initialize(t_token **token, char **line, char **beg)
{
	*token = token_new(NULL);
	if (ft_isspace(**line))
		(*line)++;
	*beg = *line;
}

int	check_tokens(t_token **list, t_token *token, char **line)
{
	char	*beg;

	while (**line)
	{
		initialize(&token, line, &beg);
		if (!process_tokens(list, token, line, beg))
			return (0);
	}
	if (!list || !*list)
		return (0);
	if (!check_syntax(list))
		return (0);
	return (1);
}

t_token	*make_tokens(char **line)
{
	t_token	*list;
	t_token	*token;

	list = NULL;
	token = NULL;
	list = token;
	if (!check_tokens(&list, token, line))
	{
		token_clear(&token);
		return (NULL);
	}
	free(token);
	return (list);
}
