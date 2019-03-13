/*
 * creePriseReception.c
 * Ouverture d'une socket UDP et affectation d'un num�ro de port
 *
 * Travaux Pratiques r�seau SILR 1
 * Nicolas Normand
 * 1999-2001
 */

#include <stdio.h>	// perror
#include <netdb.h>	// socket, connect, hostent
#include <arpa/inet.h>  // sockaddr_in
#include <stdlib.h>	// exit
#include <string.h>	// memset

#include "../primitives.h"

int creePriseReception (int port)
{
    int			sock;
    struct sockaddr_in	address;

/*
 * Cr�ation d'une socket UDP :
 * PF_INET : famille de protocoles Internet
 * SOCK_DGRAM : communication par datagrammes
 * 0 : protocole UDP implicite (car Inet + Dgram)
 */
    if ((sock = socket (PF_INET, SOCK_DGRAM, 0)) == -1)
    {
	perror ("creerPriseReception");
    	exit (1);
    }

/*
 * Cr�ation d'une structure d'adresse de socket
 *
 * sin_family = AF_INET : famille d'adresses Internet
 *
 * sin_addr.s_addr = INADDR_ANY : l'adresse de r�ception n'est pas sp�cifi�e
 *   (la requ�te peut aboutir sur n'importe quelle interface locale)
 *
 * sin_port = htons (port) : le port de r�ception est sp�cifi�,
 *   conversion au format reseau (big endian) du num�ro de port,
 *   htons : host to network short integer)
 */
    memset (&address, 0, sizeof (address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons (port);

/*
 * Affectation d'une adresse locale � la socket
 */
    if (bind (sock,
	      (struct sockaddr*) &address,
	      sizeof (address)) == -1)
    {
	perror ("creerPriseReception");
	exit (1);
    }

    return sock;
}
