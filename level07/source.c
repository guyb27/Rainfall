#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

char	c[68];

void	m(void) {
	printf("%s - %d\n", c, (int)time(0));
}

int		main(int ac, const char **av) {
    int *v1 = malloc(8); // 0x0804a008
    v1[0] = 0x1;

    int *v2 = malloc(8); // 0x0804a018
    v1[1] = v2;

    int *v3 = malloc(8); // 0x804a028
    v3[0] = 0x2;

    int *v4 = malloc(8); // 0x804a038
    v3[1] = v4;

    char *arg1 = av[1];

    ft_strcpy(v2, arg1);
    ft_strcpy(v4, arg1);
}