//
// Created by pierre on 08/03/19.
//

#ifndef NETWORTH_INITPC_H
#define NETWORTH_INITPC_H

typedef enum {
    false, true
} bool;

typedef  struct host{
    int HOST_NUMBER;
    char ADRESSE[9];
    int PORT_EMISSION;
    int PORT_RECEPTION;
    int PRISE_EMISSION;
    int PRISE_RECEPTION;
} Host;

char *addHost();

#endif //NETWORTH_INITPC_H
