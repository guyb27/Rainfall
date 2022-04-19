// level 1

#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

void run(void)
{
    fwrite("Good... Wait what?\n", 1, 13, stdout);
    system("/bin/sh");
    return;
}

int main(void)
{
    char str[76];

    gets(str);
    return 0;
}
