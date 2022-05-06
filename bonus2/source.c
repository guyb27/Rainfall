#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int language = 0x2;

// "Hyvää päivää "

int greetuser(int *var_1) {
    int var_2[18]; // 72 bytes

    if (language == 0x1) {
        // var_2[1:19] = "Hyvää päivää " 19 bytes
        var_2[0] = 0xc3767948;
        var_2[1] = 0x20a4c3a4;
        var_2[2] = 0x69a4c370;
        var_2[3] = 0xc3a4c376;
        var_2[4] = 0x0020a4;
    } else if (language == 0x2) {
        // var_2[1:18] = "Goedemiddag! " 14 bytes
        var_2[0] = 0x64656f47;
        var_2[1] = 0x64696d65;
        var_2[2] = 0x21676164;
        var_2[3] = 0x0020;
    } else {
        // var_2[1:7] = "Hello " 7 bytes
        var_2[0] = 0x6c6c6548;
        var_2[1] = 0x00206f;
    }

    // char *hello = "Hello ";
    strcat((char *)var_2, (char *)var_1);

    puts((const char *)var_2);
    return 1;
}

int main(int argc, char *argv[]) {
    // char buf[76];
    char *lang;
    int var_1[26]; // 104 bytes

    if (argc != 3) {
        return (1);
    }

    for (int i = 0; i < 19; i += 1) {
        var_1[i] = 0;
    }

    strncpy((char *)&var_1[0], argv[1], 40);
    strncpy((char *)&var_1[10], argv[2], 32); // fill until var_1[18]

    if ((lang = getenv("LANG")) != NULL) {
        if (memcmp(lang, "fi", 2) == 0) {
            language = 0x1;
        } else if (memcmp(lang, "nl", 2) == 0) {
            language = 0x2;
        }
    }

    greetuser(var_1);

    return 0;
}