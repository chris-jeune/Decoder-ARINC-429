#include "utilitaire.h"
#include <stdio.h>
#include <math.h>

void afficher_heure(unsigned int seconde)
{
	unsigned int heure= seconde/3600;
	unsigned int minute= (seconde%3600)/60;
	unsigned int sec= (seconde%3600)%60;
	printf("%02dh%02dm%02ds",heure,minute,sec);
}
unsigned int decimale_a_octale(unsigned int decimale) {
	unsigned int octale = 0;
	unsigned int puissance = 1;
	while (decimale != 0) {
		octale += (decimale % 8) * puissance;
		decimale /= 8;
		puissance *= 10;
	}
	return octale;
}

unsigned int calculer_nb_bits_actifs(unsigned int valeur) {
	unsigned int nb_bits_actifs = 0;
	while (valeur != 0) {
		nb_bits_actifs += valeur & 1;
		valeur >>= 1;  
	}
	return nb_bits_actifs;
}

void afficher_bits(unsigned int valeur, int position_bit_faible, int position_bit_fort)
{
	printf("(0x%08X) : ", valeur);
	for (int i = position_bit_fort; i >= position_bit_faible; i--) {
		printf("%d", (valeur &(1<<i))? 1:0);

		if((i-position_bit_faible)%4==0)
			printf(" ");
	}
	printf("\n");

}