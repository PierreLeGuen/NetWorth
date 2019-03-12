
#define LONGUEUR_MESSAGE    2056

//#include <curses.h>
#include <stdio.h>
#include <string.h>
#include "hosts/initHOST.h"
#include "packets/TraitePaquet.h"
#include "packets/sendPacket.h"
#include "primitives.h"

/* emetteur (ma machine) ---> recepteur (machine suivante) */



enum State {
    standby, listen, send
} currStatus;

/* Paquet <=> struct paquet */



int main(int argc, char **argv) {
    char line[10];
    Host AnHost;

    char choix = 0;
    char buffer[LONGUEUR_MESSAGE] = {0};
    bool stop = false;
    bool asToken = false;
    Paquet recvPacket = {0};

    AnHost = addHost();
    /*
    AnHost.HOST_NUMBER = initHost[0] - 48;
    AnHost.PRISE_EMISSION = initHost[2] - 48;
    AnHost.PRISE_RECEPTION = initHost[4] - 48;
    AnHost.PORT_EMISSION = (int) strtol(&initHost[32], NULL, 10);
    AnHost.PORT_RECEPTION = (int) strtol(&initHost[26], NULL, 10);
    memcpy(AnHost.ADRESSE, &initHost[5], 9);
     */

    printf("Vous êtes le pc n°: %d\n", AnHost.HOST_NUMBER);
    if (AnHost.PORT_EMISSION == 19000) {
        char initBuffer[LONGUEUR_MESSAGE] = {0};
        printf("!! INIT NETWORK TOKEN !!");
        sprintf(initBuffer, "%d,%d,%d,%d,%d,%s", 0, AnHost.HOST_NUMBER, 0, 0,
                0, "\n");
        envoie(AnHost.PRISE_EMISSION, initBuffer, strlen(initBuffer));
    }

    while (!stop) {
        printf("EN ATTENTE TOKEN\n");
        if (!asToken) {
            recoit(AnHost.PRISE_RECEPTION, buffer, sizeof(buffer) - 1);
            recvPacket = traitePaquet(AnHost, buffer);
            asToken = true;
        }
        if (asToken) {
            bool wantToSendMessage = false;
            printf("Voulez-vous envoyer un message ?");
            if (fgets(line, 10, stdin) && sscanf(line, "%d", &wantToSendMessage) != 1)
                wantToSendMessage = 0;
            if (wantToSendMessage) {
                sendNewPacket(AnHost, buffer);
            } else {
                memset(buffer, '\0', sizeof(buffer));
                if (AnHost.PORT_EMISSION == 19000) {
                    sprintf(buffer, "%d,%d,%d,%d,%d,%s", 0, AnHost.HOST_NUMBER, 0, 0,
                            0, "\n");
                } else {
                    sprintf(buffer, "%d,%d,%d,%d,%d,%s", 0, AnHost.HOST_NUMBER, AnHost.HOST_NUMBER + 1, 0,
                            0, "\n");
                }
                envoie(AnHost.PRISE_EMISSION, buffer, strlen(buffer));
            }
            asToken = false;
        }
    }
    return 0;
}
