all: 
	make bonus -C ./libft
	cp ./libft/libft.a .
	gcc minishell.c ./lexer/*.c ./expander/*.c -lreadline -L /goinfre/homebrew/opt/readline/lib libft.a

debug:
	make -C ./libft
	cp ./libft/libft.a .
	gcc minishell.c -g ./lexer/*.c ./expander/*.c -lreadline -L /goinfre/homebrew/opt/readline/lib libft.a

clean:
	rm -rf a.out
	rm -rf ./libft/*.o

fclean: clean
	rm -rf ./libft/libft.a
	rm -rf libft.a

re: fclean all

norm:
	norminette
