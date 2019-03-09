//
// Created by pierre on 08/03/19.
//

#include <stdio.h>
#include "packets.h"
#include <string.h>
#include "primitives.h"


void traitePaquet(Host AnHost, char *buffer) {
    Host srcHost = {0};
    Host destHost = {0};
    Paquet recvPacket = {0};

    sscanf(buffer, "%d,%d,%64[^\\n]s", &srcHost.HOST_NUMBER, &destHost.HOST_NUMBER, recvPacket.MESSAGE);

    if (AnHost.HOST_NUMBER == destHost.HOST_NUMBER) {
        printf("Je suis le destinataire. \n");
        printf("MSG : %*s \n\n", 20, recvPacket.MESSAGE);

    } else {
        printf("Je ne suis PAS le destinataire. \n");
        printf("DEST : %*d\n\n", 20, destHost.HOST_NUMBER);
        printf("Routage vers destinataire\n");
        envoie(AnHost.PRISE_EMISSION, buffer, strlen(buffer));
    }
}
