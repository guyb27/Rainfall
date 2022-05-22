#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
	FILE *file;
	char str[136];

	file = fopen("/home/user/end/.pass", "r");
	memset(str, 0, 132);

	if (file == 0 || argc != 2)
		return (1);

	fread(str, 1, 66, file);
	str[65] = 0;
	str[atoi(argv[1])] = 0;
	fread(&str[66], 1, 65, file);

	fclose(file);

	if (strcmp(str, argv[1]) == 0)
		execl("/bin/sh", "sh", 0);
	else
		puts(&str[66]);

	return (0);
}
