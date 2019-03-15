#include "../hosts/initHOST.h"

#ifndef NETWORTH_SENDPACKET_H
#define NETWORTH_SENDPACKET_H

/**
 * @brief Envoi un nouveau paquet dans le réseau.
 *
 * @param srcHost Une structure Host remplie.
 */
void sendNewPacket(Host srcHost, char *buffer);

void sendPacket(Host srcHot, char *buffer);

#endif //NETWORTH_SENDPACKET_H
