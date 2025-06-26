/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:47:37 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/10 00:34:17 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	fork_and_exec(char *path, char **args, char **env_2d)
{
	int	pid;
	int	status;

	status = 0;
	pid = fork();
	if (pid == -1)
	{
		perror("SHELL: fork");
		free(path);
		return (1);
	}
	else if (pid == 0)
	{
		if (execve(path, args, env_2d) == -1)
		{
			perror("SHELL: execve");
			free(path);
			exit(127);
		}
	}
	else
		waitpid(pid, &status, 0);
	return (status);
}

int	exec_simple_cmd(t_minishell *node, char **env_2d)
{
	char	*path;
	int		status;

	if (ft_strchr(node->args[0], '/'))
	{
		path = ft_strdup(node->args[0]);
		if (!path)
			return (1);
	}
	else
	{
		if (!node->args[0][0])
			return (0);
		path = get_path(node->args[0], node);
		if (!path)
		{
			write(2, "SHELL: command not found\n", 25);
			return (127);
		}
	}
	status = fork_and_exec(path, node->args, env_2d);
	free(path);
	path = NULL;
	return (get_exit_status(status));
}

void	exec_no_fork(t_minishell *node, char **env_2d, char *path)
{
	if (!execute_builtins(node))
	{
		path = get_path(node->args[0], node);
		if (execve(path, node->args, env_2d) == -1)
		{
			free_args(env_2d);
			perror("SHELL: execve");
			free(path);
			exit(127);
		}
	}
}
