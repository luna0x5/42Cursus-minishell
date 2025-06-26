/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 23:26:48 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/01 11:05:38 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_long_helper(long long *result, int digit)
{
	long long	max_value;
	long long	min_value;

	max_value = LONG_MAX;
	min_value = LONG_MIN;
	if (*result > max_value / 10
		|| (*result == max_value / 10 && digit > max_value % 10))
		return (0);
	if (*result < min_value / 10
		|| (*result == min_value / 10 && digit < min_value % 10))
		return (0);
	*result = *result * 10 + digit;
	return (1);
}

static int	check_sign_and_initialize(char **str, int *sign)
{
	*sign = 1;
	if (**str == '-')
	{
		*sign = -1;
		(*str)++;
	}
	else if (**str == '+')
		(*str)++;
	return (1);
}

static int	check_digits(char *str, long long *result)
{
	int	digit;

	while (*str)
	{
		if (*str >= '0' && *str <= '9')
		{
			digit = *str - '0';
			if (!check_long_helper(result, digit))
				return (0);
		}
		else
			break ;
		str++;
	}
	return (1);
}

int	check_long(char *str)
{
	long long	result;
	int			sign;

	result = 0;
	if (str == NULL || *str == '\0')
		return (0);
	if (!check_sign_and_initialize(&str, &sign))
		return (0);
	if (!check_digits(str, &result))
		return (0);
	result *= sign;
	if (result > LONG_MAX || result < LONG_MIN)
		return (0);
	return (1);
}

int	ft_exit(t_minishell *mini)
{
	if (mini->args[1])
	{
		if (!is_str_nbr(mini->args[1]))
		{
			write(2, "SHELL: exit: numeric argument required\n", 39);
			mini->exp->exit_s = 255;
			exit(mini->exp->exit_s);
		}
		if (mini->args[2])
		{
			write(2, "SHELL: exit: too many arguments\n", 32);
			mini->exp->exit_s = 1;
			return (1);
		}
		else
		{
			mini->exp->exit_s = (unsigned char)ft_atoi(mini->args[1]);
			exit(mini->exp->exit_s);
		}
	}
	mini->exp->exit_s = 0;
	exit(mini->exp->exit_s);
	return (0);
}
