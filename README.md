# codeplan

Pour compiler l'application :

g++ main_test.cpp attitudeController.cpp cameraController.cpp planManager.cpp plan.cpp genericInstruction.cpp statusManager.cpp -o exec

Le makefile est censé être bon aussi.
Compilation générale :
instruction make.

Penser à clean s'il reste des fichiers binaires .o

////////////////////////////////////

Pour le lancement : 
4 liaisons en SSH vers chaque Raspberry Pi.
Transférer un fichier zip avec tout le code vers les Raspberry Pi (sans les exécutables).
Compiler le code avec le makefile.
Lancer un executable par connexion SSH :
	- ./main_Com_ST (partition communication Satellite - Sol)
	- ./main_run (partition fonctionnelle)
	- ./main_Controller (partition actionneurs)

Configurer le fichier listpid avec le pid des 3 processus précédents (indiqués à leur lancement)
Dans la dernière fenêtre SSH, lancer l'ARINC en lançant le script goK.sh.

Faire de même avec la seconde Raspberry Pi.


Côté Sol, compiler de même les fichiers. 
Se placer dans le répertoire "Station Sol".
Lancer l'exécutable ./Ground.

Les fichiers plans à envoyer doivent être dans le répertoire "Plans"
Les fichiers images et le LogErreur sont reçus dans le répertoire "Photo"
Pour Déchiffrer les photos, il faut lancer l'executable corespondant du répertoire, avec comme argument le nom de la photo.


