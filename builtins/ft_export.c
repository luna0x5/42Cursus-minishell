/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:38:26 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/10 20:10:09 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_exported_list(t_exp *exp)
{
	t_env	*current;

	current = exp->env;
	while (current)
	{
		if (ft_strcmp("_", current->key))
		{
			write(1, "declare -x ", 11);
			ft_putstr_fd(current->key, 1);
			if (ft_strchr(current->data, '='))
			{
				write(1, "=", 1);
				write(1, "\"", 1);
				ft_putstr_fd(current->value, 1);
				write(1, "\"", 1);
			}
			write(1, "\n", 1);
		}
		current = current->next;
	}
}

static int	make_export_node(t_env **node, char *s)
{
	char	*tmp;

	*node = ft_lstnew(NULL);
	if (!*node)
		return (0);
	(*node)->key = extract_env_key(s);
	if (!(*node)->key)
		return (0);
	(*node)->value = get_value(s);
	if (!(*node)->value)
		return (0);
	if ((*node)->value[0] == '\0')
		free_line(&((*node)->value));
	if (ft_strchr(s, '='))
	{
		tmp = ft_strjoin((*node)->key, "=");
		(*node)->data = ft_strjoin(tmp, (*node)->value);
		free(tmp);
		tmp = NULL;
	}
	else
		(*node)->data = ft_strdup((*node)->key);
	return (1);
}

static void	add_value(t_env *env, t_env *node)
{
	t_env	*current;
	char	*value;
	char	*tmp;

	current = env;
	while (current)
	{
		if (!ft_strcmp(current->key, node->key))
		{
			value = ft_strjoin(current->value, node->value);
			free(current->value);
			current->value = ft_strdup(value);
			free(value);
			value = NULL;
			free(current->data);
			tmp = ft_strjoin(current->key, "=");
			current->data = ft_strjoin(tmp, current->value);
			free(tmp);
			tmp = NULL;
			free_env_node(node);
			break ;
		}
		current = current->next;
	}
}

static int	process_arg(t_minishell *mini, t_exp *exp, char *s)
{
	t_env	*node;
	char	*check;

	node = NULL;
	if (!make_export_node(&node, s))
		return (0);
	if (!is_valid_id(node->key))
	{
		write(2, "SHELL: export: not a valid identifier\n", 38);
		return (0);
	}
	check = ft_strchr(s, '+');
	if (!is_in_env(node->key, exp->env))
		ft_lstadd_back(&exp->env, node);
	else if (check && check[1] && check[1] == '=')
		add_value(exp->env, node);
	else
	{
		if (ft_strchr(s, '=') && !node->value)
			node->value = ft_strdup("");
		update_env(mini, node->key, node->value);
		free_env_node(node);
	}
	return (1);
}

int	ft_export(t_minishell *mini)
{
	int	i;

	i = 1;
	if (!mini->args[i])
		ft_exported_list(mini->exp);
	while (mini->args[i])
	{
		if (!process_arg(mini, mini->exp, mini->args[i]))
			return (1);
		i++;
	}
	return (0);
}
