//
// Created by pierre on 08/03/19.
//

#include <sys/socket.h>
#include <stdio.h>
#include "initPC.h"
#include "primitives.h"
#include "string.h"
#include <stdlib.h>

char *initPC(int numPC) {
    char *serialInitPC = calloc(256, sizeof(char));
    for (int i = 0; i < 256; ++i) {
        serialInitPC[i] = 0;
    }
    int priseEmission, priseReception;
    int PORT_EMISSION = 10000 + numPC;
    int PORT_RECEPTION = 10000 + numPC + 1;

    char charNumPCSender[1];
    char charNumPCReceiver[1];
    char charPriseEmission[1];
    char charPriseReception[1];

    char *ADRESSE_EMETTEUR = malloc(13);
    char *ADRESSE_RECEPTEUR = malloc(13);
    strcpy(ADRESSE_EMETTEUR, "192.168.0.100");
    strcpy(ADRESSE_RECEPTEUR, "192.168.0.100");

    sprintf(charNumPCSender, "%d", numPC);
    sprintf(charNumPCReceiver, "%d", numPC + 1);


    if (numPC < 10) {
        ADRESSE_EMETTEUR[12] = charNumPCSender[0];
        ADRESSE_RECEPTEUR[12] = charNumPCReceiver[0];
    } else {
        printf("Too much hosts, not supported yet");
        return NULL;
    }
    priseEmission = creePriseEmission(ADRESSE_RECEPTEUR, PORT_EMISSION);
    priseReception = creePriseReception(PORT_RECEPTION);

    sprintf(charPriseEmission, "%d", priseEmission);
    sprintf(charPriseReception, "%d", priseReception);

    strncat(serialInitPC, &charNumPCSender[0], 1);
    strncat(serialInitPC, ",", 1);
    strncat(serialInitPC, &charPriseEmission[0], 1);
    strncat(serialInitPC, ",", 1);
    strncat(serialInitPC, &charPriseReception[0], 1);
    strncat(serialInitPC, ",", 1);
    strncat(serialInitPC, ADRESSE_EMETTEUR, 13);
    strncat(serialInitPC, ",", 1);
    strncat(serialInitPC, ADRESSE_RECEPTEUR, 13);
    // strncat(serialInitPC)
    printf("%c", charPriseReception[0]);

    return serialInitPC;
}