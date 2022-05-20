#include <stdio.h>

void o(void)
{
    system("/bin/sh");
    exit(1);
}

void n(void)
{
    char *src;
    
    fgets(&src, 512, stdin);
    printf(&src);
    exit(1);
}

void main(void)
{
    n();
    return;
}
