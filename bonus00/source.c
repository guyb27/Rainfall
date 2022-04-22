
int p(char *buf, char *dash) {
    char s[4000];
    char *schr;

    puts(dash);
    read(0, s, 4096);
    schr = strchr(s, 10);
    *schr = 0x0;
    strncpy(buf, s, 20);
}

int pp(char *buf) {
    int buff_1[4];
    int buff_2[4];

    p(buff_1, " - ");
    p(buff_2, " - ");

}

int main() {
    char buf_0[42];

    pp(buf_0);
    puts(buf_0);

    return (0);
}