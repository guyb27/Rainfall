#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int language = 0x2;

// "Hyvää päivää "

int greetuser(char *buf) {
	//Save $eip address: 0xbffff48c
    int buff[72];

    if (language == 0x1) {
        // buff[1:19] = "Hyvää päivää " 19 bytes
        buff[0] = 0xc3767948;
        buff[1] = 0x20a4c3a4;
        buff[2] = 0x69a4c370;
        buff[3] = 0xc3a4c376;
        buff[4] = 0x0020a4;
    } else if (language == 0x2) {
        // buff[1:18] = "Goedemiddag! " 14 bytes
        buff[0] = 0x64656f47;
        buff[1] = 0x64696d65;
        buff[2] = 0x21676164;
        buff[3] = 0x0020;
    } else {
        // buff[1:7] = "Hello " 7 bytes
        buff[0] = 0x6c6c6548;
        buff[1] = 0x00206f;
    }

    strcat((char *)buff, buf);//buff address:0xbffff440, $eip address: 0xbffff48c
    puts((const char *)buff);
    return(0);
}

int main(int argc, char *argv[]) {
    char buf[76];
    char *lang;

    if (argc != 3)
        return (1);

    memset(buf, 0, 76);
    
    strncpy(buf, argv[1], 40);
    strncpy(&buf[40], argv[2], 32);

    if ((lang = getenv("LANG")) != NULL) {
        if (memcmp(lang, "fi", 2) == 0) {
            language = 0x1;
        } else if (memcmp(lang, "nl", 2) == 0) {
            language = 0x2;
        }
    }

    greetuser(buf);

    return(0);
}
