M I N I S H E L L

![minishell mind map](https://github.com/pragmataW/minishell/blob/master/plans%20for%20minishell/Screenshot%20from%202023-08-15%2017-50-23.png)
<br>
1- LEXER
<br>
We made lexer pace for split our input to commands. While doing this, we paid attention to quotations, special characters such as |, >, >>, <, <<. We have also separated these special characters and kept them in a linked list structure for easier access.
<br><br>
2- EXPANDER
<br>
As we can understand from the name in this pace we expanded $ENV_KEYS, tilda (~) and deleted quote signs for print or use them. While we do this paid attention for quote hierarchy. For example: <br>
  "$USER" -> pragmataW <br>
  '$USER' -> $USER <br>
  "hello'world'!" -> hello'world'! <br>
<br>
3- PARSER <br>
In this pace we create a command table for execve function. In this command table have 4 attribute. <br>
  1 - cmd_path = it's important for execve function. For exemple when we execute "ls" command our shell search for ls command's executable path like "/bin/ls" because ls is actually a program like our programs. The pats are in the $PATH variables. Even if you unset $PATH variable u cant execute any commands in bash (don't try this).<br>
  2- full_cmd = it's for execve function -btw, execve function is execute some shell commands in c code-. The second parameter of the execve function is which command will be executed in the path we give in the first parameter. For example i will execute ls -a in the /bin/ls. <br>
  3- infile = We use this for redirec and heredoc (<, <<) In this case we redirec our program's input to specified file in executer pace. If there is a heredoc or redirec i'm opening a file and give file's descriptor to infile attribute. <br>
  4- outfile = We use this for redirec like >> or >. In this case we redirec our program output to the specified file in executer pace. So if there is a redirec i'm opening a file and give file's descriptor to outfile attribute. <br>
<br>
4- EXECUTER <br>
We are ready for execute our commands. We can call execve functions. But we should now some tricks. Firstly after we called execve function, our process self-destructs. So we must open a new child process and call the execve function in here.<br>
Also we should made our pipe and redirec struct. For example when we try to execute ls -a | wc -l, ls should be another process, wc should be another process. And ls's output should be wc's input. For this we use "dup2" and "pipe" functions.<br>
For redirec we should control command table's infile and output attributes. If they are not normal values we should use dup2 like dup2(infile, STDINFILENO) or dup2(outfile, STDOUTFILENO)<br>
then we can execute our commands. We have some built-in functions like echo, pwd, cd etc. If our commands are built'in, i called my own built-in execve function, if our command is not built'in i called default execve function for execute.
