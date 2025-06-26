# -*- MakeFile -*-

NAME = libft.a
CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -f
ARCH = ar -rc

SOURCES = ft_atoi.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_itoa.c \
		ft_split.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_strndup.c \
		ft_strcmp.c

OBJECTS = $(SOURCES:.c=.o)

all:$(NAME)

$(NAME) : $(OBJECTS)
	$(ARCH) $(NAME) $(OBJECTS)

%.o: %.c libft.h
	$(CC) $(FLAGS) -c -o $@ $<

clean :
	$(RM) $(OBJECTS) $(B_OBJECTS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : clean