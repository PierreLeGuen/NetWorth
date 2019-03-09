cmake_minimum_required(VERSION 3.13)
project(networth)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(networth.exec
        creePriseEmission.c
        creePriseReception.c
        envoie.c
        main.c
        #exempleCOMPLET-PC2.c
        Makefile
        primitives.h
        README.md
        recoit.c initHOST.c initHOST.h packets.c packets.h sendPacket.c sendPacket.h packetChecker.c packetChecker.h)
add_executable(networth.exec.debug
        creePriseEmission.c
        creePriseReception.c
        envoie.c
        main.c
        #exempleCOMPLET-PC2.c
        Makefile
        primitives.h
        README.md
        recoit.c initHOST.c initHOST.h packets.c packets.h sendPacket.c sendPacket.h packetChecker.c packetChecker.h)