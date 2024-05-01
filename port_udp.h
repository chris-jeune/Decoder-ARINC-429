/****************************************************************************************
*                                      PORT_UDP                                        *
****************************************************************************************
Auteur : Francis Bourdeau
Port pour macOS : Hugo Leblanc
Date création  : 2 septembre 2015
Dernière modification : 2 novembre 2023

Ce module permet la gestion d'un port UDP sous Windows.
Le code a été adapté du site web de Glenn Fiedler, visité le 02/09/2015
http://gafferongames.com/networking-for-game-programmers/sending-and-receiving-packets/


Dépendance avec des libraires additionnelles:
(project properties/linker/additionnal input/additionnal depencies
    - wsock32.lib


Liste des fonctions publiques:
    - initialiser_port_udp    : Permet de créer un port UDP.
    - detruire_port_udp       : Permet de libérer un port UDP.
    - recevoir_port_udp       : Permet de recevoire des données sur un port UDP.
    - transmettre_port_udp    : Permet de transmettre des données sur un port UDP.

*****************************************************************************************/

#ifndef __INF155_PORT_UDP__
#define __INF155_PORT_UDP__

/****************************************************************************************
*                           DÉFINTION DES TYPES ET CONSTANTES                           *
****************************************************************************************/


/****************************************************************************************
*                       DÉCLARATION DES FONCTIONS PUBLIQUES                             *
****************************************************************************************/

/*
    INITIALISER_PORT_UDP

    Cette fonction crée un port UDP et lui associe le numéro reçu.
    
    Paramètres:
        - numero_port : Le numéro attribué au port UDP créé.

    Retour: 
        - L'identifiant du port créé.

    Example d'appel:
        int id_port_udp;
        id_port_udp = initialiser_port_udp(55001);
*/
int initialiser_port_udp(int numero_port);


/*
    RECEVOIR_PORT_UDP

    Cette fonction tente de lire des données sur un port UDP.
    L'opération de lecture est non-blocante.
    
    Paramètres:
        - id_port_udp : L'identifiant du port UDP à paritr du quel les données sont lues.
        - donnees     : L'addresse où les données seront inscrite.
        - taille_donnees : L'espace disponible à l'addresse reçues.

    Retour: 
        - Le nombre d'octets lus.

    Example d'appel:
        int id_port_udp;
        unsigned int valeur_recue;
        
        id_port_udp = initialiser_port_udp(55001);
        recevoir_port_udp(id_port_udp, &valeur_recue, sizeof(unsigned int));
*/
int recevoir_port_udp(int id_port_udp, unsigned int * donnees, int taille_donnees);



/*
    TRANSMETTRE_PORT_UDP

    Cette fonction tente d'écrire des données sur un port UDP.
    L'opération d'écriture est non-blocante.
    
    Paramètres:
        - id_port_udp : L'identifiant du port UDP sur lequel les données sont écrites.
        - donnees     : L'addresse où les données sont conservées.
        - taille_donnees : La quantité de données à transmettre (en octet).

    Retour: 
        - Le nombre d'octets lus.

    Example d'appel:
        int id_port_udp;
        unsigned int valeur_transmise = 0x7F;
        
        id_port_udp = initialiser_port_udp(55000);
        recevoir_port_udp(id_port_udp, 55001, &valeur_transmise, sizeof(unsigned int));
*/
int transmettre_port_udp(int id_port_udp_transmetteur, int numero_port_recepteur, 
                         unsigned int * donnees, int taille_donnees);


#endif