all: clean test

test:
	gcc -Wall -o demo_bin demo.c coprintf.c
	gcc -Wall -DCO_PRINTF_INACTIVE -o demo_bin_dis demo.c coprintf.c
clean:
	-@rm demo_bin demo_bin_dis &>/dev/null
