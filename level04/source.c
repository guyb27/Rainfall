#include <stdio.h>

int m = 0;

void p(char *src)
{
    printf(src);
    return;
}

void n(void)
{
    char *s;
    
    fgets(&s, 512, stdin);
    p((char *)&s);
    if (m == 16930116) {
        system("/bin/cat /home/user/level5/.pass");
    }
    return;
}

void main(void)
{
    n();
    return;
}
