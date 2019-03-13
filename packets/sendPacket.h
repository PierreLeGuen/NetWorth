#include "../hosts/initHOST.h"

#ifndef NETWORTH_SENDPACKET_H
#define NETWORTH_SENDPACKET_H

/**
 * @brief Send a new packet in the network
 *
 * @param srcHost A filled Host struct
 */
void sendNewPacket(Host srcHost, char *buffer);

#endif //NETWORTH_SENDPACKET_H
