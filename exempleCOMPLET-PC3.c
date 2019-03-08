#include <assert.h>
//#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "primitives.h"

/* emetteur (ma machine) ---> recepteur (machine suivante) */

#define ADRESSE_EMETTEUR	"127.0.0.3"
#define ADRESSE_RECEPTEUR	"127.0.0.1"
#define PORT_RECEPTION		10030
#define PORT_EMISSION		10010
#define LONGUEUR_ADRESSE	16
#define LONGUEUR_MESSAGE	121

typedef struct paquet
{
	char adresse[LONGUEUR_ADRESSE];
	char message[LONGUEUR_MESSAGE];
} Paquet;
/* Paquet <=> struct paquet */

void traitePaquet(Paquet *p)
{
    int priseEmission2;
	char buffer[LONGUEUR_MESSAGE];

	if (strcmp(ADRESSE_EMETTEUR, p->adresse) == 0)
	/* si je suis le destinataire du paquet */
	{
		printf("Je suis le destinataire. \n");
		printf("MSG : %*s \n\n",20, p->message);

	}
	else
	{
		/* sinon */
        priseEmission2  = creePriseEmission(ADRESSE_RECEPTEUR, PORT_EMISSION);
        printf("Je ne suis PAS le destinataire. \n");
		printf("DEST : %*s\n\n", 20, p->adresse);
        printf("Routage vers destinnataire\n");
        memset (buffer, '\0', sizeof(buffer));

        sprintf(buffer, "%15s%120s", p->adresse, p->message);
        envoie(priseEmission2, buffer, strlen(buffer));
	}
}

int main (int argc, char **argv)
{
	int    priseEmission, priseReception;
	char   buffer[LONGUEUR_ADRESSE + LONGUEUR_MESSAGE];
	Paquet p;

	priseEmission  = creePriseEmission(ADRESSE_RECEPTEUR, PORT_EMISSION);
	priseReception = creePriseReception(PORT_RECEPTION);

	printf("RECEPTION \n");
	printf("Appuer sur ENTREE pour demarrer...\n");
	printf("PC2 demarre ...\n\n");
    while( getchar() != '\n' ); /* temporisation */
    /*boucle en reception*/
	do
	{
		memset (buffer, '\0', sizeof(buffer));
		recoit(priseReception, buffer, sizeof(buffer)-1);
		sscanf(buffer, "%15s%120s", p.adresse, p.message);
		traitePaquet(&p);
	} while (1); /* boucle infinie */

  return 0;
}
