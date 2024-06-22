// * Hex-Rays decompilator
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char	*auth;
int		service;

int	main(int argc, const char **argv)
{
	char input[5];
	char v5[2];
	char v6[129];

	while (1)
	{
		printf("%p, %p \n", auth, (const void *)service);
		if (!fgets(input, 128, stdin))
			break ;
		if (!memcmp(input, "auth ", 5))
		{
			auth = malloc(4);
			*auth = 0;
			if (strlen(v5) <= 30)
				strcpy(auth, v5);
		}
		if (!memcmp(input, "reset", 5))
			free(auth);
		if (!memcmp(input, "service", 6))
			service = (int) strdup(v6);
		if (!memcmp(input, "login", 5))
		{
			if (*(auth + 0x20))
				system("/bin/sh");
			else
				fwrite("Password:\n", 1, 10, stdout);
		}
	}
	return (0);
}