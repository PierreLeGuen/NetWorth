//
// Created by pierre on 09/03/19.
//
#include <stdio.h>
#include <string.h>

#include "sendPacket.h"
#include "packets.h"
#include "primitives.h"

void sendNewPacket(Host srcHost) {
    Paquet currPacket;

    char buffer[LONGUEUR_MESSAGE];
    char line[10];
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

    sprintf(buffer, "%d,%d,%s", srcHost.HOST_NUMBER, currPacket.HOST_NUMBER, currPacket.MESSAGE);
    envoie(srcHost.PRISE_EMISSION, buffer, strlen(buffer));
}