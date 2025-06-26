/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 02:27:15 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/27 01:31:27 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../libft/libft.h"

// types of tokens
typedef enum e_token_type
{
	WORD,
	LESS,
	GREAT,
	D_LESS,
	D_GREAT,
	PIPE
}	t_token_type;

// tokens list
typedef struct s_token
{
	t_token_type	token_type;
	char			*token;
	struct s_token	*next;
}					t_token;

// list utils
t_token	*token_new(void *content);
void	token_add_back(t_token **lst, t_token *new);
void	token_clear(t_token **token);

// identifying and skiping whitespace
int		ft_isspace(char c);

// checking syntax errorx
int		check_pipe_beg(t_token *tokens);
int		check_redir(t_token_type type);
int		check_redir_beg(t_token *tokens);
int		check_syntax(t_token **list);

// handling quotes
int		ft_isquote(char c);
int		handle_quotes(t_token *tokens, char **line, char *beg);

// handling operators
int		ft_isoperator(char *c);
void	handle_operators(t_token *token, char **line);

// handling words
int		handle_words(t_token *tokens, char **line, char *beg);
int		check_tokens(t_token **list, t_token *token, char **line);

// make tokens list
int		process_tokens(t_token **list, t_token *token, char **line, char *beg);

// the main function of the tokenizer
t_token	*make_tokens(char **line);

#endif
