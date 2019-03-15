
#ifndef NETWORTH_PACKETCHECKER_H
#define NETWORTH_PACKETCHECKER_H

#include "stdint.h"

/**
 * @brief fonction permettant de calculer le CRC d'un message
 *
 * @param message un pointeur vers le message à vérifier.
 * @param length la longueur du message à vérifier.
 * @return un entier correspondant au CRC à l'instant "t".
 */
unsigned short crc16(const unsigned char *message, unsigned char length);

#endif //NETWORTH_PACKETCHECKER_H
