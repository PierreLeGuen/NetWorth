
#ifndef NETWORTH_INITPC_H
#define NETWORTH_INITPC_H

/**
 * Énumérateur permettant de simuler le type bool en C.
 */
typedef enum {
    false, true
} bool;

/**
 * Structure contenant toute les informations nécessaires d'un hote.
 */
typedef  struct host{
    int HOST_NUMBER;
    char ADRESSE[9];
    int PORT_EMISSION;
    int PORT_RECEPTION;
    int PRISE_EMISSION;
    int PRISE_RECEPTION;
} Host;

/**
 * @brief Fonction permettant d'initialiser un hote.
 *
 * @return une structure de type "Host" remplie.
 */
Host addHost();

#endif //NETWORTH_INITPC_H
