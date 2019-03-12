//
// Created by pierre on 08/03/19.
//

#include <sys/socket.h>
#include <stdio.h>
#include "initHOST.h"
#include "primitives.h"
#include "string.h"
#include <stdlib.h>

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
    /*
    char charNumPCSender[1];
    char charNumPCReceiver[1];
    char charPriseEmission[1];
    char charPriseReception[1];
    char charPortReception[5];
    char charPortEmission[5];
     */
    char *ADRESSE_EMETTEUR = malloc(15 * sizeof(char));
    char *ADRESSE_RECEPTEUR = malloc(15 * sizeof(char));

    if (local) {
        strcpy(ADRESSE_EMETTEUR, "127.0.0.1");
        strcpy(ADRESSE_RECEPTEUR, "127.0.0.1");
        /*
        sprintf(charNumPCSender, "%d", numPC);
        sprintf(charNumPCReceiver, "%d", numPC + 1);
         */
    } else {

        printf("Entrer IP prochain noeud \n");
        fgets(distIP, 20, stdin);
        strcpy(ADRESSE_EMETTEUR, "127.0.0.1");
        strcpy(ADRESSE_RECEPTEUR, distIP);
        // sprintf(charNumPCSender, "%d", numPC);
        // sprintf(charNumPCReceiver, "%d", numPC + 1);
    }
    if (isLastHost) {
        PORT_EMISSION = 19000;
        // sprintf(charNumPCReceiver, "%d", 0);
    }
    if (distIP[0] != (char) 0) {
        priseEmission = creePriseEmission(distIP, PORT_EMISSION);
    }
    else{
        priseEmission = creePriseEmission(ADRESSE_RECEPTEUR, PORT_EMISSION);
    }
    priseReception = creePriseReception(PORT_RECEPTION);
/*
    sprintf(charPriseEmission, "%d", priseEmission);
    sprintf(charPriseReception, "%d", priseReception);
    sprintf(charPortReception, "%d", PORT_RECEPTION);
    sprintf(charPortEmission, "%d", PORT_EMISSION);


    strncat(serialInitPC, charNumPCSender, 1);
    strncat(serialInitPC, ",", 1);
    strncat(serialInitPC, charPriseEmission, 1);
    strncat(serialInitPC, ",", 1);
    strncat(serialInitPC, charPriseReception, 1);
    strncat(serialInitPC, ",", 1);
    strncat(serialInitPC, ADRESSE_EMETTEUR, 9);
    strncat(serialInitPC, ",", 1);
    strncat(serialInitPC, ADRESSE_RECEPTEUR, 9);
    strncat(serialInitPC, ",", 1);
    strncat(serialInitPC, charPortReception, 5);
    strncat(serialInitPC, ",", 1);
    strncat(serialInitPC, charPortEmission, 5);
*/
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

    printf("Hote en loopback ? (true/false) \n");
    if (fgets(line, 10, stdin) && sscanf(line, "%d", &isLocalHost) != 1)
        isLocalHost = 0;
    printf("Choix du numéro d'hote (de 0 à 9, numérotation continue) \n");
    if (fgets(line, 10, stdin) && sscanf(line, "%d", &hostNumber) != 1)
        hostNumber = 0;
    if(hostNumber!=0){
        printf("C'était le dernier hote ? (true/false) \n");
        if (fgets(line, 10, stdin) && sscanf(line, "%d", &isLastHost) != 1)
            isLastHost = 0;
    }
    return initPC(hostNumber, isLocalHost, isLastHost);
}