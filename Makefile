typp: main.o texts.o
	gcc -g3 -o typp main.o texts.o -lncurses

main.o: main.c
	gcc -g3 -c main.c

texts.o: texts.c
	gcc -g3 -c texts.c
