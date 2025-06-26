# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/03 16:15:28 by hmoukit           #+#    #+#              #
#    Updated: 2024/12/10 18:47:32 by hmoukit          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -*- MakeFile -*-

NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror

# Source files
T_SOURCES = ./tokenizer/tokenizer.c \
			./tokenizer/tokenizer_handler.c \
			./tokenizer/tokenizer_utils.c \
			./tokenizer/t_token_utils.c \
			./tokenizer/process_tokens.c \
			./tokenizer/syntax_errors.c

P_SOURCES = ./parser/parser.c \
			./parser/parser_utils.c \
			./parser/parser_handler.c

EXP_SOURCES = ./expander/expander_handler.c \
			  ./expander/expander_utils.c \
			  ./expander/expander.c \
			  ./expander/heredoc_ex.c \
			  ./expander/handle_quoted_str.c \
			  ./expander/ft_getenv.c \
			  ./expander/delimeter_quotes.c

EXEC_SOURCES = ./execution/find_path.c \
			   ./execution/execution_utils.c \
			   ./execution/make_env.c \
			   ./execution/pipelines.c \
			   ./execution/redirections_handler.c \
			   ./execution/heredoc_handler.c \
			   ./execution/redirections_utils.c \
			   ./execution/redirections.c \
			   ./execution/simple_cmd.c \
			   ./execution/minishell.c \
			   ./execution/executer.c \
			   ./execution/open_out_files.c \
			   ./execution/signals.c \
			   ./execution/pipelines_utils.c \
			   ./execution/simple_cmd_utils.c \
			   ./execution/cleanup.c

B_SOURCES = ./builtins/execute_builtins.c \
			./builtins/ft_echo.c \
			./builtins/ft_exit.c \
			./builtins/ft_env.c \
			./builtins/ft_pwd.c \
			./builtins/ft_cd.c \
			./builtins/builtins_utils.c \
			./builtins/ft_export.c \
			./builtins/ft_unset.c

# Object files
T_OBJECTS = $(T_SOURCES:.c=.o)
P_OBJECTS = $(P_SOURCES:.c=.o)
EXP_OBJECTS = $(EXP_SOURCES:.c=.o)
EXEC_OBJECTS = $(EXEC_SOURCES:.c=.o)
B_OBJECTS = $(B_SOURCES:.c=.o)

# Include headers
INCLUDES = ./includes/tokenizer.h \
		   ./includes/parser.h \
	       ./includes/expander.h \
		   ./includes/minishell.h 

# Compiler flags 
RINCLUDE = -I /Users/hmoukit/homebrew/opt/readline/include
RLINK = -lreadline -L /Users/hmoukit/homebrew/opt/readline/lib

# Rule to create object files
%.o: %.c
	$(CC) $(FLAGS) $(RINCLUDE) -c -o $@ $<

# Target to build the final executable
all: libft $(NAME)

$(NAME): $(T_OBJECTS) $(P_OBJECTS) $(EXP_OBJECTS) $(EXEC_OBJECTS) $(B_OBJECTS) $(INCLUDES)
	$(CC) $(FLAGS) -o $(NAME) $(T_OBJECTS) $(P_OBJECTS) $(EXP_OBJECTS) $(EXEC_OBJECTS) $(B_OBJECTS) $(RINCLUDE) $(RLINK) ./libft/libft.a

# libft target
libft:
	make -C ./libft

# Clean object files
clean:
	$(RM) $(T_OBJECTS) $(P_OBJECTS) $(EXP_OBJECTS) $(EXEC_OBJECTS) $(B_OBJECTS)
	make -C ./libft clean

# Full clean
fclean: clean
	$(RM) $(NAME)
	make -C ./libft fclean

# Rebuild from scratch
re: fclean all

.PHONY: libft clean