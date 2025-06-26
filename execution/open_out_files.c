/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_out_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 02:02:33 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/30 03:53:22 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_out(t_parser *n)
{
	int	fd;

	fd = open(n->right->id->ident, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("SHELL: fd");
		return (0);
	}
	close(fd);
	return (1);
}

int	open_append(t_parser *n)
{
	int	fd;

	fd = open(n->right->id->ident, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("SHELL: fd");
		return (0);
	}
	close(fd);
	return (1);
}
