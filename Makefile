I = -L /Users/soutchak/readline/lib

all:
	make -C libs/libft
	cc -Wall -Wextra src/*.c src/lexer/*.c src/parser/*.c src/executor/*.c src/environment/*.c src/builtins/*.c \
	src/utils/*.c src/expander/*.c libs/libft/libft.a $I -o minishell  -lreadline

clean:
	make -C libs/libft clean

fclean: clean
	make -C libs/libft fclean
	rm -f minishell

re: fclean all

run: all
	./minishell

.PHONY: all clean fclean re run
