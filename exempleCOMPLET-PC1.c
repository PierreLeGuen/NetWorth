#include <assert.h>
//#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "initPC.h"

#include "primitives.h"

/* emetteur (ma machine) ---> recepteur (machine suivante) */

#define LONGUEUR_ADRESSE    16
#define LONGUEUR_MESSAGE    121

#define ADRESSE_EMETTEUR    "127.0.0.1"
#define ADRESSE_RECEPTEUR    "127.0.0.2"
#define PORT_RECEPTION        10010
#define PORT_EMISSION        10020
enum State {
    listen, send
} currStatus;

int repertoire[100];

typedef struct paquet {
    char adresse[LONGUEUR_ADRESSE];
    char message[LONGUEUR_MESSAGE];
} Paquet;

/* Paquet <=> struct paquet */

void traitePaquet(Paquet *p) {
    char buffer[LONGUEUR_MESSAGE];

    if (strcmp(ADRESSE_EMETTEUR, p->adresse) == 0)
        /* si je suis le destinataire du paquet */
    {
        printf("message : ");
        scanf("%s", buffer);
        sprintf(p->message, "%120s", buffer);
        printf("\n");
    } else
        /* sinon */
        printf("message de %s : %s\n", p->adresse, p->message);
}

int main(int argc, char **argv) {
    char *myHost;
    int numero = 0;
    int priseEmission, priseReception;
    char buffer[LONGUEUR_ADRESSE + LONGUEUR_MESSAGE];
    Paquet p;

    myHost = initPC(numero);

    priseEmission = myHost[2] - 48;
    char test[13];
    memcpy(test, &myHost[6], 13);
/***
    printf("Appuyer ENTREE pour demarrer...\n");
    while (getchar() != '\n');
    printf("Ajouter nouveau pc ? o/n \n");
    if (getchar() == 'r') {
        numero += 1;
        repertoire[numero] = numero;
    } else {
        printf("Pourquoi lancer le programme ?? \n");
    }
    printf("Vous êtes le pc n°: %d\n", numero);

    printf("e pour envoyer un message, r pour passer en mode écoute\n");
    if (getchar() != 'e' && getchar() != 'r') {
        printf("Erreur, veuillez re-saisir \n");
    }
    if (getchar() == 'e') {
        currStatus = send;
    } else if (getchar() == 'r') {
        currStatus = listen;
    }
    do {
        do {
            char message[100] = {0};
            printf("Saisir message :\n");
            fgets(message, 100, stdin);

            printf("Touche e pour envoyer le message\n");
            while (getchar() != 'e');

            memset(buffer, '\0', sizeof(buffer));

            sprintf(buffer, "%15s%120s", repertoire[num_dest], message);

            envoie(priseEmission, buffer, strlen(buffer));

        } while (currStatus == send);
        do {
            memset(buffer, '\0', sizeof(buffer));

            recoit(priseReception, buffer, sizeof(buffer) - 1);
            if (buffer == '$ù$') {
                currStatus = send;
            }
            sscanf(buffer, "%15s%120s", &p.adresse, &p.message);
            traitePaquet(&p);
        } while (currStatus = send);

    } while (1);
***/
    return 0;
}
