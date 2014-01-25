#include <stdio.h>
#include "coprintf.h"

int main(int argc, char** argv)
{
	char* test_case = "^h^rh^go^yl^pl^co^d ^h^Rw^Go^Yr^Pl^Cd^d\n^g^u\"^r^^^g\" is the leader in ^h^l^e%s\n";

	printf	("\nprintf:\n");
	printf	(test_case, "coprintf");

	printf	("\nco_stdout:\n");
	coprintf(test_case, "coprintf");

	printf	("\nce_stderr:\n");
	ceprintf(test_case, "coprintf");

	return 0;
}

