/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 00:03:23 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/10 00:34:09 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_builtins(t_minishell *mini)
{
	if (!ft_strcmp("env", mini->args[0]))
		return ((mini->exp->exit_s = ft_env(mini)), 1);
	if (!ft_strcmp("echo", mini->args[0]))
		return ((mini->exp->exit_s = ft_echo(mini)), 1);
	if (!ft_strcmp("exit", mini->args[0]))
		return (ft_exit(mini), 1);
	if (!ft_strcmp("pwd", mini->args[0]))
		return ((mini->exp->exit_s = ft_pwd(mini)), 1);
	if (!ft_strcmp("cd", mini->args[0]))
		return ((mini->exp->exit_s = ft_cd(mini)), 1);
	if (!ft_strcmp("export", mini->args[0]))
		return ((mini->exp->exit_s = ft_export(mini)), 1);
	if (!ft_strcmp("unset", mini->args[0]))
		return ((mini->exp->exit_s = ft_unset(mini)), 1);
	return (0);
}
