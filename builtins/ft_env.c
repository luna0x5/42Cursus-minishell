/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 23:26:27 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/09 23:07:46 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(t_minishell *mini)
{
	t_env	*current;

	if (!mini->exp->env)
		return (0);
	if (mini->args[1])
	{
		write(2, "SHELL: env: unkown option\n", 26);
		return (127);
	}
	current = mini->exp->env;
	while (current)
	{
		if (ft_strchr(current->data, '='))
		{
			ft_putstr_fd(current->data, 1);
			write(1, "\n", 1);
		}
		current = current->next;
	}
	return (0);
}
