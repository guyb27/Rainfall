#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void t_ft(void);

void n(void)
{
    system("/bin/cat /home/user/level7/.pass");
    return;
}

void m(void)
{
    puts("Nope");
    return;
}

int main(int argc, char **argv)
{
    void *p1;
    t_ft *p2;
    
    p1 = malloc(64);
    p2 = malloc(4);
    p2 = &m;
    strcpy(p1, argv[1]);
    (*p2)();
    return(0);
}
