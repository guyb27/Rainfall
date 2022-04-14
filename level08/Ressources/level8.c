#include <stdio.h>

char str_stdin[128];
//str_stdin: 0xffffd050
char *eax_str;
int eax_int;
int i;
char *malloc_1;
//malloc_1: 0x804a9c0
void *service;
//service: 0x8049ab0
void *auth;
//auth: 0x8049aac
//("auth "): 0x8048819 
//("reset"): 0x804881f
//("login"): 0x804882d
int main()
{
	while(1)
	{
		printf("%p, %p\n", auth, service);
		if (!fgets(str_stdin, 0x80, stdin))//128
			exit (0);
		if (!strncmp(str_stdin, "auth ", 5))
		{
			malloc_1 = malloc(4);
			auth = &malloc_1;
			if (strlen(str_stdin) <= 34)//29 max apres "auth ", mais cette condition est inutile, on peut ne pas rentrer dedans !
				strcpy(auth, str_stdin+5);//Le contenu ne nous interesse pas du tout !
		}
		if (!strncmp(str_stdin, "reset", 5))
			free(malloc_1);
		if (!strncmp(str_stdin, "service", 6))
		{
			*service = strdup(str_stdin+7);
		}
		if (!strncmp(str_stdin, "login", 5))
		{
			if (*service+0x20 != 0)//Le contenu de service+0x20!
				system("/bin/sh");
			else
				puts("Password:");
		}
	}
	return (0);
}

