# Mini Shell

# Introduction à l'interface en ligne de commande
Qu'est-ce qu'une ligne de commande ?
=
Cette fenêtre, qu'on appelle aussi ligne de commande ou interface en ligne de commande, 
est une application qui permet de voir et de manipuler des fichiers sur votre ordinateur.


Ouvrir l'interface en ligne de commande
==
Pour commencer à expérimenter, nous avons d'abord besoin d'ouvrir notre interface en ligne de commande.


Invite de commande
-
Vous devriez maintenant voir une fenêtre noire ou blanche qui attend vos commandes.

Commençant par :
`$>`

Les commandes de base
-

Afficher le dossier courant:
-
$> `pwd`

`/Users/zntlm`

Pour changer de repertoire:
-
$> `cd OS`

`/Users/OS`

Lister les fichiers et les dossiers:
-
$> `ls`

`Applications`

`Bureau`

`Musique`

`Téléchargements`

...

Lister les fichier et dossiers avec leur droits:
-
$> `ls -l`

`-rwxr-xr-x  1 zntlm  staff  13308 24 jan 15:47 Prog`

`drwxr-xr-x  2 zntlm  staff     64 24 jan 14:18 test?`

`-rw-r--r--@ 1 zntlm  staff   1777 24 jan 15:47 test.c`

`drwxr-xr-x  2 zntlm  staff     64 24 jan 14:24 test2`

...

Créer un dossier
-
$> `mkdir exercices`

Créer un fichier
-
$> `touch exo1`

Pour Sortir du shell
-
$> `exit`


