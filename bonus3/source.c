#include <stdio.h>

int   main(int argc, char **argv)
{
    char str[132];
    FILE *fd;

    fd = fopen("/home/user/end/.pass", "r");
    memset(str, 0, sizeof(str));
    if (!fd || argc != 2 )
        return -1;
    fread(str, 1, 66, fd);
    str[65] = 0;
    str[atoi(argv[1])] = 0;
    fread(str + 66, 1, 65, fd);
    fclose(fd);
    if (!strcmp(str, argv[1]))
        execl("/bin/sh", "sh", 0);
    else
        puts(str + 66);
    return 0;
}