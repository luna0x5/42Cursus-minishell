/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 00:59:11 by hmoukit          #+#    #+#             */
/*   Updated: 2024/11/27 01:16:07 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t			i;
	unsigned char	*s3;
	unsigned char	*s4;

	if (!s1 || !s2)
		return (1);
	i = 0;
	s3 = (unsigned char *)s1;
	s4 = (unsigned char *)s2;
	while (s3[i] && s4[i])
	{
		if (s3[i] != s4[i])
			return (s3[i] - s4[i]);
		i++;
	}
	return (s3[i] - s4[i]);
}
