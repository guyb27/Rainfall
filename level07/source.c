#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

char	c[68];

void	m(void) {
	printf("%s - %ld\n", c, time(0));
}

int		main(int argc, const char *argv[]) {
    // int *v1 = (8); // 0x0804a008
    // v1[0] = 0x1;

    // int *v2 = malloc(8); // 0x0804a018
    // v1[1] = v2;

    // int *v3 = malloc(8); // 0x804a028
    // v3[0] = 0x2;

    // int *v4 = malloc(8); // 0x804a038
    // v3[1] = v4;

    // char *arg1 = av[1];
    int *i1 = malloc(8);
    i1[0] = 0x1;
    i1[1] = (int)malloc(8);

    int *i2 = malloc(8);
    i2[0] = 0x2;
    i2[1] = (int)malloc(8);

    strcpy((char *)i1[1], argv[1]);
    strcpy((char *)i2[1], argv[2]);

    puts("~~");
    return 0;
}