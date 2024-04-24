I = -L /Users/soutchak/readline/lib
FLAGS = -g3 -fsanitize=address

all:
	make -C libs/libft
	cc -Wall -Wextra src/*.c src/lexer/*.c src/parser/*.c src/executor/*.c src/environment/*.c src/builtins/*.c \
	src/utils/*.c src/expander/*.c libs/libft/libft.a -o minishell  -lreadline 

clean:
	make -C libs/libft clean

fclean: clean
	make -C libs/libft fclean
	rm -f minishell

re: fclean all

run: all
	./minishell

.PHONY: all clean fclean re run
