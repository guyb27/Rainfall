# ASM

`p`

```assembly
   0x080484d4 <+0>:	    push   ebp                      # Push Base Pointer on top of the stack   
   0x080484d5 <+1>:	    mov    ebp,esp                  # Top Stack Pointer points on Base Pointer
   0x080484d7 <+3>:	    sub    esp,0x68                 # Allocate 104 bytes for the current stack frame
   0x080484da <+6>:	    mov    eax,ds:0x8049860         # Move the value of 0x8049860 to eax (stdout)
   0x080484df <+11>:	mov    DWORD PTR [esp],eax      # esp points to eax
   0x080484e2 <+14>:	call   0x80483b0 <fflush@plt>   # Call to fflush (so eax, so stdout)
   0x080484e7 <+19>:	lea    eax,[ebp-0x4c]           # eax is now at ebp-76
   0x080484ea <+22>:	mov    DWORD PTR [esp],eax      # esp points on eax (ebp-76) (28 bytes are left from the top of the stack)
   0x080484ed <+25>:	call   0x80483c0 <gets@plt>     # Call to gets
   0x080484f2 <+30>:	mov    eax,DWORD PTR [ebp+0x4]  # eax address become value of ebp+4 (value of eip)
   0x080484f5 <+33>:	mov    DWORD PTR [ebp-0xc],eax  # ebp-12 value now become eax address
   0x080484f8 <+36>:	mov    eax,DWORD PTR [ebp-0xc]  # eax address now become ebp-12 value (eax is already ebp-12)
   0x080484fb <+39>:	and    eax,0xb0000000           # AND operand on eax address
   0x08048500 <+44>:	cmp    eax,0xb0000000           # COMPARE operand on eax address
   0x08048505 <+49>:	jne    0x8048527 <p+83>         # JUMP on p+83 if not equal
   0x08048507 <+51>:	mov    eax,0x8048620            
   0x0804850c <+56>:	mov    edx,DWORD PTR [ebp-0xc]
   0x0804850f <+59>:	mov    DWORD PTR [esp+0x4],edx
   0x08048513 <+63>:	mov    DWORD PTR [esp],eax
   0x08048516 <+66>:	call   0x80483a0 <printf@plt>
   0x0804851b <+71>:	mov    DWORD PTR [esp],0x1
   0x08048522 <+78>:	call   0x80483d0 <_exit@plt>
   0x08048527 <+83>:	lea    eax,[ebp-0x4c]           # eax is now at ebp-76 (beginning of buffer from gets)
   0x0804852a <+86>:	mov    DWORD PTR [esp],eax      # esp points on eax (ebp-76)
   0x0804852d <+89>:	call   0x80483f0 <puts@plt>     # Call puts
   0x08048532 <+94>:	lea    eax,[ebp-0x4c]           # eax is now at ebp-76
   0x08048535 <+97>:	mov    DWORD PTR [esp],eax      # esp points on eax (ebp-76)
   0x08048538 <+100>:	call   0x80483e0 <strdup@plt>   # Call strdup
   0x0804853d <+105>:	leave
   0x0804853e <+106>:	ret
```
