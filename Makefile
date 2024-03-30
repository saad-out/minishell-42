all:
	make -C libs/libft
	cc libs/libft/libft.a src/*.c src/lexer/*.c src/parser/*.c src/executor/*.c -o minishell -lreadline

clean:
	make -C libs/libft clean

fclean: clean
	make -C libs/libft fclean
	rm -f minishell

re: fclean all

run: all
	./minishell

.PHONY: all clean fclean re run
