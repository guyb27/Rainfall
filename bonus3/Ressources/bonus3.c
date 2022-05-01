int main(int ac,char **av)
{
	char str[168];
	FILE *file;
	file = fopen("/home/user/end/.pass", "r");
	if (file != 2)
		return 1;
	if (ac != 2)
		return (1);
	fread(str, 1, 41, file);
	fclose(file);
	if (strcmp("", av[1]))
		execl("/bin/sh", "sh", 0);
	else
		puts("");
	return (0);
}
