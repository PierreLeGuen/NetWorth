/*
 * creePriseEmission.c
 * Ouverture d'une socket UDP et "connexion"
 *
 * Travaux Pratiques r�seau SILR 1
 * Nicolas Normand
 * 1999-2001
 */

#include <stdio.h>	// perror
#include <netdb.h>	// socket, connect, hostent
#include <arpa/inet.h>  // sockaddr_in
#include <stdlib.h>

#include "primitives.h"	// exit
#include <string.h>	// memset

int creePriseEmission (char *server, int port)
{
    int			sock;
    struct sockaddr_in	address;
    struct hostent     *hp;

/*
 * Cr�ation d'une socket UDP :
 * PF_INET : famille de protocoles Internet
 * SOCK_DGRAM : communication par datagrammes
 * 0 : protocole UDP implicite (car inet + dgram)
 */
    if ((sock = socket (AF_INET, SOCK_DGRAM, 0)) == -1)
    {
	perror ("creerPriseEmission");
	exit (1);
    }

/*
 * R�solution d'adresse � partir du nom de l'h�te
 */
    hp = gethostbyname(server);
    if (hp == 0)
    {
	perror ("creerPriseEmission");
	exit (1);
    }

/*
 * Cr�ation d'une structure d'adresse de socket
 *
 * sin_family = AF_INET : famille d'adresses Internet
 *
 * sin_addr.s_addr : on r�cup�re l'adresse donn�e par gethostbyname
 *
 * sin_port = htons (port) : port destinataire,
 *   conversion au format reseau (big endian) du num�ro de port,
 *   htons : host to network short integer)
 */
    memset (&address, 0, sizeof (address));
    memcpy (&address.sin_addr, hp->h_addr, hp->h_length);
    address.sin_family = AF_INET;
    address.sin_port = htons (port);

/*
 * connect pour les sockets UDP permet d'affecter l'adresse destinataire
 * qui sera utilisee lors d'une emission avec send
 */
    if (connect (sock,
		 (struct sockaddr*) &address,
		 sizeof (struct sockaddr_in)) == -1)
    {
	perror ("creerPriseEmission");
	exit (1);
    }

    return sock;
}
