#include <time.h>
#include <stdio.h>

char c[80];

typedef struct s_struct {
    unsigned int i;
    char *str;
} t_struct;

void	m(void)
{
	time_t	t;

	t = time(0);
	printf("%s - %d\n", c, t);
	return ;
}

int	main(int argc, char **argv)
{
	t_struct *s1;
	t_struct *s2;
	FILE *fd;

	s1 = malloc(sizeof(t_struct));
	s1->i = 1;
	s1->str = malloc(8);

	s2 = malloc(sizeof(t_struct));
	s2->i = 2;
	s2->str = malloc(8);

	strcpy(s1->str, argv[1]);
	strcpy(s2->str, argv[2]);

	fd = fopen("/home/user/level8/.pass", "r");
	fgets(c, 0x44, fd);
	puts("~~");
	return (0);
}