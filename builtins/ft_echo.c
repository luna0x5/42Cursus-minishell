/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 23:24:11 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/27 01:41:33 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_n_option(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] != '-')
		return (0);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_minishell *mini)
{
	int	check_n;
	int	i;

	check_n = 0;
	i = 1;
	while (mini->args[i] && check_n_option(mini->args[i]))
	{
		check_n = 1;
		i++;
	}
	while (mini->args[i])
	{
		ft_putstr_fd(mini->args[i], 1);
		if (mini->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!check_n)
		write(1, "\n", 1);
	return (0);
}
