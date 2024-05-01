/****************************************************************************************
*                                      PORT_UDP                                        *
****************************************************************************************
Auteur : Francis Bourdeau
Port pour macOS : Hugo Leblanc
Date création  : 2 septembre 2015
Dernière modification : 2 novembre 2023

Ce module permet la gestion d'un port UDP sous Windows et macOS.
Le code a été adapté du site web de Glenn Fiedler, visité le 02/09/2015
http://gafferongames.com/networking-for-game-programmers/sending-and-receiving-packets/

*****************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS 


#include <winsock2.h>
typedef int socklen_t;

#include "port_udp.h"
#include "configuration.h"

/****************************************************************************************
*                           DÉFINTION DES TYPES ET CONSTANTES                           *
****************************************************************************************/

#define LOCAL_HOST "127.0.0.1"

#if defined(MODE_DEBUG) || defined(MODE_TEST)
#define UDP_LOG(format, ...)    std::cout << format << std::endl
#else
#define UDP_LOG(format, ...)
#endif

/****************************************************************************************
*                           DÉFINTION DES FONCTIONS PUBLIQUES                           *
****************************************************************************************/

int initialiser_port_udp(int numero_port)
{
    int id_socket;
    struct sockaddr_in addresse_ip;


    WSADATA WsaData;
    unsigned long operation_non_blocante;

    WSAStartup(MAKEWORD(2,2), &WsaData);


    id_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (id_socket == -1)
    {
        UDP_LOG("ERREUR : échec lors de la création du port [%i]\n", numero_port);
        exit(EXIT_FAILURE);
    }

    addresse_ip.sin_family = AF_INET;
    addresse_ip.sin_addr.s_addr = INADDR_ANY;
    addresse_ip.sin_port = htons(numero_port);

    if (bind(id_socket, (struct sockaddr*) &addresse_ip, sizeof(struct sockaddr_in)) < 0)
    {
        UDP_LOG("ERREUR : échec lors de l'association du port  [%i]\n", numero_port);
        exit(EXIT_FAILURE);
    }


    operation_non_blocante = 1;
    if (ioctlsocket(id_socket, FIONBIO, &operation_non_blocante) != 0)
    {
        UDP_LOG("ERREUR: le port [%i] ne peut être placé en mode non-bloquant\n", numero_port);
        exit(EXIT_FAILURE);
    }


    return id_socket;
}

int recevoir_port_udp(int id_port_udp, unsigned int* donnees, int taille_donnees)
{
    int nb_octets_recus;
    struct sockaddr_in sender_address;
    socklen_t sender_size = sizeof(sender_address);

    nb_octets_recus = recvfrom(id_port_udp, (char*)donnees, taille_donnees, 0, (struct sockaddr*) &sender_address, &sender_size);

    return nb_octets_recus;
}

int transmettre_port_udp(int id_port_udp_transmetteur, int numero_port_recepteur, unsigned int* donnees, int taille_donnees)
{
    int nb_octets_transmis;
    struct sockaddr_in addresse_ip;

    addresse_ip.sin_family = AF_INET;
    addresse_ip.sin_addr.s_addr = inet_addr(LOCAL_HOST);
    addresse_ip.sin_port = htons(numero_port_recepteur);

    nb_octets_transmis = sendto(id_port_udp_transmetteur, (char*)donnees, taille_donnees, 0, (struct sockaddr*) &addresse_ip, sizeof(addresse_ip));

    return nb_octets_transmis;
}
