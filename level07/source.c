#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct s_buffer {
    int i;
    int *j;
}   t_buffer;

char	c[68];

void	m(void) {
	printf("%s - %ld\n", c, time(0));
}

int		main(int argc, const char *argv[]) {
    t_buffer *buf_1;
    t_buffer *buf_2;

    buf_1 = malloc(sizeof(t_buffer));
    buf_1->i = 0x1;
    buf_1->j = malloc(8);

    buf_2 = malloc(sizeof(t_buffer));
    buf_2->i = 0x2;
    buf_2->j = malloc(8);

    strcpy((char *)buf_1->j, argv[1]);
    strcpy((char *)buf_2->j, argv[2]);

    fgets(c, 68, fopen("/home/user/level8/.pass", "r"));

    puts("~~");
    return 0;
}