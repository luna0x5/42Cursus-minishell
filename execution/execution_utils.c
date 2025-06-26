/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:06:58 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/03 13:16:57 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

int	count_arg(t_parser *ast)
{
	t_parser	*current;
	int			count;

	current = ast;
	count = 0;
	while (current)
	{
		current = current->right;
		count++;
	}
	return (count);
}

int	envlen(t_env *env)
{
	t_env	*current;
	int		len;

	current = env;
	len = 0;
	while (current)
	{
		len++;
		current = current->next;
	}
	return (len);
}

void	free_i(char **env_2d, int i)
{
	int	j;

	j = 0;
	while (j != i)
	{
		free(env_2d[j]);
		j++;
	}
	free(env_2d);
}

char	**make_env_2d(t_env *env)
{
	char	**env_2d;
	t_env	*current;
	int		i;

	env_2d = (char **)malloc(sizeof(char *) * (envlen(env) + 1));
	if (!env_2d)
		return (NULL);
	current = env;
	i = 0;
	while (current)
	{
		env_2d[i] = ft_strdup(current->data);
		if (!env_2d[i])
		{
			free_i(env_2d, i);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	env_2d[i] = NULL;
	return (env_2d);
}
