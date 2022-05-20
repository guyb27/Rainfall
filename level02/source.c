#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *p(void)
{
    void *retaddr;
    void *ebp;
    char src[76];
    
    fflush(stdout);
    gets(&src);
    if (((uint32_t)retaddr & 0xb0000000) == 0xb0000000) {
        printf("(%p)\n", retaddr);
        exit(1);
    }
    puts(&src);
    retaddr = strdup(&src);
    return retaddr;
}

void main(void) {
    p();
    return;
}
