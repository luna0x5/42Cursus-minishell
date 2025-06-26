/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimeter_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:46:24 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/10 18:55:40 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"

static int	quoted_string(char **line, char **result, int *i, char quote)
{
	char	*unquoted;
	char	*tmp;
	int		start;

	(*i)++;
	start = (*i);
	while ((*line)[*i] && (*line)[*i] != quote)
		(*i)++;
	if ((*line)[*i] != quote)
		return (0);
	unquoted = ft_substr(*line, start, *i - start);
	tmp = *result;
	*result = ft_strjoin(tmp, unquoted);
	free(tmp);
	tmp = NULL;
	return (1);
}

static void	make_unquoted(char **result, char **line, int start, int len)
{
	char	*unquoted;
	char	*tmp;

	unquoted = ft_substr(*line, start, len);
	tmp = *result;
	*result = ft_strjoin(tmp, unquoted);
	free(tmp);
	tmp = NULL;
}

static int	unquoted_string(char **line, int *i, char **result)
{
	int		check;
	int		start;

	check = ft_isquote((*line)[*i]);
	start = *i;
	if (check == 1)
	{
		if (!quoted_string(line, result, i, '\''))
			return (write(2, "SHELL: SYNTAX ERROR: closing quote\n", 35), 0);
	}
	else if (check == 2)
	{
		if (!quoted_string(line, result, i, '"'))
			return (write(2, "SHELL: SYNTAX ERROR: closing quote\n", 35), 0);
	}
	else
	{
		while ((*line)[*i] && !ft_isquote((*line)[*i]))
			(*i)++;
		make_unquoted(result, line, start, *i - start);
	}
	return (1);
}

char	*remove_quotes(char *delim)
{
	char	*result;
	int		i;
	int		quote_type;

	quote_type = ft_isquote(*delim);
	if (quote_type == 0)
	{
		result = ft_strdup(delim);
		return (result);
	}
	result = ft_strdup("");
	i = 0;
	while (delim[i])
	{
		if (!unquoted_string(&delim, &i, &result))
			return (NULL);
		if (delim[i])
			i++;
	}
	return (result);
}
