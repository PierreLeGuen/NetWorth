
//#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "initPC.h"
#include "packets.h"

#include "primitives.h"

/* emetteur (ma machine) ---> recepteur (machine suivante) */

#define LONGUEUR_MESSAGE    128


enum State {
    standby, listen, send
} currStatus;

/* Paquet <=> struct paquet */



int main(int argc, char **argv) {
    char line[10];
    Host PC1;

    char choix = 0;
    char *initHost;
    int numero = 0;
    int destHostNumber = -1;
    char buffer[LONGUEUR_MESSAGE];
    Paquet currPacket;
    bool stop = false;

    initHost = initPC(numero, true);

    PC1.HOST_NUMBER = initHost[0] - 48;
    PC1.PRISE_EMISSION = initHost[2] - 48;
    PC1.PRISE_RECEPTION = initHost[4] - 48;
    PC1.PORT_EMISSION = (int) strtol(&initHost[32], NULL, 10);
    PC1.PORT_RECEPTION = (int) strtol(&initHost[26], NULL, 10);
    memcpy(PC1.ADRESSE, &initHost[5], 9);
    numero += 1;

    printf("Vous êtes le pc n°: %d\n", PC1.HOST_NUMBER);

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
            int destHostNumber = -1;
            printf("Saisir message :\n");
            fgets(currPacket.MESSAGE, 100, stdin);

            printf("Destinataire (numPC) : \n");
            if (fgets(line, 10, stdin) && sscanf(line, "%d", &destHostNumber) != 1)
                destHostNumber = 0;

            currPacket.HOST_NUMBER = destHostNumber;
            printf("Presser ENTREE pour envoyer le message\n");
            while (getchar() != '\n');
            memset(buffer, '\0', sizeof(buffer));

            sprintf(buffer, "%d,%d,%s", PC1.HOST_NUMBER, currPacket.HOST_NUMBER, currPacket.MESSAGE);
            envoie(PC1.PRISE_EMISSION, buffer, strlen(buffer));
            printf("Prise ENVOI %d", PC1.PRISE_EMISSION);

        } else if (currStatus == listen) {
            Host senderHost;
            memset(buffer, '\0', sizeof(buffer));
            recoit(PC1.PRISE_RECEPTION, buffer, sizeof(buffer) - 1);
            sscanf(buffer, "%d,%d,%120s", &senderHost.HOST_NUMBER, &currPacket.HOST_NUMBER, currPacket.MESSAGE);
            traitePaquet(currPacket, PC1);
        } else {
            printf("ERROR : WRONG INPUT");
        }
        currStatus = standby;
        choix = 0;
    }
    return 0;
}
