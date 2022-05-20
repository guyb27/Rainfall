
void p(char *buf, char *dash) {
    char s[4000];
    char *schr;

    puts(dash);
    read(0, s, 4096);
    schr = strchr(s, 10);
    *schr = 0x0;
    strncpy(buf, s, 20);
}

void pp(char *buf) {
    int buff_1[4];
    int buff_2[4];

    p(buff_1, " - ");
    p(buff_2, " - ");

	strcpy(buf, buff_1);

    int len = strlen(buf);
    buf[len] = ' ';

    strcat(buf, buff_2);
}

void main() {
    char buf_0[42];

    pp(buf_0);
    puts(buf_0);
}