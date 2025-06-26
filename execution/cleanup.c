/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:03:01 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/10 20:10:19 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tree(t_parser *ast)
{
	if (!ast)
		return ;
	if (ast->id->ident)
	{
		free(ast->id->ident);
		ast->id->ident = NULL;
	}
	free(ast->id);
	ast->id = NULL;
	free_tree(ast->left);
	free_tree(ast->right);
	free(ast->left);
	ast->left = NULL;
	free(ast->right);
	ast->right = NULL;
}

void	free_env(t_env **env)
{
	t_env	*tmp;
	t_env	*current;

	if (!env || !*env)
		return ;
	current = *env;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp->data);
		tmp->data = NULL;
		free(tmp->key);
		tmp->key = NULL;
		free(tmp->value);
		tmp->value = NULL;
		free(tmp);
		tmp = NULL;
	}
	*env = NULL;
}

void	free_line(char **line)
{
	free(*line);
	*line = NULL;
}

void	cleanup_mini(t_minishell *mini)
{
	free_env(&(mini->exp->env));
	mini->exp->env = NULL;
	free(mini->exp);
	mini->exp = NULL;
	free(mini->pwd);
	mini->pwd = NULL;
	free(mini->oldpwd);
	mini->oldpwd = NULL;
	free(mini);
	mini = NULL;
}

void	free_env_node(t_env *env)
{
	free(env->data);
	env->data = NULL;
	free(env->key);
	env->key = NULL;
	free(env->value);
	env->value = NULL;
	free(env);
}
