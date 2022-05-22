#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void o(void)
{
    system("/bin/sh");
    exit(1);
}

void n(void)
{
    char src[520];
    
    fgets(src, 512, stdin);
    printf(src);
    exit(1);
}

void main(void)
{
    n();
    return(0);
}
