Pour lancer un shell il faut ne entrer dans les jumps a partir de *main+357.
Pour ce faire il faut entrer "login" dans le fgets et remplir les conditions suivantes:
_Pouvoir acceder a la variables "auth" (0x8049aac), sinon le programme segfault
_Le pointeur contenu dans auth doit etre une adresse et cette adresse+0x20 doit etre accessible et doit contenir une valeur autre que 0x0

======================================================================================

Step1: "auth "
Donne a la valeur de la variable "auth" l adresse du premier malloc(4), on a donc deja allouer 4 bytes apres auth sur 32, il y en a 2 de vide, mais ce n est pas important, on pourrait les remplir a la suite de "auth ".
Ce qui est important c est que sur la heap on avance pour la prochaine allocation qui se fera a la suite de celle-ci.
Malloc reserve 0x10(16) bytes a chaque allocation qui est en dessous de 0x10(16) bytes, du coup, la prochaine allocation se fera 0x10(16) bytes plus loin que cette adresse.

Step2: "service LeChevalCGenial"
le deuxieme malloc va se faire a la suite de l autre, celui-c est sous la forme d un strdup(), du coup on peut lui donner une valeur allant jusqu a 128 bytes, c'est la valeur max du fgets, nous avons juste besoin de 16 (32-16) bytes

Step3: "login"
Nous remplissons maintenant les conditions pour arriver a *main+401 qui n'est autre que la commande system("/bin/sh") qui nous ouvre un "beau" shell
