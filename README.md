# Networth, le réseau qui vaut le coup

## Fonctionnalités

* Échange de message;
* Calcul d'erreurs (**CRC**);
* Message en **broadcast**;
* Ajout de PCs grâce aux entrées clavier;
* Token entièrement fonctionnel;
* **Prévention** de la famine.

## Compilation :

	dans la racine du projet faire :
	$ make

## Usage :

- Éxecuter NetWorth grâce à l'executable : networth.exec
($ ./networth.exec)

- Choisir si vous êtes en loopback ou sur un réseau.
- Saisir le numéro d'hôte correspondant au numéro du PC sur lequel vous lancez le programme.
- Indiquer si vous êtes le dernier hôte de l'anneau.
- Si sur un réseau : Saisir l'adresse IP de l'hôte suivant (ex: si vous êtes l'hôte 2 vous saisissez l'adresse IP de l'hôte 3).
- Vous pouvez maintenant envoyer des messages aux autres hôtes de l'anneau.

- Pour arreter le programme faire CTRL-C
