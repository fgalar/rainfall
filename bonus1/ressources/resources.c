#include <stdio.h>
#include <stdlib.h>

int main(int ac, char *av[])
{
	int n;

	n = atoi(av[1]);
	printf("atoi %d\n", n);
	printf("unsigned:  %u\n", (size_t)n * 4);

	return 0;
}