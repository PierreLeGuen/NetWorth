//
// Created by pierre on 08/03/19.
//

#ifndef NETWORTH_PACKETS_H
#define NETWORTH_PACKETS_H

#include "initPC.h"

#define LONGUEUR_MESSAGE    128

typedef struct paquet {
    int HOST_NUMBER;
    char *ADDRESSE;
    char MESSAGE[LONGUEUR_MESSAGE];
} Paquet;

void traitePaquet(Paquet receivedPacket, Host AnHost);

#endif //NETWORTH_PACKETS_H
