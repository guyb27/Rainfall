# ASM

`main`

`n`

```assembly
   0x08048457 <+0>:     push   ebp                          # Push Base Pointer
   0x08048458 <+1>:     mov    ebp,esp                      # Set esp to ebp
   0x0804845a <+3>:     sub    esp,0x218                    # Allocate 536 bytes
   0x08048460 <+9>:     mov    eax,ds:0x8049804             # Set stdin to eax
   0x08048465 <+14>:    mov    DWORD PTR [esp+0x8],eax      # Set eax(stdin) to esp+8
   0x08048469 <+18>:    mov    DWORD PTR [esp+0x4],0x200    # Set 512 to esp+4
   0x08048471 <+26>:    lea    eax,[ebp-0x208]              # Set [ebp-520] 
   0x08048477 <+32>:    mov    DWORD PTR [esp],eax
   0x0804847a <+35>:    call   0x8048350 <fgets@plt>
   0x0804847f <+40>:    lea    eax,[ebp-0x208]
   0x08048485 <+46>:    mov    DWORD PTR [esp],eax
   0x08048488 <+49>:    call   0x8048444 <p>
   0x0804848d <+54>:    mov    eax,ds:0x8049810
   0x08048492 <+59>:    cmp    eax,0x1025544
   0x08048497 <+64>:    jne    0x80484a5 <n+78>
   0x08048499 <+66>:    mov    DWORD PTR [esp],0x8048590
   0x080484a0 <+73>:    call   0x8048360 <system@plt>
   0x080484a5 <+78>:    leave  
   0x080484a6 <+79>:    ret 
```
