Here we have still our user input in the first argument of printf, I do not see other thing.

When I do the "info functions" command in gdb, we can see the function "o" who is never called.
If we examine it, we can see, it call system, uhmm, interesting...

To see the argument to system, we break at *n+54 and jump at *o+0 and break again at o+13.
Okay system have as argument "/bin/sh".

We execute my "loop_address.py" script and I found my user input as write in the fourth Direct Access Parameter

If we see the global offset table (global_offset_table.png), with "objdump -R level5" we can see the address to the exit fonction who is called at *n+61, we can overwrite this value to put the "o" function address to jump to the "o" function when the address of exit is call

the "o" function address is "0x080484a4" it's 134513828 in base 10 we sub 4 for the 4 first byte of the destination address.

We can execute this cammand to have a shell with the level6 user right to get the flag:
(python -c 'print "\x38\x98\x04\x08" + "%134513824x" + "%4$n"';cat) | ./level5
