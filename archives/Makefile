# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/29 00:42:09 by klakbuic          #+#    #+#              #
#    Updated: 2024/03/29 00:43:41 by klakbuic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     = minishell
CC       = cc
CFLAGS   = -Wall -Wextra #-Werror -lreadline
DEBUG    = -fsanitize=address -g3
LIB      = libs/libft/libft.a libs/ft_containers/containersft.a

DIR_SRC = src
DIR_LEXER = lexer

SRC_FILES = main.c
SRCS_SRC = $(foreach file,$(SRC_FILES),$(DIR_SRC)/$(file))

LEXER_FILES = lexer.c string_iterator.c helpers.c lexer_helpers.c
SRCS_LEXER = $(foreach file,$(LEXER_FILES),$(DIR_SRC)/$(DIR_LEXER)/$(file))

SRCS = $(SRCS_SRC) $(SRCS_LEXER) $(SRCS_MEMORY)

DIR_OBJ = obj
OBJS = $(patsubst $(DIR_SRC)/%.c,$(DIR_OBJ)/%.o,$(SRCS))

all: $(NAME)

$(LIB):
	@make -C libs/libft --quiet
	@make -C libs/ft_containers --quiet

$(NAME): objs $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME)

$(DIR_OBJ)/%.o : $(DIR_SRC)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

objs:
	@mkdir $(DIR_OBJ)
	@mkdir $(DIR_OBJ)/$(DIR_LEXER)
	@mkdir $(DIR_OBJ)/$(DIR_MEMORY)
	@printf "$(OBJS)"
	@printf "\e[38;5;190m\t==>>directory of binaries is created.\e[0m\n"

clean:
	@make clean -C libs/libft --quiet
	@make clean -C libs/ft_containers --quiet
	@rm -rf $(DIR_OBJ)

fclean: clean
	@make fclean -C libs/libft --quiet
	@make fclean -C libs/ft_containers --quiet
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean  fclean re