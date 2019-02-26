#include <assert.h>
//#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "primitives.h"

/* emetteur (ma machine) ---> recepteur (machine suivante) */

#define LONGUEUR_ADRESSE	16
#define LONGUEUR_MESSAGE	121

enum etat
{
	ecoute,
	envoie
}

int repertoire[100];
int numero = 0;

typedef struct paquet
{
	char adresse[LONGUEUR_ADRESSE];
	char message[LONGUEUR_MESSAGE];
} Paquet;
/* Paquet <=> struct paquet */

void traitePaquet(Paquet *p)
{
	char buffer[LONGUEUR_MESSAGE];

	if (strcmp(ADRESSE_EMETTEUR, p->adresse) == 0)
	/* si je suis le destinataire du paquet */
	{
		printf("message : ");
		scanf("%s", buffer);
		sprintf(p->message, "%120s", buffer);
		printf("\n");
	}
	else
		/* sinon */
		printf("message de %s : %s\n", p->adresse, p->message);
}

int main (int argc, char **argv)
{
	int    priseEmission, priseReception;
	char   buffer[LONGUEUR_ADRESSE + LONGUEUR_MESSAGE];
	Paquet p;

	priseEmission  = creePriseEmission(ADRESSE_RECEPTEUR, PORT_EMISSION);
	priseReception = creePriseReception(PORT_RECEPTION);

	printf("J'envoie le 1er paquet \n");
	printf("Touche d pour demarrer...\n");
  	while (getchar() != 'd'); /* temporisation */
	printf("Ajouter nouveau pc ? o/n \n");
	if (getchar() = 'r')
	{
		numereo += ;1
		repertoire[numero] = numero;
	}
	else
	{
		"Pourquoi lancer le programme ??"
	}
	printf("Vous êtes le pc n°: %d\n", numero);

	printf("e pour envoyer un message, r pour passer en mode écoute\n");
	if (getchar() != 'e' && getchar() != 'r')
	{
		printf("Erreur, veuillez re-saisir \n");
	}
	if (getchar() = 'e')
	{
		etat = envoie;
	}
	if (getchar() = 'r')
	{
		etat = ecoute;
	}
	do
	{
	do
	{
		char message[100] = NULL;
		printf("Saisir message :\n");

		printf("Touche e pour continuer...\n");
  		while (getchar() != 'e'); /* temporisation */

		memset (buffer, '\0', sizeof(buffer));

		sprintf(buffer, "%15s%120s", repertoire[num_dest], message);

		envoie(priseEmission, buffer, strlen(buffer));

	} while (etat = envoie); /* boucle infinie */
	do
	{
		memset (buffer, '\0', sizeof(buffer));

		recoit(priseReception, buffer, sizeof(buffer)-1);

		sscanf(buffer, "%15s%120s", &p.adresse, &p.message);

		traitePaquet(&p);
	} while(etat = ecoute);

} while(1);

  return 0;
}
