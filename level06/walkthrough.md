We have three interessant functions:
main: The main function
m: The function called at *main+84
n: An uncalled function

The malloc at *main+16 take 0x40 (64) in argument and the address of the result is stocked at $esp+0x1c
Address:0x804a1a0
Addres_VM:0x804a008

The malloc at *main+32 tke 0x4 in argument and stock th result at $esp+0x18.
Address:0x804a1f0
Address_VM:0x804a050


======================
At *main+41 it stock the m function address in $edx

At *main+46 it stock the pointer of the second malloc

At *main+50, it stock the m function in the value of $eax->0x804a1f0(address_second_malloc>)

At *main+52, it stock the PATH/Name address of the binary in eax

At *main+55 it increment eax of 4, to go to the first argument of the program

At *main+58, it dereference the pointer:
EAX: 0xffffb238 --> 0xffffb429 ('A' <repeats 200 times>...)
->EAX: 0xffffb429 ('A' <repeats 200 times>...)

At *main+60 it move the address from $eax to $edx

At *main+75 our first argument parameter value of the program is stocker as the address of eax

At *main+84 it call our first argument parameter value of the program as an address !

If we examine the "n" function, we can see it calls system with "/bin/cat /home/user/level7/.pass" in argument

Ok, We have to put the address of the function "n" in the first argument parameter value to print the flag 

We have to find the good padding because if we run the programm with "A * 100" we overwrite This address, but not just with 4 bytes

If we subtract the second malloc from the first, we found 72, we can use this calculation in gdb:
(gdb) p/d 0x804a050-0x804a008
$2 = 72

we can use this command to get the flag:
./level6 $(python -c 'print "\x41" * 72 + "\x54\x84\x04\x08"')
