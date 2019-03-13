
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

Host addHost();

#endif //NETWORTH_INITPC_H
