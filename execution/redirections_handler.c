/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:48:04 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/30 03:54:23 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_input(t_parser *node)
{
	int	fd;

	fd = open(node->right->id->ident, O_RDONLY);
	if (fd < 0)
	{
		perror("SHELL: fd");
		return (0);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("SHELL: dup2");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int	handle_output(t_parser *node)
{
	int	fd;

	fd = open(node->right->id->ident, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("SHELL: fd");
		return (0);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("SHELL: dup2");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int	handle_append(t_parser *node)
{
	int	fd;

	fd = open(node->right->id->ident, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("SHELL: fd");
		return (0);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("SHELL: dup");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}
