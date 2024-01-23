#include <stdio.h>
#include "a429.h"
#include "configuration.h"

// Requis 11 : Compilation du sous-programme en mode APPLICATION
#ifdef APPLICATION
int main() {

	// Requis 12 : Afficher l'ent�te du d�codeur
	afficher_entete_decodeur();

	// Requis 27 : Le port UDP 55001 doit �tre initialis�(utiliser le module port_udp).
	//int id_port_udp = initialiser_port_udp(UDP_PORT_NUMBER);
	//Requis 28 : Des lectures doivent �tre continuellement tent�es sur le port UDP 5501.
	unsigned int valeur;
	unsigned int comparateur;
	while (1) {
		//int nb_octets_recus = recevoir_port_udp(id_port_udp,&valeur , sizeof(valeur));
			// Requis 29 : Affichage des mots ARINC-429 re�us
			if (comparateur != valeur) {
				afficher_mot_a429(valeur);
				comparateur=valeur;
			}
			
			
		

	}



	return 0;
}
#endif // APPLICATION_MODE