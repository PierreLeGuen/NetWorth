/*
 * primitives.h
 * Prototypes des primitives UDP
 *
 * Travaux Pratiques réseau SILR 1
 * Nicolas Normand
 * 1999-2001
 */

#include <sys/types.h>

int creePriseEmission (char *, int);

int creePriseReception (int);

int recoit (int, char *, size_t);

int envoie (int, char *, size_t);

