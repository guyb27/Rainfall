#include <stdio.h>

char *service;
char *auth;

int main()
{
	char src[128];
	
	while(1)
	{
		printf("%p, %p\n", auth, service);
		if (!fgets(src, 128, stdin))
			break;
		if (!strncmp(src, "auth ", 5))
		{
			auth = malloc(4);
            auth = NULL;
			if (strlen(src) <= 30)
				strcpy(auth, &src[5]);
		}
		if (!strncmp(src, "reset", 5))
			free(auth);
		if (!strncmp(src, "service", 7))
			service = strdup(&src[7]);
		if (!strncmp(src, "login", 5))
		{
			if (auth[32] != 0)
				system("/bin/sh");
			else
				puts("Password:");
		}
	}
	return (0);
}

