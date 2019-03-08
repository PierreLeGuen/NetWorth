cmake_minimum_required(VERSION 3.13)
project(networth)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(networthPC1
        creePriseEmission.c
        creePriseReception.c
        envoie.c
        exempleCOMPLET-PC1.c
        #exempleCOMPLET-PC2.c
        Makefile
        primitives.h
        README.md
        recoit.c initPC.c initPC.h packets.c packets.h)

add_executable(networthPC2
        creePriseEmission.c
        creePriseReception.c
        envoie.c
        #exempleCOMPLET-PC1.c
        exempleCOMPLET-PC2.c
        Makefile
        primitives.h
        README.md
        recoit.c initPC.c initPC.h packets.c packets.h)