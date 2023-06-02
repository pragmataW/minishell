all: 
	make -C ./libft
	cp ./libft/libft.a .
	gcc minishell.c ./lexer/*.c -lreadline -L /goinfre/homebrew/opt/readline/lib libft.a

clean:
	rm -rf a.out

fclean: clean
	rm -rf ./libft/libft.a
	rm -rf libft.a

re: fclean all

norm:
	norminette