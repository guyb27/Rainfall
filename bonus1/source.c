
int main(int argc, char *argv[]) {
	int n;
	int res;
	char buf[40];

	n = atoi(argv[1]);
	if (n > 9)
		return (1);

	memcpy(buf, argv[2], n * 4);

	if (res == 1464814662) {
		execl("/bin/sh", "sh", 0);
	}

	return(0);
}
