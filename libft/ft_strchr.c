/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:43:18 by hmoukit           #+#    #+#             */
/*   Updated: 2023/11/14 09:29:46 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	n;
	char	*s1;
	int		i;

	n = (char)c;
	s1 = (char *)s;
	i = 0;
	while (s[i])
	{
		if (s1[i] == n)
			return (&s1[i]);
		i++;
	}
	if (n == '\0')
		return (&s1[i]);
	return (NULL);
}
