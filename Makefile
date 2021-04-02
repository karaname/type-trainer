typp: main.o texts.o
	gcc `pkg-config ncursesw --libs --cflags` -Wall -g3 -o typp main.o texts.o -lncurses

main.o: main.c
	gcc `pkg-config ncursesw --libs --cflags` -Wall -g3 -c main.c

texts.o: texts.c
	gcc -Wall -g3 -c texts.c

clean:
	rm *.o
