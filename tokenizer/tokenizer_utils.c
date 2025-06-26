/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:16:18 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/07 04:47:24 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenizer.h"

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_isoperator(char *c)
{
	if (!ft_strncmp(c, "|", 1) || !ft_strncmp(c, "<", 1)
		|| !ft_strncmp(c, ">", 1) || !ft_strncmp(c, "<<", 2)
		|| !ft_strncmp(c, ">>", 2))
		return (1);
	return (0);
}

int	ft_isquote(char c)
{
	if (c == '\'')
		return (1);
	if (c == '"')
		return (2);
	return (0);
}
