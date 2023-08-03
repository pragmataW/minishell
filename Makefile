all: 
	make bonus -C ./libft
	cp ./libft/libft.a .
	gcc -o minishell *.c ./1-lexer/*.c ./2-expander/*.c ./3-parser/*.c ./4-executer/*.c -lreadline -L /goinfre/homebrew/opt/readline/lib libft.a

debug:
	make bonus -C ./libft
	cp ./libft/libft.a .
	gcc minishell.c -g -o minishell ./1-lexer/*.c ./2-expander/*.c ./3-parser/*.c ./4-executer/*.c -lreadline -L /goinfre/homebrew/opt/readline/lib libft.a

clean:
	rm -rf minishell
	rm -rf ./libft/*.o

fclean: clean
	rm -rf ./libft/libft.a
	rm -rf libft.a

re: fclean all

norm:
	norminette

git:
	rm -rf .vscode
	make fclean
	git add .
	git commit -m "unfinished yet"
	git push
