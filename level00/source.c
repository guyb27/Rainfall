// level 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define _GNU_SOURCE
#include <unistd.h>

int main(int argc, char **argv) {
  int arg;
  char *binsh;
  int gid;
  int uid;

  arg = atoi(argv[1]);
  if (arg == 0x1a7) {
    binsh = strdup("/bin/sh");

    gid = getegid();
    uid = geteuid();

    setresgid(gid, gid, gid);
    setresuid(uid, uid, uid);

    execv("/bin/sh", &binsh);
  } else {
    fwrite("No !\n", 1, 5, stderr);
  }
  return 0;
}