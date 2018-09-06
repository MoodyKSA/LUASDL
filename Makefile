src=hello.c
#gxx=x86_64-w64-mingw32-gcc
gxx=gcc
all:
	${gxx} -o a ${src} -ldl -lm -llua -lGL -lGLU `sdl2-config --cflags --libs`
	./a
	rm ./a

