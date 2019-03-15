/*
 * envoie.c
 * �mission d'un datagramme sur une socket UDP "connect�e"
 *
 * Travaux Pratiques r�seau SILR 1
 * Nicolas Normand
 * 1999-2001
 */

#include <unistd.h>

#include "utils/primitives.h"

int envoie (int prise, char *buffer, size_t taille)
{
    if (write (prise, buffer, taille) == taille)
	return 0;
    else
	return -1;
}
