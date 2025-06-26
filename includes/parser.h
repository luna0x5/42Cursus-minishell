/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 02:32:09 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/27 09:59:24 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>

# include "../includes/tokenizer.h"

// to identify the token
typedef enum e_identifier
{
	CMD,
	ARG,
	PIPELINE,
	REDIRECTION,
	RFILE
}	t_identifier;

// to give the right type of the redirection
typedef enum e_red_type
{
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC
}	t_red_type;

// to make the identifier
typedef struct s_build_id
{
	t_identifier	id_type;
	char			*ident;
}					t_build_id;

// the structure of the AST
typedef struct s_parser
{
	t_build_id		*id;
	t_red_type		io_type;
	struct s_parser	*left;
	struct s_parser	*right;
}					t_parser;

// checks and assignements
int			check_redir(t_token_type type);
int			assign_prec(t_token *tokens);

// tree utils
t_parser	*node_new(t_token *tokens);
t_parser	*create_node(t_token *operator, t_parser *left, t_parser *right);

// parser handlers
t_parser	*parse_primary(t_token **tokens);
t_parser	*parse_expression(int prec_level, t_token **tokens);
int			handle_redir(t_parser **ast, t_token **tokens);

// the main function of the parser
t_parser	*make_ast(t_token *tokens);

#endif