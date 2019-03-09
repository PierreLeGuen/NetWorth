//
// Created by pierre on 08/03/19.
//

#ifndef NETWORTH_INITPC_H
#define NETWORTH_INITPC_H


typedef  struct host{
    int HOST_NUMBER;
    char ADRESSE[11];
    int PORT_EMISSION;
    int PRISE_EMISSION;
    int PRISE_RECEPTION;
} Host;

/**
 * @brief A function to add a PC in the network
 *
 * @param numPC
 * @return 1 : PC NUMBER, 2-
 */
char *initPC(int numPC);

#endif //NETWORTH_INITPC_H
