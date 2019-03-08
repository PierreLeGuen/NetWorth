#include <assert.h>
//#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "initPC.h"
#include "packets.h"

#include "primitives.h"

/* emetteur (ma machine) ---> recepteur (machine suivante) */

#define LONGUEUR_MESSAGE    128
typedef enum {
    false, true
} bool;

enum State {
    standby, listen, send
} currStatus;

/* Paquet <=> struct paquet */

int main(int argc, char **argv) {
    char line[10];
    Host PC2;

    char choix = 0;
    char *initHost;
    int numero = 1;
    int destHostNumber = -1;
    char buffer[+LONGUEUR_MESSAGE];
    Paquet currPacket;
    bool stop = false;


    printf("Appuyer ENTREE pour demarrer...\n");
    // while (getchar() != '\n');
    printf("Ajouter nouveau pc ? o/n \n");
    if (1) {
        initHost = initPC(numero);

        PC2.HOST_NUMBER = initHost[0] - 48;
        PC2.PRISE_EMISSION = initHost[2] - 48;
        PC2.PRISE_RECEPTION = initHost[4] - 48;
        char *pend = &initHost[34] + 5;
        PC2.PORT_EMISSION = (int) strtol(&initHost[40], &pend, 10);
        memcpy(PC2.ADRESSE, &initHost[6], 13);
        numero += 1;
    } else {
        return EXIT_FAILURE;
    }
    printf("Vous êtes le pc n°: %d\n", PC2.HOST_NUMBER);


    while (!stop) {
        while (currStatus == standby) {
            switch (choix) {
                case 's' :
                    currStatus = send;
                    break;
                case 'l':
                    currStatus = listen;
                    break;
                case 'q':
                    stop = true;
                    return EXIT_SUCCESS;
                default:
                    printf("s (aka send) pour envoyer un message, l (aka listen) pour passer en mode écoute, ou q pour quitter\n");
                    if (fgets(line, 10, stdin) && sscanf(line, "%c", &choix) != 1)
                        choix = 0;
            }
        }

        if (currStatus == send) {
            char message[100] = {0};
            printf("Saisir message :\n");
            fgets(currPacket.MESSAGE, 100, stdin);

            printf("Destinataire ?");
            if (fgets(line, 10, stdin) && sscanf(line, "%d", &destHostNumber) != 1)
                destHostNumber = 0;

            currPacket.HOST_NUMBER = destHostNumber;
            printf("Presser ENTREE pour envoyer le message\n");
            while (getchar() != '\n');

            memset(buffer, '\0', sizeof(buffer));

            sprintf(buffer, "%d,%d,%s", PC2.HOST_NUMBER, currPacket.HOST_NUMBER, currPacket.MESSAGE);
            envoie(PC2.PRISE_EMISSION, buffer, strlen(buffer));
        } else if (currStatus == listen) {
            int priseR, priseE;
            priseR = creePriseReception(10050);
            priseE = creePriseEmission("192.168.0.102", 10100);
            Host senderHost;
            memset(buffer, '\0', sizeof(buffer));
            printf("Prise RECEP %d", PC2.PRISE_RECEPTION);
            recoit(priseR, buffer, sizeof(buffer) - 1);
            sscanf(buffer, "%d,%d,%120s", &senderHost.HOST_NUMBER, &currPacket.HOST_NUMBER, currPacket.MESSAGE);
            traitePaquet(currPacket, PC2);
        } else {
            printf("ERROR : WRONG INPUT");
        }
        currStatus = standby;
        choix = 0;
    }
    return 0;
}
