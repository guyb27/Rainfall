#include <stdio.h>

int m = 0;

void v(void)
{
    char *src;
    
    fgets(&src, 500, stdin);
    printf(&src);
    if (m == 64) {
        fwrite("Wait what?!\n", 1, 12, stdout);
        system("/bin/sh");
    }
    return;
}

void main(void)
{
    v();
    return;
}
