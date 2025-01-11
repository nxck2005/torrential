main: main.c
	$(CC) main.c -o ./build/torrential -Wall -Wextra -pedantic -std=c99 -lncurses
	