#include <string.h>

void p(char *str, char *text)
{
    char buf[4104];

    puts(text);
    read(0, buf, 4096);
    *(strchr(buf, '\n')) = '\0';
    strncpy(str, buf, 20);
}

void pp(char *str)
{
    char str1[20];
    char str2[20];
    unsigned int i = 4294967295;

    p(str1, " - ");
    p(str2, " - ");
    strcpy(str, str1);
    char *cpy = str;
    while (i--)
    {
        if (cpy[0] == '\0')
            break;
        cpy += 1;
    }
    str[(4294967295 - i) + 1] = ' ';
    strcat(str, str2);
}

int main()
{
    char c[54];

    pp(c);
    puts(c);
    return 0;
}