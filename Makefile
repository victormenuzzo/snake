all:
	gcc snake.c queue.c principal.c ordena.c menu.c -o sn -lncurses && ./sn ranking.txt
