all:
	gcc -o myasshole hello.c -ldl -lm -llua `sdl2-config --cflags --libs`  
	./myasshole
