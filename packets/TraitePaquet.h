#ifndef NETWORTH_PACKETS_H
#define NETWORTH_PACKETS_H

#include "../hosts/initHOST.h"

#define LONGUEUR_MESSAGE    2056
/**
 *
 */
typedef struct paquet {
    bool containsMsg;
    int HOST_NUMBER;
    char *ADDRESSE;
    int slotReserve;
    unsigned short CRC;
    char MESSAGE[LONGUEUR_MESSAGE];
} Paquet;

/**
 * @brief Traite le paquet (désencapsulation)
 *
 * @param AnHost Une structure Host
 * @param buffer Un buffer contenant le message reçu
 */
Paquet traitePaquet(Host AnHost, char *buffer);

#endif //NETWORTH_PACKETS_H
