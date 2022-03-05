
CC=gcc
FLAGS=-fopenmp -lm

clean:
	rm -rf build/integral.o

run:
	$(CC) -o build/integral.o integral.c $(FLAGS)
	./build/integral.o

