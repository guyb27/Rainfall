# ASM

`main`

```assembly
   0x0804851a <+0>:     push   ebp
   0x0804851b <+1>:     mov    ebp,esp
   0x0804851d <+3>:     and    esp,0xfffffff0
   0x08048520 <+6>:     call   0x80484a4 <v>
   0x08048525 <+11>:    leave  
   0x08048526 <+12>:    ret 
```

`v`

```assembly
   0x080484a4 <+0>:     push   ebp                          # Push Base Pointer
   0x080484a5 <+1>:     mov    ebp,esp                      # Push Top Stack Pointer
   0x080484a7 <+3>:     sub    esp,0x218                    # Allocate 536 Bytes for the current stack frame
   0x080484ad <+9>:     mov    eax,ds:0x8049860             # Put stdin in eax
   0x080484b2 <+14>:    mov    DWORD PTR [esp+0x8],eax      # Set eax (stdin) in esp+8 ()
   0x080484b6 <+18>:    mov    DWORD PTR [esp+0x4],0x200    # Set 512 in esp+4
   0x080484be <+26>:    lea    eax,[ebp-0x208]              # Set eax to ebp-520
   0x080484c4 <+32>:    mov    DWORD PTR [esp],eax          # esp now points on eax
   0x080484c7 <+35>:    call   0x80483a0 <fgets@plt>        # Call fgets
   0x080484cc <+40>:    lea    eax,[ebp-0x208]              # Set eax to ebp-520
   0x080484d2 <+46>:    mov    DWORD PTR [esp],eax          # esp now points on eax (ebp-520)
   0x080484d5 <+49>:    call   0x8048390 <printf@plt>       # Call printf
   0x080484da <+54>:    mov    eax,ds:0x804988c             # Set m variable in eax
   0x080484df <+59>:    cmp    eax,0x40                     # Compare eax (return of m function) and 64
   0x080484e2 <+62>:    jne    0x8048518 <v+116>            # Jump to v+116 if not equals
   0x080484e4 <+64>:    mov    eax,ds:0x8049880             # Set stdout to eax
   0x080484e9 <+69>:    mov    edx,eax                      # Set eax to edx
   0x080484eb <+71>:    mov    eax,0x8048600                # Set "Wait what?!\n" to eax
   0x080484f0 <+76>:    mov    DWORD PTR [esp+0xc],edx      # Set edx to to esp+12
   0x080484f4 <+80>:    mov    DWORD PTR [esp+0x8],0xc      # Set 12 to esp+8
   0x080484fc <+88>:    mov    DWORD PTR [esp+0x4],0x1      # Set 1 to esp+4
   0x08048504 <+96>:    mov    DWORD PTR [esp],eax          # Set eax to esp
   0x08048507 <+99>:    call   0x80483b0 <fwrite@plt>       # Call fwrite
   0x0804850c <+104>:   mov    DWORD PTR [esp],0x804860d    # Set "/bin/sh" to esp
   0x08048513 <+111>:   call   0x80483c0 <system@plt>       # Call system
   0x08048518 <+116>:   leave  
   0x08048519 <+117>:   ret 
```
