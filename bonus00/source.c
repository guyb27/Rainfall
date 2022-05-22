
void p(char *buf, char *dash) {
    char s[4096];
    char *schr;

    puts(dash);
    read(0, s, 4096);
    schr = strchr(s, 10);
    *schr = 0x0;
    strncpy(buf, s, 20);
    return;
}

void pp(char *src) {
    int buf1[20];
    int buf2[21];

    p(buf1, " - ");
    p(&buf2[1], " - ");

    strcpy(src, buf1);
    buf2[0] = " ";
    strcat(&src[strlen(src)], buf2);
    return;
}

int main() {
    char src[42];

    pp(src);
    puts(src);

    return (0);
}
