//
// Created by pierre on 08/03/19.
//

#include <stdio.h>
#include "packets.h"
#include "initPC.h"
#include <stdlib.h>
#include <string.h>
#include "primitives.h"


void traitePaquet(Paquet receivedPacket, Host AnHost) {
    char buffer[LONGUEUR_MESSAGE];

    if (AnHost.HOST_NUMBER == receivedPacket.HOST_NUMBER)
        /* si je suis le destinataire du paquet */
    {
        printf("Je suis le destinataire. \n");
        printf("MSG : %*s \n\n", 20, receivedPacket.MESSAGE);

    } else {
        /* sinon */
        printf("Je ne suis PAS le destinataire. \n");
        printf("DEST : %*d\n\n", 20, receivedPacket.HOST_NUMBER);
        printf("Routage vers destinataire\n");
        memset(buffer, '\0', sizeof(buffer));

        sprintf(buffer, "%d%120s", receivedPacket.HOST_NUMBER, receivedPacket.MESSAGE);
        envoie(AnHost.PRISE_EMISSION, buffer, strlen(buffer));
    }
}
