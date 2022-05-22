# ASM

`main`

```assembly
   0x080485a4 <+0>:     push   ebp                  #
   0x080485a5 <+1>:     mov    ebp,esp              # 
   0x080485a7 <+3>:     and    esp,0xfffffff0       # 
   0x080485aa <+6>:     sub    esp,0x40             # allocate 64 bytes 
   0x080485ad <+9>:     lea    eax,[esp+0x16]       # 
   0x080485b1 <+13>:    mov    DWORD PTR [esp],eax  # 
   0x080485b4 <+16>:    call   0x804851e <pp>       # call pp(src[42])
   0x080485b9 <+21>:    lea    eax,[esp+0x16]       #
   0x080485bd <+25>:    mov    DWORD PTR [esp],eax  #
   0x080485c0 <+28>:    call   0x80483b0 <puts@plt> # call puts(src[42])
   0x080485c5 <+33>:    mov    eax,0x0              #
   0x080485ca <+38>:    leave  
   0x080485cb <+39>:    ret 
```

`pp`

```assembly
   0x0804851e <+0>:     push   ebp                              #
   0x0804851f <+1>:     mov    ebp,esp                          #
   0x08048521 <+3>:     push   edi                              #
   0x08048522 <+4>:     push   ebx                              #
   0x08048523 <+5>:     sub    esp,0x50                         # allocate 80 bytes
   0x08048526 <+8>:     mov    DWORD PTR [esp+0x4],0x80486a0    # " - "
   0x0804852e <+16>:    lea    eax,[ebp-0x30]                   #
   0x08048531 <+19>:    mov    DWORD PTR [esp],eax              #
   0x08048534 <+22>:    call   0x80484b4 <p>                    # call p(buf1[20], " - ")
   0x08048539 <+27>:    mov    DWORD PTR [esp+0x4],0x80486a0    # " - "
   0x08048541 <+35>:    lea    eax,[ebp-0x1c]                   #
   0x08048544 <+38>:    mov    DWORD PTR [esp],eax              #
   0x08048547 <+41>:    call   0x80484b4 <p>                    # call p(buf2[20], " - ")
   0x0804854c <+46>:    lea    eax,[ebp-0x30]                   #
   0x0804854f <+49>:    mov    DWORD PTR [esp+0x4],eax          #
   0x08048553 <+53>:    mov    eax,DWORD PTR [ebp+0x8]          #
   0x08048556 <+56>:    mov    DWORD PTR [esp],eax              #
   0x08048559 <+59>:    call   0x80483a0 <strcpy@plt>           # call strcpy(src[42], buf1[20])
   0x0804855e <+64>:    mov    ebx,0x80486a4                    # " " (0x20)
   0x08048563 <+69>:    mov    eax,DWORD PTR [ebp+0x8]          #
   0x08048566 <+72>:    mov    DWORD PTR [ebp-0x3c],0xffffffff  # 0xffffffff (4294967295 in 64-bit, -1 in 32-bit)
   0x0804856d <+79>:    mov    edx,eax                          # Set edx to eax (ebp+8)
   0x0804856f <+81>:    mov    eax,0x0                          # Set eax to 0
   0x08048574 <+86>:    mov    ecx,DWORD PTR [ebp-0x3c]         # Set ecx to ebp-60 value (0xffffffff)
   0x08048577 <+89>:    mov    edi,edx                          # Set edi to edx (ebp+8)
   0x08048579 <+91>:    repnz scas al,BYTE PTR es:[edi]         # repeat string operation until zero : scan es:[edi]
   0x0804857b <+93>:    mov    eax,ecx                          # result of repnz scas
   0x0804857d <+95>:    not    eax                              # inverse eax bits
   0x0804857f <+97>:    sub    eax,0x1                          # len - 1
   0x08048582 <+100>:   add    eax,DWORD PTR [ebp+0x8]          #
   0x08048585 <+103>:   movzx  edx,WORD PTR [ebx]               #
   0x08048588 <+106>:   mov    WORD PTR [eax],dx                # 
   0x0804858b <+109>:   lea    eax,[ebp-0x1c]                   # 
   0x0804858e <+112>:   mov    DWORD PTR [esp+0x4],eax
   0x08048592 <+116>:   mov    eax,DWORD PTR [ebp+0x8]          
   0x08048595 <+119>:   mov    DWORD PTR [esp],eax
   0x08048598 <+122>:   call   0x8048390 <strcat@plt>           # strcat(src[42], buf2[20])
   0x0804859d <+127>:   add    esp,0x50
   0x080485a0 <+130>:   pop    ebx
   0x080485a1 <+131>:   pop    edi
   0x080485a2 <+132>:   pop    ebp
   0x080485a3 <+133>:   ret   
```

`p`

```assembly
   0x080484b4 <+0>:     push   ebp                          # Push Base Pointer 
   0x080484b5 <+1>:     mov    ebp,esp                      # Set ebp to esp
   0x080484b7 <+3>:     sub    esp,0x1018                   # Allocate 4120 bytes
   0x080484bd <+9>:     mov    eax,DWORD PTR [ebp+0xc]      # Set eax to ebp+12 (2th arg function)
   0x080484c0 <+12>:    mov    DWORD PTR [esp],eax          # Set esp to eax
   0x080484c3 <+15>:    call   0x80483b0 <puts@plt>         # Call puts
   0x080484c8 <+20>:    mov    DWORD PTR [esp+0x8],0x1000   # Set esp+8 value to 4096
   0x080484d0 <+28>:    lea    eax,[ebp-0x1008]             # Set eax to ebp-4104
   0x080484d6 <+34>:    mov    DWORD PTR [esp+0x4],eax      # Set esp+4 to eax
   0x080484da <+38>:    mov    DWORD PTR [esp],0x0          # Set esp to 0
   0x080484e1 <+45>:    call   0x8048380 <read@plt>         # Call read
   0x080484e6 <+50>:    mov    DWORD PTR [esp+0x4],0xa      # Set esp+4 value to 10
   0x080484ee <+58>:    lea    eax,[ebp-0x1008]             # Set eax to ebp-4104
   0x080484f4 <+64>:    mov    DWORD PTR [esp],eax          # Set esp to eax
   0x080484f7 <+67>:    call   0x80483d0 <strchr@plt>       # Call strchr
   0x080484fc <+72>:    mov    BYTE PTR [eax],0x0           # Set first byte of eax to 0
   0x080484ff <+75>:    lea    eax,[ebp-0x1008]             # Set eax to ebp-4104
   0x08048505 <+81>:    mov    DWORD PTR [esp+0x8],0x14     # Set esp+8 value to 20
   0x0804850d <+89>:    mov    DWORD PTR [esp+0x4],eax      # Set esp+4 value to eax
   0x08048511 <+93>:    mov    eax,DWORD PTR [ebp+0x8]      # Set eax to ebp+8 (1th arg function)
   0x08048514 <+96>:    mov    DWORD PTR [esp],eax          # Set esp to eax
   0x08048517 <+99>:    call   0x80483f0 <strncpy@plt>      # Call strncpy
   0x0804851c <+104>:   leave  
   0x0804851d <+105>:   ret
```
