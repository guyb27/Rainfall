#Format string  
  
As you can see on the "disassembled.png" picture, in red at *v+62 we have a conditional jump to execute a shell or leave the progam.  


At *v+54 we mov 0x0804988c in eax and for execute the the need 0x40 (64)

As you can see on the "v\_54\_0x0804988c\_value.png" picture we have 0x0 at the "0x0804988c" address.  
  
But how can I change that !?  
  
In the man of printf in the bug section, you can see if print take an user input in first parameter, it's a security hole.

As you can see on the "printf\_parameter.png" picture, printf get the user input in the first parameter

To test if this security hole work we can pass "%x" in argument fo watch if printf print the first argument on the stack after our argument.

You can see the "proof\_printf\_security\_hole.png" picture, it's works, and we have get the number of the Direct Access Parameter to acces at our string.

If we jump manually to *v+62 from *v+64 and continue in gdb, we can see, it's execute a shell, we have to do that !

This printf security hole can modify the value to an address, in our case, it works like that:  
"\<address\_to\_modify>\<size\_to\_increment\_the\_address>\<Direct\_Access\_Parameter>"  

We can do that like this in gdb:  
  
run <<< $(python -c 'print "\x8c\x98\x04\x08" + "%60x" + "%4$n"')  
  
You can see that in the "GDB\_POC.png" picture.  
  
Ok, It's works, you can get the level4 user privilege and get the flag like that:  
(python -c 'print "\x8c\x98\x04\x08" + "%60x" + "%4$n"';cat) | ./level3
