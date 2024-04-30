FLAGS := -fsanitize=address -g3
LIBS := libs/libft/libft.a

all:
	make -C libs/libft
	# make -C libs/ft_containers
	cc -Wall -Wextra src/*.c src/lexer/*.c src/parser/*.c src/executor/*.c src/environment/*.c \
	src/builtins/*.c src/utils/*.c src/expander/*.c src/memory/*.c libs/libft/libft.a \
	$(LIBS) -o minishell  -lreadline \
	# $(FLAGS)

clean:
	make -C libs/libft clean

fclean: clean
	make -C libs/libft fclean
	rm -f minishell

re: fclean all

run: all
	./minishell

.PHONY: all clean fclean re run
