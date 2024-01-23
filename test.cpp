#include <stdio.h>
#include "configuration.h"
#include "utilitaire.h"
#include <random>
#include"a429.h"
using namespace std;


void afficher_entete_test() {
	printf("/***************************************************************************************\n");
	printf("* DECODEUR ARINC-429 :: Mode Test\n*\n");
	printf("* Auteur  : Christian Jeune\n");
	printf("* Session : Hiver 2023\n*\n");
	printf("/***************************************************************************************\n");

}	

#ifdef TEST

int main() {
	afficher_entete_test();
	printf("\nTest de la fonction afficher_heure\n");
	for (int i = 0; i < 86400; i += 3661)
	{
		printf("%d secondes = ",i);
		afficher_heure(i);
		printf("\n");
	}

	printf("\n");

	default_random_engine generateur(static_cast<int>(time(0)));
	uniform_int_distribution<int> distribution(0, 209);
	printf("Test de la fonction decimale_a_octale\n");
	for (int i = 0; i < 7; i++)
	{
		int j = distribution(generateur);
		printf("%d = %d\n",j,decimale_a_octale(j));
	}	

	printf("\n");


	printf("Test de la fonction calculer_nb_bits_actifs\n");

		printf("0x00000000 = %d\n", calculer_nb_bits_actifs(0x00000000));
		printf("0x00000001 = %d\n",  calculer_nb_bits_actifs(0x00000001));
		printf("0x80000000 = %d\n",  calculer_nb_bits_actifs(0x80000000));
		printf("0x12345678 = %d\n",  calculer_nb_bits_actifs(0x12345678));
		printf("0xFFFFFFFF = %d\n",  calculer_nb_bits_actifs(0xFFFFFFFF));
	

	printf("\n");

	printf("Test de la fonction afficher_bits\n");

		afficher_bits(0x12345678, 0, 31);
		afficher_bits(0x9ABCDEF0, 0, 31);
		afficher_bits(0xA3CF8643, 4, 15);
		afficher_bits(0xA3CF8643, 31, 31);
		afficher_bits(0xA3CF8643, 0, 0);
		printf("\n");

	printf("\n");

	printf("Test de la fonction decoder_mot_a429\n");
	int est_corrompu;
	int numero_mot;
	double donnee_bnr;
	int donnee_bcd[4];
	decoder_mot_a429(0x85D3029A, est_corrompu, numero_mot, donnee_bnr, donnee_bcd);
	decoder_mot_a429(0x003C90B0, est_corrompu, numero_mot, donnee_bnr, donnee_bcd);
	decoder_mot_a429(0x812EAF68, est_corrompu, numero_mot, donnee_bnr, donnee_bcd);
	decoder_mot_a429(0x83D2E3C8, est_corrompu, numero_mot, donnee_bnr, donnee_bcd);
	decoder_mot_a429(0x00261AAA, est_corrompu, numero_mot, donnee_bnr, donnee_bcd);

	printf("\n");

	afficher_entete_decodeur();
	afficher_mot_a429(0x85D3029A);
	afficher_mot_a429(0x003C90B0);
	afficher_mot_a429(0x811c6268);
	afficher_mot_a429(0x840834c8);
	afficher_mot_a429(0xe68b4bc9);
	afficher_mot_a429(0x8001abaa);

	return 0;
}

#endif