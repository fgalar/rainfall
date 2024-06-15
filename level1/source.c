#include <unistd.h>
#include <stdio.h>// type stdout


void run()
{
	fwrite("Good... Wait what?\n", 1, 19, stdout);
	system("/bin/sh");
}

int main(int argc, char **argv)
{
	char buffer[76];
	gets(buffer);
}
