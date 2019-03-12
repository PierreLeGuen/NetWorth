/*
 * envoie.c
 * Émission d'un datagramme sur une socket UDP "connectée"
 *
 * Travaux Pratiques réseau SILR 1
 * Nicolas Normand
 * 1999-2001
 */

#include <unistd.h>

#include "primitives.h"

int envoie (int prise, char *buffer, size_t taille)
{
    if (write (prise, buffer, taille) == taille)
	return 0;
    else
	return -1;
}

