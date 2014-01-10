all: clean test

test:
	gcc -Wall -o demo_bin demo.c coprintf.c
clean:
	-@rm demo_bin
