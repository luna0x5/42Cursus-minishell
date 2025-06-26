/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:24:43 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/09 23:18:06 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_env	*ft_lstlast(t_env *lst)
{
	t_env	*current;
	t_env	*last;

	if (!lst)
		return (NULL);
	current = lst;
	last = NULL;
	while (current != NULL)
	{
		last = current;
		current = current -> next;
	}
	return (last);
}

t_env	*ft_lstnew(void *content)
{
	t_env	*list;

	list = (t_env *)malloc(sizeof(t_env));
	if (list == NULL)
		return (NULL);
	list -> data = ft_strdup(content);
	list -> next = NULL;
	return (list);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last -> next = new;
}

char	*extract_env_key(char *data)
{
	char	*key;

	key = ft_substr(data, 0, count_equal_len(data));
	if (!key)
		return (NULL);
	return (key);
}

t_env	*make_env(void)
{
	extern char	**environ;
	t_env		*env;
	t_env		*new_node;
	int			i;

	env = NULL;
	i = 0;
	if (!environ)
		return (NULL);
	while (environ[i])
	{
		new_node = ft_lstnew(environ[i]);
		new_node->key = extract_env_key(new_node->data);
		new_node->value = get_value(new_node->data);
		ft_lstadd_back(&env, new_node);
		i++;
	}
	return (env);
}
