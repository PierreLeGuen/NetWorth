//
// Created by pierre on 09/03/19.
//

#include "initHOST.h"

#ifndef NETWORTH_SENDPACKET_H
#define NETWORTH_SENDPACKET_H

/**
 * @brief Send a new packet in the network
 *
 * @param srcHost A filled Host struct
 */
void sendNewPacket(Host srcHost, char *buffer);

#endif //NETWORTH_SENDPACKET_H
