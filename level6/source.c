#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef void (*ptrFonction)(void);

void	n(void)
{
	system("/bin/cat /home/user/level7/.pass");
	return ;
}

void	m(void)
{
	puts("Nope");
	return ;
}

void	main(int argc, char **argv)
{
	char *dest;
	ptrFonction *f;

	dest = (char *)malloc(0x40);
	f = (ptrFonction *) malloc(4);
	f = &m;
	strcpy(dest, argv[1]);
	(*f)();
	return ;
}