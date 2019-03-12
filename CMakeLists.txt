cmake_minimum_required(VERSION 3.13)
project(networth)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(networth.exec
        hosts/creePriseEmission.c
        hosts/creePriseReception.c
        packets/envoie.c
        main.c
        #exempleCOMPLET-PC2.c
        Makefile
        primitives.h
        README.md
        packets/recoit.c hosts/initHOST.c hosts/initHOST.h packets/TraitePaquet.c packets/TraitePaquet.h packets/sendPacket.c packets/sendPacket.h packets/packetChecker.c packets/packetChecker.h)
add_executable(networth.exec.debug
        hosts/creePriseEmission.c
        hosts/creePriseReception.c
        packets/envoie.c
        main.c
        #exempleCOMPLET-PC2.c
        Makefile
        primitives.h
        README.md
        packets/recoit.c hosts/initHOST.c hosts/initHOST.h packets/TraitePaquet.c packets/TraitePaquet.h packets/sendPacket.c packets/sendPacket.h packets/packetChecker.c packets/packetChecker.h)