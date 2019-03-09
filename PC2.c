
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
    Host PC2;

    char choix = 0;
    char *initHost;
    int numero = 1;
    char buffer[LONGUEUR_MESSAGE];
    Paquet currPacket;
    bool stop = false;

    initHost = initPC(numero, true);

    PC2.HOST_NUMBER = initHost[0] - 48;
    PC2.PRISE_EMISSION = initHost[2] - 48;
    PC2.PRISE_RECEPTION = initHost[4] - 48;
    PC2.PORT_EMISSION = (int) strtol(&initHost[32], NULL, 10);
    PC2.PORT_RECEPTION = (int) strtol(&initHost[26], NULL, 10);
    memcpy(PC2.ADRESSE, &initHost[5], 9);
    printf("Vous êtes le pc n°: %d\n", PC2.HOST_NUMBER);
    // numero += 1;


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
            for (int i = 0; i < sizeof(buffer); ++i) {
                buffer[i] = 0;
            }
            Host senderHost;
            memset(buffer, '\0', sizeof(buffer));
            recoit(PC2.PRISE_RECEPTION, buffer, sizeof(buffer) - 1);
            sscanf(buffer, "%d,%d,%64[^\\n]s", &senderHost.HOST_NUMBER, &currPacket.HOST_NUMBER, currPacket.MESSAGE);
            traitePaquet(currPacket, PC2);
        } else {
            printf("ERROR : WRONG INPUT");
        }
        currStatus = standby;
        choix = 0;
    }
    return 0;
}
