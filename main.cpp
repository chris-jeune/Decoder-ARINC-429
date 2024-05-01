#include <stdio.h>
#include "a429.h"
#include "configuration.h"
#include "port_udp.h"

// Requis 11 : Compilation du sous-programme en mode APPLICATION
#ifdef APPLICATION
int main() {

	afficher_entete_decodeur();
	int id_port_udp = initialiser_port_udp(UDP_PORT_NUMBER);
	unsigned int valeur;
	unsigned int comparateur=0;
	while (1) {
		recevoir_port_udp(id_port_udp,&valeur , sizeof(valeur));
			// Requis 29 : Affichage des mots ARINC-429 reçus
			if (comparateur != valeur) {
				afficher_mot_a429(valeur);
				comparateur=valeur;
			}
			
			
		

	}



	return 0;
}
#endif // APPLICATION_MODE
