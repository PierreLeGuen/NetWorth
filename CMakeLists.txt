cmake_minimum_required(VERSION 3.13)
project(networth C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(hosts)
include_directories(packets)

add_executable(networth.exec
        hosts/creePriseEmission.c
        hosts/creePriseReception.c
        hosts/initHOST.c
        hosts/initHOST.h
        packets/envoie.c
        packets/packetChecker.c
        packets/packetChecker.h
        packets/recoit.c
        packets/sendPacket.c
        packets/sendPacket.h
        packets/TraitePaquet.c
        packets/TraitePaquet.h
        main.c
        utils/primitives.h utils/userinput.c utils/userinput.h)
