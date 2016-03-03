shell: main.c shell.c parser.c env.c builtin.c
	gcc -o shell *.c
