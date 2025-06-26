/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:42:53 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/03 16:32:49 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"

int	ft_isvalid(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*expand_var(char *arg, t_exp *exp)
{
	char	*env_var;
	char	*result;

	if (!arg && !(*arg))
		return ("$");
	env_var = ft_getenv(arg, exp);
	if (!env_var)
		return (ft_strdup(""));
	result = ft_strdup(env_var);
	return (result);
}

char	*append_string(char *result, const char *to_append)
{
	char	*new_result;

	new_result = ft_strjoin(result, to_append);
	if (result)
	{
		free(result);
		result = NULL;
	}
	return (new_result);
}

void	append_single_char(char *arg, int *i, char **result)
{
	char	single_char[2];

	single_char[0] = arg[*i];
	single_char[1] = '\0';
	*result = append_string(*result, single_char);
	(*i)++;
}

void	check_quote(char *arg, int *i, char **result, t_exp *exp)
{
	if (ft_isquote(arg[*i]) == 1)
		handle_single_quote(arg, result, i, 0);
	else if (ft_isquote(arg[*i]) == 2)
		handle_double_quote(arg, result, i, exp);
}
