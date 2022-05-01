# ASM

`main`

```assembly
   0x08048529 <+0>:     push   ebp                      # Push stack base pointer
   0x0804852a <+1>:     mov    ebp,esp                  # Set stack base pointer to stack pointer
   0x0804852c <+3>:     push   edi                      # Push destination pointer
   0x0804852d <+4>:     push   esi                      # Push source pointer
   0x0804852e <+5>:     push   ebx                      # Push base pointer
   0x0804852f <+6>:     and    esp,0xfffffff0           # Align stack on 16 (sub esp 12)
   0x08048532 <+9>:     sub    esp,0xa0                 # Alloc 160 bytes
   0x08048538 <+15>:    cmp    DWORD PTR [ebp+0x8],0x3  # Compare number of arguments and 3 
   0x0804853c <+19>:    je     0x8048548 <main+31>      # Jump to +31 if equal
   0x0804853e <+21>:    mov    eax,0x1                  # Set eax to 1
   0x08048543 <+26>:    jmp    0x8048630 <main+263>     # Jump to +263
   0x08048548 <+31>:    lea    ebx,[esp+0x50]           # Set ebx to esp+80 value
   0x0804854c <+35>:    mov    eax,0x0                  # Set 0 to eax
   0x08048551 <+40>:    mov    edx,0x13                 # Set 19 to edx
   0x08048556 <+45>:    mov    edi,ebx                  # Set ebx (esp+80) to edi
   0x08048558 <+47>:    mov    ecx,edx                  # Set edx (19) to ecx
   0x0804855a <+49>:    rep stos DWORD PTR es:[edi],eax # Repeat string operation : for ecx, store eax to edi, incrementing 4 bytes each time
   0x0804855c <+51>:    mov    eax,DWORD PTR [ebp+0xc]  # Get argv
   0x0804855f <+54>:    add    eax,0x4                  # Get argv+1
   0x08048562 <+57>:    mov    eax,DWORD PTR [eax]      # Derefence eax (now points on argv+1)
   0x08048564 <+59>:    mov    DWORD PTR [esp+0x8],0x28 # Set 40 to esp+8 (3th arg)
   0x0804856c <+67>:    mov    DWORD PTR [esp+0x4],eax  # Set eax (argv+1 string) to esp+4 (2nd arg)
   0x08048570 <+71>:    lea    eax,[esp+0x50]           # Set eax to esp+80 value
   0x08048574 <+75>:    mov    DWORD PTR [esp],eax      # Set eax to esp value
   0x08048577 <+78>:    call   0x80483c0 <strncpy@plt>  # Call strncpy
   0x0804857c <+83>:    mov    eax,DWORD PTR [ebp+0xc]  # Get argv
   0x0804857f <+86>:    add    eax,0x8                  # Get argv+2
   0x08048582 <+89>:    mov    eax,DWORD PTR [eax]      # Derefence eax (now points on argv+2)
   0x08048584 <+91>:    mov    DWORD PTR [esp+0x8],0x20 # Set esp+8 value to 32
   0x0804858c <+99>:    mov    DWORD PTR [esp+0x4],eax  # Set esp+4 value to eax (argv+2 string)
   0x08048590 <+103>:   lea    eax,[esp+0x50]           # Set eax to esp+80 value
   0x08048594 <+107>:   add    eax,0x28                 # Set eax to esp+120
   0x08048597 <+110>:   mov    DWORD PTR [esp],eax      # Set eax to esp value
   0x0804859a <+113>:   call   0x80483c0 <strncpy@plt>  # Call strncpy 
   0x0804859f <+118>:   mov    DWORD PTR [esp],0x8048738# Set "LANG" to esp value
   0x080485a6 <+125>:   call   0x8048380 <getenv@plt>   # Call getenv
   0x080485ab <+130>:   mov    DWORD PTR [esp+0x9c],eax # Set getenv return to esp+156 value
   0x080485b2 <+137>:   cmp    DWORD PTR [esp+0x9c],0x0 # Compare getenv return with 0
   0x080485ba <+145>:   je     0x8048618 <main+239>     # Jump to +239 if equal
   0x080485bc <+147>:   mov    DWORD PTR [esp+0x8],0x2  # 3th arg to 2
   0x080485c4 <+155>:   mov    DWORD PTR [esp+0x4],0x804873d # 2nd arg to "fi"
   0x080485cc <+163>:   mov    eax,DWORD PTR [esp+0x9c] # esp+156 value to eax
   0x080485d3 <+170>:   mov    DWORD PTR [esp],eax      # 1th arg to getenv return
   0x080485d6 <+173>:   call   0x8048360 <memcmp@plt>   # 
   0x080485db <+178>:   test   eax,eax                  # test if eax == 0
   0x080485dd <+180>:   jne    0x80485eb <main+194>     # jump to +194 if not true
   0x080485df <+182>:   mov    DWORD PTR ds:0x8049988,0x1 # 
   0x080485e9 <+192>:   jmp    0x8048618 <main+239>
   0x080485eb <+194>:   mov    DWORD PTR [esp+0x8],0x2  # 3th arg to 2
   0x080485f3 <+202>:   mov    DWORD PTR [esp+0x4],0x8048740 # 2nd arg to "nl"
   0x080485fb <+210>:   mov    eax,DWORD PTR [esp+0x9c] # esp+156 value to eax
   0x08048602 <+217>:   mov    DWORD PTR [esp],eax      # 1th arg to getenv return
   0x08048605 <+220>:   call   0x8048360 <memcmp@plt>
   0x0804860a <+225>:   test   eax,eax                  # test if eax == 0
   0x0804860c <+227>:   jne    0x8048618 <main+239>     # jump to +239 if not true
   0x0804860e <+229>:   mov    DWORD PTR ds:0x8049988,0x2 # 
   0x08048618 <+239>:   mov    edx,esp                  # set edx on top of stack
   0x0804861a <+241>:   lea    ebx,[esp+0x50]           # Set esp+80 value to ebx
   0x0804861e <+245>:   mov    eax,0x13                 # Set eax to 13
   0x08048623 <+250>:   mov    edi,edx                  # Set edi to top of stack
   0x08048625 <+252>:   mov    esi,ebx                  # Set esi to esp+80
   0x08048627 <+254>:   mov    ecx,eax                  # Set ecx to 13
   0x08048629 <+256>:   rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi] # Repeat string operation : for ecx, move ds:esi to es:edi
   0x0804862b <+258>:   call   0x8048484 <greetuser>
   0x08048630 <+263>:   lea    esp,[ebp-0xc]
   0x08048633 <+266>:   pop    ebx
   0x08048634 <+267>:   pop    esi
   0x08048635 <+268>:   pop    edi
   0x08048636 <+269>:   pop    ebp
   0x08048637 <+270>:   ret    
```

`greetuser`

```assembly
=> 0x08048484 <+0>:     push   ebp                       #  
   0x08048485 <+1>:     mov    ebp,esp                   #
   0x08048487 <+3>:     sub    esp,0x58                  # alloc 88 bytes
   0x0804848a <+6>:     mov    eax,ds:0x8049988          # set <language> value
   0x0804848f <+11>:    cmp    eax,0x1                   # compare with 1
   0x08048492 <+14>:    je     0x80484ba <greetuser+54>  # jmp +54 if true
   0x08048494 <+16>:    cmp    eax,0x2                   # compare with 2
   0x08048497 <+19>:    je     0x80484e9 <greetuser+101> # jmp +101 if true
   0x08048499 <+21>:    test   eax,eax                   # test if eax == 0 
   0x0804849b <+23>:    jne    0x804850a <greetuser+134> # jmp +134 if not
   0x0804849d <+25>:    mov    edx,0x8048710             # set 0x8048717 ("Hello ") to edx
   0x080484a2 <+30>:    lea    eax,[ebp-0x48]            # set ebp-72 to eax (local buffer)
   0x080484a5 <+33>:    mov    ecx,DWORD PTR [edx]       #
   0x080484a7 <+35>:    mov    DWORD PTR [eax],ecx       # set 0x6c6c6548 to eax value
   0x080484a9 <+37>:    movzx  ecx,WORD PTR [edx+0x4]    # 
   0x080484ad <+41>:    mov    WORD PTR [eax+0x4],cx     # set 0x206f to eax+4 value
   0x080484b1 <+45>:    movzx  edx,BYTE PTR [edx+0x6]    #
   0x080484b5 <+49>:    mov    BYTE PTR [eax+0x6],dl     # set 0x0 to eax+6
   0x080484b8 <+52>:    jmp    0x804850a <greetuser+134> # jmp to +134
   0x080484ba <+54>:    mov    edx,0x8048717             # set 0x8048717 ("Hyvää päivää ") to edx
   0x080484bf <+59>:    lea    eax,[ebp-0x48]            # set ebp-72 to eax 
   0x080484c2 <+62>:    mov    ecx,DWORD PTR [edx]       # set edx to ecx
   0x080484c4 <+64>:    mov    DWORD PTR [eax],ecx       # set 0xc3767948 to eax value
   0x080484c6 <+66>:    mov    ecx,DWORD PTR [edx+0x4]   # set edx+4 to ecx
   0x080484c9 <+69>:    mov    DWORD PTR [eax+0x4],ecx   # set 0x20a4c3a4 to eax+4 value
   0x080484cc <+72>:    mov    ecx,DWORD PTR [edx+0x8]   # set edx+8 to ecx
   0x080484cf <+75>:    mov    DWORD PTR [eax+0x8],ecx   # set 0x69a4c370 to eax+8 value
   0x080484d2 <+78>:    mov    ecx,DWORD PTR [edx+0xc]   # 
   0x080484d5 <+81>:    mov    DWORD PTR [eax+0xc],ecx   # set 0xc3a4c376 to eax+12 value
   0x080484d8 <+84>:    movzx  ecx,WORD PTR [edx+0x10]   #
   0x080484dc <+88>:    mov    WORD PTR [eax+0x10],cx    # set 0x20a4 to eax+16 value
   0x080484e0 <+92>:    movzx  edx,BYTE PTR [edx+0x12]   # 
   0x080484e4 <+96>:    mov    BYTE PTR [eax+0x12],dl    # set 0x0 to eax+18 value
   0x080484e7 <+99>:    jmp    0x804850a <greetuser+134> # jmp +134
   0x080484e9 <+101>:   mov    edx,0x804872a             # set 0x8048717 ("Goedemiddag! ") to edx
   0x080484ee <+106>:   lea    eax,[ebp-0x48]            # set ebp-72 to eax (local buffer)
   0x080484f1 <+109>:   mov    ecx,DWORD PTR [edx]       # 
   0x080484f3 <+111>:   mov    DWORD PTR [eax],ecx       # set 0x64656f47 to eax
   0x080484f5 <+113>:   mov    ecx,DWORD PTR [edx+0x4]   #
   0x080484f8 <+116>:   mov    DWORD PTR [eax+0x4],ecx   # set 0x64696d65 to eax+4
   0x080484fb <+119>:   mov    ecx,DWORD PTR [edx+0x8]   # 
   0x080484fe <+122>:   mov    DWORD PTR [eax+0x8],ecx   # set 0x21676164 to eax+8
   0x08048501 <+125>:   movzx  edx,WORD PTR [edx+0xc]    # 
   0x08048505 <+129>:   mov    WORD PTR [eax+0xc],dx     # set 0x0020 to eax+12
   0x08048509 <+133>:   nop
   0x0804850a <+134>:   lea    eax,[ebp+0x8]             # set ebp+8 (arg buffer) to eax
   0x0804850d <+137>:   mov    DWORD PTR [esp+0x4],eax   # 2nd arg : arg buffer
   0x08048511 <+141>:   lea    eax,[ebp-0x48]            # set ebp-72 (local buffer) to eax
   0x08048514 <+144>:   mov    DWORD PTR [esp],eax       # 1st arg : local buffer 
   0x08048517 <+147>:   call   0x8048370 <strcat@plt> 
   0x0804851c <+152>:   lea    eax,[ebp-0x48]            
   0x0804851f <+155>:   mov    DWORD PTR [esp],eax       # 1st arg : local buffer
   0x08048522 <+158>:   call   0x8048390 <puts@plt>
   0x08048527 <+163>:   leave  
   0x08048528 <+164>:   ret    
```