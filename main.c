
#define LONGUEUR_MESSAGE    2056

//#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "initHOST.h"
#include "packets.h"
#include "sendPacket.h"
#include "primitives.h"

/* emetteur (ma machine) ---> recepteur (machine suivante) */



enum State {
    standby, listen, send
} currStatus;

/* Paquet <=> struct paquet */



int main(int argc, char **argv) {
    char line[10];
    Host PC;

    char choix = 0;
    char *initHost;
    char buffer[LONGUEUR_MESSAGE] = {0};
    bool stop = false;
    bool asToken = false;

    initHost = addHost();
    PC.HOST_NUMBER = initHost[0] - 48;
    PC.PRISE_EMISSION = initHost[2] - 48;
    PC.PRISE_RECEPTION = initHost[4] - 48;
    PC.PORT_EMISSION = (int) strtol(&initHost[32], NULL, 10);
    PC.PORT_RECEPTION = (int) strtol(&initHost[26], NULL, 10);
    memcpy(PC.ADRESSE, &initHost[5], 9);

    printf("Vous êtes le pc n°: %d\n", PC.HOST_NUMBER);
    Paquet currPacket;
    if (PC.PORT_EMISSION == 19000) {
        char initBuffer[LONGUEUR_MESSAGE] = {0};
        printf("!! INIT NETWORK TOKEN !!");
        sprintf(initBuffer, "%d,%d,%d,%d,%s", PC.HOST_NUMBER, 0, 0,
                0, "(TOKEN) INIT NETWORK");
        envoie(PC.PRISE_EMISSION, initBuffer, strlen(initBuffer));
    }


    while (!stop) {
        printf("EN ATTENTE TOKEN\n");
        if (!asToken) {
            recoit(PC.PRISE_RECEPTION, buffer, sizeof(buffer) - 1);
            traitePaquet(PC, buffer);
            if (PC.HOST_NUMBER == (int) buffer[2] - 48) {
                asToken = true;
            }
        }
        if (asToken) {
            bool wantToSendMessage = false;
            printf("Voulez-vous envoyer un message ?");
            if (fgets(line, 10, stdin) && sscanf(line, "%d", &wantToSendMessage) != 1)
                wantToSendMessage = 0;
            if (wantToSendMessage) {
                sendNewPacket(PC, buffer);
            } else {
                memset(buffer, '\0', sizeof(buffer));
                if (PC.PORT_EMISSION == 19000){
                    sprintf(buffer, "%d,%d,%d,%d,%s", PC.HOST_NUMBER, 0, 0,
                            0, "(TOKEN)");
                }else{
                    sprintf(buffer, "%d,%d,%d,%d,%s", PC.HOST_NUMBER, PC.HOST_NUMBER + 1, 0,
                            0, "(TOKEN)");
                }
                envoie(PC.PRISE_EMISSION, buffer, strlen(buffer));
            }
            asToken = false;
        }
    }
    return 0;
}
