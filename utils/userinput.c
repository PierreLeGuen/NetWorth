//
// Created by pierre on 15/03/19.
//

#include <stdio.h>
#include "userinput.h"

int interaction_utilisateur() {
    char line[2048];
    int variable;
    if (fgets(line, 10, stdin) && sscanf(line, "%d", &variable) != 1)
        variable = 0;

    return variable;
}