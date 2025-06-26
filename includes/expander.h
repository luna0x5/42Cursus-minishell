/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:12:24 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/10 18:18:54 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../includes/parser.h"

// the structure of the list of environment variables
typedef struct s_env
{
	char			*key;
	char			*value;
	char			*data;
	struct s_env	*next;
}					t_env;

// the structure used in expanding
typedef struct s_exp
{
	t_env			*env;
	unsigned char	exit_s;
}					t_exp;

// check if the character is a valid character for expanding
int		ft_isvalid(char c);

// to append two strings or a string witg character
char	*append_string(char *result, const char *to_append);
void	append_single_char(char *arg, int *i, char **result);

// utils used in expanding
char	*get_value(char *data);
char	*ft_getenv(char *name, t_exp *exp);
char	*expand_var(char *arg, t_exp *exp);
void	check_quote(char *arg, int *i, char **result, t_exp *exp);

// the expander handlers
void	heredoc_expand(t_parser *node, t_exp *exp);
char	*remove_quotes(char	*delim);
void	handle_heredoc_ex(t_parser *ast, t_exp *exp);
char	*handle_variable_expansion(char *arg, int *i, t_exp *exp);
void	handle_single_quote(char *arg, char **result, int *i, int check);
void	handle_double_quote(char *arg, char **result, int *i, t_exp *exp);
void	process_string(t_parser *ast, t_exp *exp);

// calculating the len of the key and the value
int		count_equal_len(char *data);
int		count_value_len(char *data);

// the main function of the expander
int		expand_ast(t_parser *ast, t_exp *exp);

// to free 2d strings
void	free_args(char **args);

#endif
