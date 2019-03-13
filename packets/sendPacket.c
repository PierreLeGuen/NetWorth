//
// Created by pierre on 09/03/19.
//
#include <stdio.h>
#include <string.h>

#include "sendPacket.h"
#include "TraitePaquet.h"
#include "../primitives.h"
#include "packetChecker.h"


void sendNewPacket(Host srcHost, char *buffer) {
    Paquet currPacket = {0};

    char line[10];
    int destHostNumber = -1;
    bool isModeConnecte = false;

    printf("-- Saisir message :\n");
    fgets(currPacket.MESSAGE, 2000, stdin);

    printf("-- Destinataire (numPC) : \n");
    if (fgets(line, 10, stdin) && sscanf(line, "%d", &destHostNumber) != 1)
        destHostNumber = 0;

    printf("-- Mode avec CRC ? (Oui : 1/Non : 0) \n");
    if (fgets(line, 10, stdin) && sscanf(line, "%d", &isModeConnecte) != 1)
        isModeConnecte = 0;

    memset(buffer, '\0', sizeof(buffer));
    currPacket.HOST_NUMBER = destHostNumber;
    currPacket.containsMsg = true;
    if (srcHost.PORT_EMISSION != 19000) {
        currPacket.slotReserve = srcHost.HOST_NUMBER + 1;
    } else {
        currPacket.slotReserve = 0;
    }
    if (isModeConnecte) {
        const unsigned char *ptr2msg;
        ptr2msg = currPacket.MESSAGE;

        currPacket.CRC = crc16(ptr2msg, strlen(currPacket.MESSAGE) - 1);
        //TODO ERREUR AU niveau du CRC
        sprintf(buffer, "%d,%d,%d,%d,%d,%s", currPacket.containsMsg, srcHost.HOST_NUMBER, currPacket.HOST_NUMBER,
                currPacket.slotReserve, currPacket.CRC, currPacket.MESSAGE);
        printf("--- Presser ENTREE pour envoyer le message ---\n");
        while (getchar() != '\n');
        envoie(srcHost.PRISE_EMISSION, buffer, strlen(buffer));
        // envoie(srcHost.PRISE_EMISSION, buffer, strlen(buffer));
        // recoit(srcHost.PRISE_RECEPTION, buffer, sizeof(buffer) - 1);
        // traitePaquet(srcHost, buffer);
    } else {
        printf("Presser ENTREE pour envoyer le message\n");
        while (getchar() != '\n');
        sprintf(buffer, "%d,%d,%d,%d,%d,%s", currPacket.containsMsg, srcHost.HOST_NUMBER, currPacket.HOST_NUMBER,
                currPacket.slotReserve, 0, currPacket.MESSAGE);
        envoie(srcHost.PRISE_EMISSION, buffer, strlen(buffer));
    }
}
