/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quoted_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 00:08:25 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/09 18:26:44 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"

void	handle_single_quote(char *arg, char **result, int *i, int check)
{
	int		start;
	char	*new_val;
	char	*val;

	start = (*i)++;
	new_val = NULL;
	while (arg[*i] && arg[*i] != '\'')
		(*i)++;
	if (!check)
		new_val = ft_substr(arg, start + 1, (*i) - start - 1);
	if (check)
		new_val = ft_substr(arg, start, (*i) - start + 1);
	val = *result;
	*result = ft_strjoin(val, new_val);
	free(new_val);
	new_val = NULL;
	free(val);
	val = NULL;
	(*i)++;
}

int	closer_quote(char *str, int j)
{
	int	i;

	i = j;
	i++;
	while (str[i] && str[i] != '\'')
		i++;
	if (!str[i])
		return (0);
	return (1);
}

void	expansion_inside_quotes(char *ar, char **r, int *i, t_exp *exp)
{
	char	*expand;

	if (ar[*i + 1] && ar[*i + 1] == '"')
	{
		*r = append_string(*r, "$");
		(*i)++;
		return ;
	}
	else if (ar[*i + 1] && ar[*i + 1] == '\'' && closer_quote(ar, *i + 1))
	{
		(*i)++;
		*r = append_string(*r, "$");
		handle_single_quote(ar, r, i, 1);
		return ;
	}
	expand = handle_variable_expansion(ar, i, exp);
	*r = append_string(*r, expand);
	free(expand);
}

void	handle_double_quote(char *arg, char **result, int *i, t_exp *exp)
{
	(*i)++;
	if (arg[*i] == '"')
		*result = append_string(*result, "");
	while (arg[*i] && arg[*i] != '"')
	{
		if (arg[*i] == '$')
			expansion_inside_quotes(arg, result, i, exp);
		else if (arg[*i] == '\'' && closer_quote(arg, *i))
			handle_single_quote(arg, result, i, 1);
		else
			append_single_char(arg, i, result);
	}
	if (arg[*i])
		(*i)++;
}
