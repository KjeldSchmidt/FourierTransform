CC=gcc
CFLAGS=-Wall -Werror -pedantic-errors -g --std=c99  -Wextra

fft: fft.o

fft.o: fft.h fft.c

clean:
	-rm *.o *~
