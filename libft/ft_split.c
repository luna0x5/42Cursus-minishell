/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:29:37 by hmoukit           #+#    #+#             */
/*   Updated: 2023/12/06 11:08:40 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count(char const *s, char c)
{
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			counter++;
		while (s[i] != c && s[i])
			i++;
	}
	return (counter);
}

static void	free_split(char **str)
{
	size_t	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

static void	initialize(size_t *i, size_t *j)
{
	*i = 0;
	*j = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	i;
	size_t	j;
	size_t	start;

	if (s == NULL)
		return (NULL);
	str = (char **)malloc((count(s, c) + 1) * sizeof(char *));
	if (str == NULL)
		return (NULL);
	initialize(&i, &j);
	while (j < count(s, c))
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] != c && s[i])
			i++;
		str[j] = (char *)malloc(i - start + 1);
		if (str[j] == NULL)
			return (free_split(str), NULL);
		ft_strlcpy(str[j], &s[start], i - start + 1);
		j++;
	}
	return (str[j] = NULL, str);
}
