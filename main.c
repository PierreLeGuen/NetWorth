
/**
 * Nicolas Vautier, Florian Daniel, Carlos Gomez-Tapia et Pierre Le Guen
 *
 * Fonctionnalités:
 * - Présence d'un unique message sur le ring;
 * - Choix entre loopback ou réseau réel;
 * - Calcul d'erreur (CRC)
 */

#define LONGUEUR_MESSAGE    2056
#include <stdio.h>
#include <string.h>
#include "hosts/initHOST.h"
#include "packets/TraitePaquet.h"
#include "packets/sendPacket.h"
#include "utils/primitives.h"
#include "utils/userinput.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

/*
 * Toutes les descriptions des fonctions sont présentes dans les header de chaque fonction.
 */
int main(int argc, char **argv) {
    Host AnHost;
    Paquet recvPacket = {0};

    char line[10];
    char buffer[LONGUEUR_MESSAGE] = {0};
    bool stop = false;
    bool asToken = false;

    /*
     * Initialisation de l'hote au lancement
     */
    AnHost = addHost();

    printf("-- HOTE n° : %d\n", AnHost.HOST_NUMBER);
    if (AnHost.PORT_EMISSION == 19000) {
        char initBuffer[LONGUEUR_MESSAGE] = {0};
        printf("--- INITIALISATION DU TOKEN ---\n");
        sprintf(initBuffer, "%d,%d,%d,%d,%d,%s", 0, AnHost.HOST_NUMBER, 0, 0,
                0, "\n");
        envoie(AnHost.PRISE_EMISSION, initBuffer, strlen(initBuffer));
        printf("--- TOKEN VERS HOTE 0 ---\n");
    }

    while (!stop) {
        printf("--- EN ATTENTE TOKEN ---\n\n");
        if (!asToken) {
            recoit(AnHost.PRISE_RECEPTION, buffer, sizeof(buffer) - 1);
            recvPacket = traitePaquet(AnHost, buffer);
            if (recvPacket.slotReserve == AnHost.HOST_NUMBER) {
                asToken = true;
                printf("--- TOKEN LIBRE ---\n");
            }
        }
        if (asToken) {
            bool wantToSendMessage = false;
            printf("-- Envoyer un message ?(Oui : 1/Non : 0)\n");
            wantToSendMessage = interaction_utilisateur();
            if (wantToSendMessage) {
                sendNewPacket(AnHost, buffer);
            } else {
                sendPacket(AnHost, buffer);
            }
            asToken = false;
        }
    }
    return 0;
}

#pragma clang diagnostic pop
