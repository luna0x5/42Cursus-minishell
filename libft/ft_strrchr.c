/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:31:17 by hmoukit           #+#    #+#             */
/*   Updated: 2023/11/14 09:30:36 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	n;
	char	*s1;
	size_t	slen;

	n = (char)c;
	s1 = (char *)s;
	slen = ft_strlen(s1);
	if (n == '\0')
		return (&s1[slen]);
	while (slen > 0)
	{
		slen--;
		if (s1[slen] == n)
			return (&s1[slen]);
	}
	return (NULL);
}
