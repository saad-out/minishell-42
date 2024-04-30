I = -L /Users/soutchak/readline/lib
FLAGS := -fsanitize=address -g3
all:
	make -C libs/libft
	cc -Wall -Wextra src/*.c src/lexer/*.c src/parser/*.c src/executor/*.c src/environment/*.c \
	src/builtins/*.c src/utils/*.c src/expander/*.c src/memory/*.c libs/libft/libft.a \
	libs/ft_containers/containersft.a -o minishell  -lreadline \
	$(FLAGS) $(I)

clean:
	make -C libs/libft clean

fclean: clean
	make -C libs/libft fclean
	rm -f minishell

re: fclean all

run: all
	./minishell

.PHONY: all clean fclean re run
