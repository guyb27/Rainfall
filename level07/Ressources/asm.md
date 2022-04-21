# ASM

`main`

```assembly
   0x08048521 <+0>:     push   ebp                      # Push Base Pointer
   0x08048522 <+1>:     mov    ebp,esp                  # Set ebp to esp
   0x08048524 <+3>:     and    esp,0xfffffff0           # Align stack
   0x08048527 <+6>:     sub    esp,0x20                 # Allocate 32 bytes
   0x0804852a <+9>:     mov    DWORD PTR [esp],0x8      # Set 8 as value of esp
   0x08048531 <+16>:    call   0x80483f0 <malloc@plt>   # Call malloc
   0x08048536 <+21>:    mov    DWORD PTR [esp+0x1c],eax # Set return malloc on esp+28
   0x0804853a <+25>:    mov    eax,DWORD PTR [esp+0x1c] # Set esp+28 on eax
   0x0804853e <+29>:    mov    DWORD PTR [eax],0x1      # Set 1 as value of eax (esp+28)
   0x08048544 <+35>:    mov    DWORD PTR [esp],0x8      # Set 8 as value esp
   0x0804854b <+42>:    call   0x80483f0 <malloc@plt>   # Call malloc
   0x08048550 <+47>:    mov    edx,eax                  # Set eax (0x0804a018) to edx
   0x08048552 <+49>:    mov    eax,DWORD PTR [esp+0x1c] # Set esp+28 as value of eax (0x0804a008)
   0x08048556 <+53>:    mov    DWORD PTR [eax+0x4],edx  # Set edx as value of eax+4 (0x804a00c:0x0804a018)
   0x08048559 <+56>:    mov    DWORD PTR [esp],0x8      # Set 8 as value of esp
   0x08048560 <+63>:    call   0x80483f0 <malloc@plt>   # Call Malloc
   0x08048565 <+68>:    mov    DWORD PTR [esp+0x18],eax # Set eax(0x804a028) to esp+24
   0x08048569 <+72>:    mov    eax,DWORD PTR [esp+0x18] # Set esp+24 value to eax
   0x0804856d <+76>:    mov    DWORD PTR [eax],0x2      # Set 2 to eax value (0x804a028)
   0x08048573 <+82>:    mov    DWORD PTR [esp],0x8      # Set 8 to esp value
   0x0804857a <+89>:    call   0x80483f0 <malloc@plt>   # Call malloc
   0x0804857f <+94>:    mov    edx,eax                  # Set eax(0x804a038) to edx
   0x08048581 <+96>:    mov    eax,DWORD PTR [esp+0x18] # Set eax+24(0x0804a028) to eax
   0x08048585 <+100>:   mov    DWORD PTR [eax+0x4],edx  # Set edx(0x804a038) to eax+4 value (0x0804a028 + 4 bytes)
   0x08048588 <+103>:   mov    eax,DWORD PTR [ebp+0xc]  # Set ebp+12 value to eax
   0x0804858b <+106>:   add    eax,0x4                  # Add 4 bytes to eax
   0x0804858e <+109>:   mov    eax,DWORD PTR [eax]      # Set eax value to eax (get the first arg param)
   0x08048590 <+111>:   mov    edx,eax                  # Set eax to edx
   0x08048592 <+113>:   mov    eax,DWORD PTR [esp+0x1c] # Set esp+28(val: 0x0804a008) to eax
   0x08048596 <+117>:   mov    eax,DWORD PTR [eax+0x4]  # Set eax to eax+4 (0x0804a018)
   0x08048599 <+120>:   mov    DWORD PTR [esp+0x4],edx  # Set edx to esp+4 value (first arg param)
   0x0804859d <+124>:   mov    DWORD PTR [esp],eax      # Set eax(0x0804a018) to esp value
   0x080485a0 <+127>:   call   0x80483e0 <strcpy@plt>   # Call strcpy
   0x080485a5 <+132>:   mov    eax,DWORD PTR [ebp+0xc]  # Set ebp+12 value to eax
   0x080485a8 <+135>:   add    eax,0x8                  # Add 8 bytes to eax
   0x080485ab <+138>:   mov    eax,DWORD PTR [eax]      # Set eax value to eax (get the second arg param)
   0x080485ad <+140>:   mov    edx,eax                  # Set eax to edx
   0x080485af <+142>:   mov    eax,DWORD PTR [esp+0x18] # Set esp+24(0x0804a028) to eax
   0x080485b3 <+146>:   mov    eax,DWORD PTR [eax+0x4]  # Set eax+4 value(0x804a038) to eax
   0x080485b6 <+149>:   mov    DWORD PTR [esp+0x4],edx  # Set edx to esp+4 value (second arg param)
   0x080485ba <+153>:   mov    DWORD PTR [esp],eax      # Set eax(0x804a038) to esp value
   0x080485bd <+156>:   call   0x80483e0 <strcpy@plt>   # Call to strcpy
   0x080485c2 <+161>:   mov    edx,0x80486e9            # Set 0x80486e9 to edx
   0x080485c7 <+166>:   mov    eax,0x80486eb            # Set 0x80486eb to eax
   0x080485cc <+171>:   mov    DWORD PTR [esp+0x4],edx  # Set edx to esp+4
   0x080485d0 <+175>:   mov    DWORD PTR [esp],eax      # eax to esp
   0x080485d3 <+178>:   call   0x8048430 <fopen@plt>    # Call fopen
   0x080485d8 <+183>:   mov    DWORD PTR [esp+0x8],eax  # Set eax to esp+8
   0x080485dc <+187>:   mov    DWORD PTR [esp+0x4],0x44 # Set 68 to esp+4
   0x080485e4 <+195>:   mov    DWORD PTR [esp],0x8049960 # Set 0x8049960 (c variable) to esp
   0x080485eb <+202>:   call   0x80483c0 <fgets@plt>    # Call fgets
   0x080485f0 <+207>:   mov    DWORD PTR [esp],0x8048703 #
   0x080485f7 <+214>:   call   0x8048400 <puts@plt>
   0x080485fc <+219>:   mov    eax,0x0
   0x08048601 <+224>:   leave  
   0x08048602 <+225>:   ret 
```
