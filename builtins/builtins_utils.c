/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:40:48 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/10 19:58:36 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_env(t_minishell *mini, char *key, char *new_value)
{
	t_env		*node;
	char		*tmp;

	node = mini->exp->env;
	while (node)
	{
		if (!strcmp(node->key, key))
		{
			if (node->value)
				free(node->value);
			node->value = ft_strdup(new_value);
			if (!node->value)
				return ;
			if (node->data)
				free(node->data);
			tmp = ft_strjoin(key, "=");
			node->data = ft_strjoin(tmp, new_value);
			free(tmp);
			tmp = NULL;
			break ;
		}
		node = node->next;
	}
}

int	is_valid_id(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (0);
	i++;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	is_in_env(char *key, t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
			return (1);
		current = current->next;
	}
	return (0);
}

int	is_str_nbr(char *str)
{
	int	i;

	if (!check_long(str))
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
