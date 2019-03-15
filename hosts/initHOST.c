#include <sys/socket.h>
#include <stdio.h>
#include "initHOST.h"
#include "utils/primitives.h"
#include "string.h"
#include <stdlib.h>
#include <utils/userinput.h>

Host initPC(int numPC, bool local, bool isLastHost) {
    Host AnHost = {0};
    char distIP[20] = {0};
    char *serialInitPC = calloc(256, sizeof(char));
    for (int i = 0; i < 256; ++i) {
        serialInitPC[i] = 0;
    }
    int priseEmission, priseReception;
    int PORT_EMISSION = 19000 + (1 + numPC) * 50;
    int PORT_RECEPTION = 19000 + numPC * 50;

    char *ADRESSE_EMETTEUR = malloc(15 * sizeof(char));
    char *ADRESSE_RECEPTEUR = malloc(15 * sizeof(char));

    if (local) {
        /*
         * Utilisation de l'adresse de loopback
         */
        strcpy(ADRESSE_EMETTEUR, "127.0.0.1");
        strcpy(ADRESSE_RECEPTEUR, "127.0.0.1");
    } else {
        /*
         * Si nous sommes dans un véritable réseau
         */
        printf("Entrer IP prochain noeud \n");
        fgets(distIP, 20, stdin);
        distIP[strlen(distIP) - 1] = '\000';
        strcpy(ADRESSE_EMETTEUR, "127.0.0.1");
        strcpy(ADRESSE_RECEPTEUR, distIP);
    }
    if (isLastHost) {
        PORT_EMISSION = 19000;
    }
    if (distIP[0] != (char) 0) {
        priseEmission = creePriseEmission(distIP, PORT_EMISSION);
    }
    else{
        priseEmission = creePriseEmission(ADRESSE_RECEPTEUR, PORT_EMISSION);
    }
    priseReception = creePriseReception(PORT_RECEPTION);
    AnHost.PORT_EMISSION = PORT_EMISSION;
    AnHost.PORT_RECEPTION = PORT_RECEPTION;
    AnHost.PRISE_EMISSION = priseEmission;
    AnHost.PRISE_RECEPTION = priseReception;
    for (int j = 0; j < strlen(ADRESSE_EMETTEUR); ++j) {
        AnHost.ADRESSE[j] = ADRESSE_EMETTEUR[j];
    }
    AnHost.HOST_NUMBER = numPC;
    return AnHost;
}

Host addHost() {
    char line[10];
    bool isLastHost = false;
    bool isLocalHost = true;
    int hostNumber = -1;
    char distIP[20] = {0};

    printf("Hote en loopback ? (Oui : 1/Non : 0) \n");
    isLocalHost = interaction_utilisateur();
    printf("Choix du numéro d'hote (de 0 à 9, numérotation continue) \n");
    hostNumber = interaction_utilisateur();
    if(hostNumber!=0){
        printf("C'était le dernier hote ? (Oui : 1/Non : 0) \n");
        isLastHost = interaction_utilisateur();
    }
    return initPC(hostNumber, isLocalHost, isLastHost);
}
