/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:37:09 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/10 00:34:48 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unset_env(t_env **env, char *key)
{
	t_env	*prev;
	t_env	*tmp;

	prev = *env;
	if (!env || !*env)
		return ;
	if (prev && !ft_strcmp(prev->key, key))
	{
		*env = prev->next;
		free_env_node(prev);
	}
	else
	{
		while (prev->next && ft_strcmp(prev->next->key, key))
			prev = prev->next;
		if (prev->next)
		{
			tmp = prev->next->next;
			free_env_node(prev->next);
			prev->next = tmp;
		}
	}
}

int	ft_unset(t_minishell *mini)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	if (!mini->args[i])
		return (0);
	while (mini->args[i])
	{
		if (!is_valid_id(mini->args[i]))
		{
			ret = 1;
			write(2, "SHELL: unset: not a valid identifier\n", 37);
		}
		else
			unset_env(&(mini->exp->env), mini->args[i]);
		i++;
	}
	return (ret);
}
