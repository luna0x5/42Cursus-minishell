/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 03:45:17 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/10 05:24:57 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	create_pipe(int pipefd[2])
{
	if (pipe(pipefd) < 0)
	{
		perror("SHELL: pipe: Error creating pipe for heredoc");
		return (0);
	}
	return (1);
}

static int	write_to_pipe(int pipefd[2], char *line, t_exp *exp, int i)
{
	t_parser	*node;

	node = malloc(sizeof(t_parser));
	if (!node)
		return (0);
	node->id = malloc(sizeof(t_build_id));
	if (!node->id)
		return (0);
	node->id->id_type = ARG;
	node->id->ident = ft_strdup(line);
	node->left = NULL;
	node->right = NULL;
	if (i != 2)
		heredoc_expand(node, exp);
	if (write(pipefd[1], node->id->ident, ft_strlen(node->id->ident)) < 0)
		return (perror("SHELL: pipe: Error writing to pipe"), 0);
	if (write(pipefd[1], "\n", 1) < 0)
		return (perror("SHELL: pipe: Error writing newline to pipe"), 0);
	free(node->id->ident);
	free(node->id);
	free(node);
	return (1);
}

static int	handle_duplication(int pipefd[2])
{
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
	{
		perror("SHELL: dup: Error duplicating file descriptor for heredoc");
		close(pipefd[0]);
		return (0);
	}
	close(pipefd[0]);
	return (1);
}

int	read_input(t_parser *node, char **line)
{
	int		i;
	char	*unquoted;

	i = 1;
	unquoted = NULL;
	*line = readline("heredoc> ");
	if (!*line)
		return (0);
	if (ft_isquote(*(node->right->id->ident)))
		i = 2;
	unquoted = remove_quotes(node->right->id->ident);
	if (!unquoted)
		return (-1);
	if (unquoted && !ft_strcmp(*line, unquoted))
	{
		free(*line);
		*line = NULL;
		free(unquoted);
		unquoted = NULL;
		return (-1);
	}
	free(unquoted);
	unquoted = NULL;
	return (i);
}

int	handle_heredoc(t_parser *node, t_exp *exp)
{
	char	*line;
	int		pipefd[2];
	int		check;

	line = NULL;
	signal(SIGINT, ft_sigint_handler_heredoc);
	signal(SIGQUIT, ft_sigquit_handler);
	if (!create_pipe(pipefd))
		return (0);
	while (1)
	{
		check = read_input(node, &line);
		if (check == -1 || check == 0)
			break ;
		if (!write_to_pipe(pipefd, line, exp, check))
		{
			free(line);
			line = NULL;
			close(pipefd[1]);
			return (0);
		}
		free(line);
		line = NULL;
	}
	return (close(pipefd[1]), handle_duplication(pipefd));
}
