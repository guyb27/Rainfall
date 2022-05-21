# ASM

`main`

```assembly
   0x080485f4 <+0>:     push   ebp                      # push stack base pointer
   0x080485f5 <+1>:     mov    ebp,esp                  # set stack base pointer to stack pointer
   0x080485f7 <+3>:     push   ebx                      # push base pointer
   0x080485f8 <+4>:     and    esp,0xfffffff0           # align stack on 16 (-4 bytes)
   0x080485fb <+7>:     sub    esp,0x20                 # alloc 32 bytes
   0x080485fe <+10>:    cmp    DWORD PTR [ebp+0x8],0x1  # cmp argc with 1
   0x08048602 <+14>:    jg     0x8048610 <main+28>      # jmp +28 if argc > 1
   0x08048604 <+16>:    mov    DWORD PTR [esp],0x1      #
   0x0804860b <+23>:    call   0x80484f0 <_exit@plt>    # exit with 1
   0x08048610 <+28>:    mov    DWORD PTR [esp],0x6c     # 1st arg: 108
   0x08048617 <+35>:    call   0x8048530 <_Znwj@plt>    # new operator() in C++ : alloc 108 bytes
   0x0804861c <+40>:    mov    ebx,eax                  # set eax to ebx
   0x0804861e <+42>:    mov    DWORD PTR [esp+0x4],0x5  # 2nd arg: 5
   0x08048626 <+50>:    mov    DWORD PTR [esp],ebx      # 1st arg: address from +35
   0x08048629 <+53>:    call   0x80486f6 <_ZN1NC2Ei>    # call _ZN1NC2Ei method
   0x0804862e <+58>:    mov    DWORD PTR [esp+0x1c],ebx # set address from +35 to esp+28
   0x08048632 <+62>:    mov    DWORD PTR [esp],0x6c     # 1st arg: 108
   0x08048639 <+69>:    call   0x8048530 <_Znwj@plt>    # new operator() in C++ : alloc 108 bytes
   0x0804863e <+74>:    mov    ebx,eax                  # set eax to ebx
   0x08048640 <+76>:    mov    DWORD PTR [esp+0x4],0x6  # 2nd arg: 6
   0x08048648 <+84>:    mov    DWORD PTR [esp],ebx      # 1st arg: address from +69
   0x0804864b <+87>:    call   0x80486f6 <_ZN1NC2Ei>    # call _ZN1NC2Ei method
   0x08048650 <+92>:    mov    DWORD PTR [esp+0x18],ebx # set address from +69 to esp+24
   0x08048654 <+96>:    mov    eax,DWORD PTR [esp+0x1c] # set address from +35 to eax
   0x08048658 <+100>:   mov    DWORD PTR [esp+0x14],eax # set address from +35 to esp+20
   0x0804865c <+104>:   mov    eax,DWORD PTR [esp+0x18] # set address from +69 to eax
   0x08048660 <+108>:   mov    DWORD PTR [esp+0x10],eax # set address from +69 to esp+16
   0x08048664 <+112>:   mov    eax,DWORD PTR [ebp+0xc]  # get argv
   0x08048667 <+115>:   add    eax,0x4                  # get argv+1
   0x0804866a <+118>:   mov    eax,DWORD PTR [eax]      # get argv+1 value
   0x0804866c <+120>:   mov    DWORD PTR [esp+0x4],eax  # 2nd arg : argv+1 value
   0x08048670 <+124>:   mov    eax,DWORD PTR [esp+0x14] # 
   0x08048674 <+128>:   mov    DWORD PTR [esp],eax      # 1st arg : address from +35
   0x08048677 <+131>:   call   0x804870e <_ZN1N13setAnnotationEPc>
   0x0804867c <+136>:   mov    eax,DWORD PTR [esp+0x10] # 
   0x08048680 <+140>:   mov    eax,DWORD PTR [eax]      # 
   0x08048682 <+142>:   mov    edx,DWORD PTR [eax]      # 
   0x08048684 <+144>:   mov    eax,DWORD PTR [esp+0x14]
   0x08048688 <+148>:   mov    DWORD PTR [esp+0x4],eax
   0x0804868c <+152>:   mov    eax,DWORD PTR [esp+0x10]
   0x08048690 <+156>:   mov    DWORD PTR [esp],eax
   0x08048693 <+159>:   call   edx
   0x08048695 <+161>:   mov    ebx,DWORD PTR [ebp-0x4]
   0x08048698 <+164>:   leave  
   0x08048699 <+165>:   ret 
```

`_Znwj`

```assembly
   0xb7f9b600 <+0>:     push   edi
   0xb7f9b601 <+1>:     mov    eax,0x1
   0xb7f9b606 <+6>:     push   esi
   0xb7f9b607 <+7>:     push   ebx
   0xb7f9b608 <+8>:     sub    esp,0x10
   0xb7f9b60b <+11>:    mov    esi,DWORD PTR [esp+0x20]
   0xb7f9b60f <+15>:    call   0xb7f364e7
   0xb7f9b614 <+20>:    add    ebx,0x319e0
   0xb7f9b61a <+26>:    test   esi,esi
   0xb7f9b61c <+28>:    cmove  esi,eax
   0xb7f9b61f <+31>:    mov    DWORD PTR [esp],esi
   0xb7f9b622 <+34>:    call   0xb7f34f60 <malloc@plt>
   0xb7f9b627 <+39>:    test   eax,eax
   0xb7f9b629 <+41>:    jne    0xb7f9b680 <_Znwj+128>
   0xb7f9b62b <+43>:    mov    edi,DWORD PTR [ebx-0x264]
   0xb7f9b631 <+49>:    mov    eax,DWORD PTR [edi]
   0xb7f9b633 <+51>:    test   eax,eax
   0xb7f9b635 <+53>:    je     0xb7f9b64c <_Znwj+76>
   0xb7f9b637 <+55>:    nop
   0xb7f9b638 <+56>:    call   eax
   0xb7f9b63a <+58>:    mov    DWORD PTR [esp],esi
   0xb7f9b63d <+61>:    call   0xb7f34f60 <malloc@plt>
   0xb7f9b642 <+66>:    test   eax,eax
   0xb7f9b644 <+68>:    jne    0xb7f9b680 <_Znwj+128>
   0xb7f9b646 <+70>:    mov    eax,DWORD PTR [edi]
   0xb7f9b648 <+72>:    test   eax,eax
   0xb7f9b64a <+74>:    jne    0xb7f9b638 <_Znwj+56>
   0xb7f9b64c <+76>:    mov    DWORD PTR [esp],0x4
   0xb7f9b653 <+83>:    call   0xb7f34410 <__cxa_allocate_exception@plt>
   0xb7f9b658 <+88>:    mov    edx,DWORD PTR [ebx-0x320]
   0xb7f9b65e <+94>:    add    edx,0x8
   0xb7f9b661 <+97>:    mov    DWORD PTR [eax],edx
   0xb7f9b663 <+99>:    mov    edx,DWORD PTR [ebx-0x9c]
   0xb7f9b669 <+105>:   mov    DWORD PTR [esp],eax
   0xb7f9b66c <+108>:   mov    DWORD PTR [esp+0x8],edx
   0xb7f9b670 <+112>:   mov    edx,DWORD PTR [ebx-0x4b4]
   0xb7f9b676 <+118>:   mov    DWORD PTR [esp+0x4],edx
   0xb7f9b67a <+122>:   call   0xb7f348c0 <__cxa_throw@plt>
   0xb7f9b67f <+127>:   nop
   0xb7f9b680 <+128>:   add    esp,0x10
   0xb7f9b683 <+131>:   pop    ebx
   0xb7f9b684 <+132>:   pop    esi
   0xb7f9b685 <+133>:   pop    edi
   0xb7f9b686 <+134>:   ret    
   0xb7f9b687 <+135>:   cmp    edx,0xffffffff
   0xb7f9b68a <+138>:   mov    DWORD PTR [esp],eax
   0xb7f9b68d <+141>:   je     0xb7f9b694 <_Znwj+148>
   0xb7f9b68f <+143>:   call   0xb7f359d0 <_Unwind_Resume@plt>
   0xb7f9b694 <+148>:   call   0xb7f340e0 <__cxa_call_unexpected@plt>
```

`_ZN1NC2Ei`

```assembly
   0x080486f6 <+0>:     push   ebp                          #
   0x080486f7 <+1>:     mov    ebp,esp                      #
   0x080486f9 <+3>:     mov    eax,DWORD PTR [ebp+0x8]      # set 1st arg to eax
   0x080486fc <+6>:     mov    DWORD PTR [eax],0x8048848    # set address 0x8048848 on eax value
   0x08048702 <+12>:    mov    eax,DWORD PTR [ebp+0x8]      # 
   0x08048705 <+15>:    mov    edx,DWORD PTR [ebp+0xc]      # set 2nd arg to edx
   0x08048708 <+18>:    mov    DWORD PTR [eax+0x68],edx     # 
   0x0804870b <+21>:    pop    ebp
   0x0804870c <+22>:    ret 
```

`_ZN1N13setAnnotationEPc`

```assembly
   0x0804870e <+0>:     push   ebp                      #
   0x0804870f <+1>:     mov    ebp,esp                  #
   0x08048711 <+3>:     sub    esp,0x18                 # alloc 24 bytes
   0x08048714 <+6>:     mov    eax,DWORD PTR [ebp+0xc]  # set 1st arg to eax
   0x08048717 <+9>:     mov    DWORD PTR [esp],eax      # 1st arg : 1st arg of function
   0x0804871a <+12>:    call   0x8048520 <strlen@plt>   #
   0x0804871f <+17>:    mov    edx,DWORD PTR [ebp+0x8]  # set 2st arg to edx
   0x08048722 <+20>:    add    edx,0x4                  # add 4 bytes to address
   0x08048725 <+23>:    mov    DWORD PTR [esp+0x8],eax  # 
   0x08048729 <+27>:    mov    eax,DWORD PTR [ebp+0xc]
   0x0804872c <+30>:    mov    DWORD PTR [esp+0x4],eax
   0x08048730 <+34>:    mov    DWORD PTR [esp],edx
   0x08048733 <+37>:    call   0x8048510 <memcpy@plt>
   0x08048738 <+42>:    leave  
   0x08048739 <+43>:    ret  
```
