
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

    char buffer[LONGUEUR_MESSAGE] = {0};
    bool stop = false;
    bool asToken = false;
    Paquet recvPacket = {0};

    AnHost = addHost();

    printf("-- HOTE n° : %d\n", AnHost.HOST_NUMBER);
    if (AnHost.PORT_EMISSION == 19000) {
        char initBuffer[LONGUEUR_MESSAGE] = {0};
        printf("--- INITIALISATION DU TOKEN ---\n");
        sprintf(initBuffer, "%d,%d,%d,%d,%d,%s", 0, AnHost.HOST_NUMBER, 0, 0,
                0, "\n");
        envoie(AnHost.PRISE_EMISSION, initBuffer, strlen(initBuffer));
        printf("--- TOKEN VERS HOTE 0 ---\n");
    }

    while (!stop) {
        printf("--- EN ATTENTE TOKEN ---\n\n");
        if (!asToken) {
            recoit(AnHost.PRISE_RECEPTION, buffer, sizeof(buffer) - 1);
            recvPacket = traitePaquet(AnHost, buffer);
            if (recvPacket.slotReserve == AnHost.HOST_NUMBER) {
                asToken = true;
            }
        }
        if (asToken) {
            bool wantToSendMessage = false;
            printf("-- Envoyer un message ?(Oui : 1/Non : 0\n");
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
                    sprintf(buffer, "%d,%d,%d,%d,%d,%s", 0, AnHost.HOST_NUMBER, AnHost.HOST_NUMBER + 1,
                            AnHost.HOST_NUMBER + 1,
                            0, "\n");
                }
                envoie(AnHost.PRISE_EMISSION, buffer, strlen(buffer));
            }
            asToken = false;
        }
    }
    return 0;
}
