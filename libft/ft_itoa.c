/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:28:15 by hmoukit           #+#    #+#             */
/*   Updated: 2023/11/21 16:30:26 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	counter(int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	else if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*check(long x, size_t len, char *s)
{
	size_t	i;

	if (x == 0)
	{
		s[0] = '0';
		return (s);
	}
	if (x < 0)
	{
		s[0] = '-';
		x *= -1;
	}
	i = len - 1;
	while (x > 0)
	{
		s[i] = x % 10 + '0';
		x /= 10;
		i--;
	}
	return (s);
}

static char	*fill_allocate(int n, size_t len)
{
	char	*s;
	long	x;

	x = n;
	s = (char *)malloc(len + 1);
	if (s == NULL)
		return (NULL);
	s[len] = '\0';
	return (check(x, len, s));
}

char	*ft_itoa(int n)
{
	size_t	len;
	long	x;

	x = n;
	if (x == -2147483648)
	{
		len = 11;
		return (fill_allocate(x, len));
	}
	len = counter(x);
	return (fill_allocate(x, len));
}
