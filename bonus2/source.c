#include <string.h>

extern unsigned int language;
char l1[] = "Hyvää päivää ";


int  greetuser(char *src)
{
  char *dest;

  switch (language)
  {
    case 1:
        dest = l1;
        break;
    case 2:
        strcpy(dest, "Goedemiddag! ");
        break;
    case 0:
        strcpy(dest, "Hello ");
        break;
  }
  strcat(dest, src);
  puts(dest);
}

int main(int argc, char **argv)
{
    char dest[76];
    char *env;

    if ( argc != 3 )
      return 1;
    memset(dest, 0, sizeof(dest));
    strncpy(dest, argv[1], 40);
    strncpy(dest + 40, argv[2], 32);
    env = getenv("LANG");
    if (env)
    {
      if (!memcmp(env, "fi", 2))
      {
          language = 1;
      }
      else if (!memcmp(env, "nl", 2))
      {
          language = 2;
      }
    }
    greetuser(dest);
}