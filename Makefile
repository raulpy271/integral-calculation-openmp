
CC=gcc
FLAGS=-fopenmp

clean:
	rm -rf build/integral.o

run:
	$(CC) $(FLAGS) integral.c -o build/integral.o
	./build/integral.o

