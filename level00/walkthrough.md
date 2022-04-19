# level0

The program segfault without arguments and print `No!` with any value :

```bash
level0@RainFall:~$ ./level0
Segmentation fault (core dumped)
level0@RainFall:~$ ./level0 1222
No !
level0@RainFall:~$ ./level0 12asxz
No !
```

At `main+20`, we can see that the program does an `atoi` on the command line parameter and compare it with `0x1a7` (`423` in decimal) at `main+25` :

```assembly
   0x08048ec9 <+9>:     mov    eax,DWORD PTR [ebp+0xc]
   0x08048ecc <+12>:    add    eax,0x4
   0x08048ecf <+15>:    mov    eax,DWORD PTR [eax]
   0x08048ed1 <+17>:    mov    DWORD PTR [esp],eax
   0x08048ed4 <+20>:    call   0x8049710 <atoi>
   0x08048ed9 <+25>:    cmp    eax,0x1a7
```

If it is equals, we can see at `main+145` that the programm run a shell with `/bin/sh` as argument :

``` assembly
   0x08048f4a <+138>:   mov    DWORD PTR [esp],0x80c5348
   0x08048f51 <+145>:   call   0x8054640 <execv>
```

```bash
(gdb) x/s 0x80c5348
0x80c5348:  "/bin/sh"
```

Get the flag :

```bash
level0@RainFall:~$ ./level0 423
$ whoami
level1
$ cd ../level1
$ cat .pass
1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
```
