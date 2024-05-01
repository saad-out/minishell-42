I = -L /Users/klakbuic/readline/lib
FLAGS := -fsanitize=address -g3
LIBS := libs/libft/libft.a

all:
	cc -Wall -Wextra src/*.c src/lexer/*.c src/parser/*.c src/executor/*.c src/environment/*.c \
	src/builtins/*.c src/utils/*.c src/expander/*.c src/memory/*.c src/libs/*.c $(I) \
	-o minishell  -lreadline \
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
