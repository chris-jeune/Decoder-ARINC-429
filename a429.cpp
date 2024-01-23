#include "a429.h"
#include "configuration.h"
#include <stdio.h>
#include "utilitaire.h"


// Définition du sous-programme
void afficher_entete_decodeur() {
    printf("/***************************************************************************************\n");
    printf("* DECODEUR ARINC-429\n*\n");
    // Requis 5 : Affichage des noms des auteurs
    printf("* Auteur  : Christian Jeune\n");

    // Requis 6 : Affichage de la session
    printf("* Session : Hiver 2023\n*\n");
    printf("/***************************************************************************************\n");
    // Requis 7 : Affichage des colonnes de données reçues
    printf("Mot ARINC-429 | Est Corrompu | Donnee\n");
    printf("--------------|--------------|----------------------------------------------------------\n");
}


void decoder_mot_a429(unsigned int valeur, int& est_corrompu, int& numero_mot, double& donnee_bnr, int donnee_bcd[4]) {
    //le numero de mot est le dernier octet
    numero_mot=decimale_a_octale((valeur&0xFF));
    //verification de la corruption avec le nombre de bits actifs
    est_corrompu=(calculer_nb_bits_actifs(valeur)%2==0)?ODD_PARITY:!ODD_PARITY;

    valeur >>= 8;//decalage de 8 bits

    //Decodage BCD
    if (numero_mot == 232 || numero_mot == 255 || numero_mot == 260) {
        
        for (int i = 0; i < 4; i++) {
			donnee_bcd[i]=(valeur&0x1F);
            valeur >>= 5;
		}
        return;
    }
    //Decodage BNR
    else {
        donnee_bnr = (valeur & 0x1FFFFF);
        if (numero_mot == 310 || numero_mot == 311) {
            donnee_bnr * 0.000172;

        }

        if ((valeur >> 21 & 0x3) == 3)
            donnee_bnr *= -1;
    }
    //test
    
    printf("est corrompu %d\n", est_corrompu);
    printf("numero mot %d\n", numero_mot);
    printf("donnee bnr %f\n", donnee_bnr);
    printf("donnee bcd %d\n", donnee_bcd[0]);
    printf("donnee bcd %d\n", donnee_bcd[1]);
    printf("donnee bcd %d\n", donnee_bcd[2]);
    printf("donnee bcd %d\n\n", donnee_bcd[3]);    
    

}

void afficher_mot_a429(unsigned int valeur) {
    int est_corrompu;
    int numero_mot;
    double donnee_bnr;
    int donnee_bcd[4];
    decoder_mot_a429(valeur, est_corrompu, numero_mot, donnee_bnr, donnee_bcd);
    printf("0x%08X    |     %s      |", valeur, (est_corrompu)?"oui":"   ");
    // Requis 8 : Affichage du numéro de mot
    switch (numero_mot) {
    case 150:
		printf("Heure du vol      : ");
        afficher_heure(donnee_bnr);
        printf("\n");
		break;
    case 232:
        printf("Depart de l'aeroport : ");
        for (int i = 0; i < 4; i++) {
            printf("%c", donnee_bcd[i] + 'A');
        }
        printf("\n");
        break;
     case 252:
         printf("Altitude          : %.1lf\n", donnee_bnr);
		break;
     case 255:
         printf("Arrive a l'aeroport : ");
         for (int i = 0; i < 4; i++) {
			printf("%c", donnee_bcd[i] + 'A');
		 }
		 printf("\n");
		 break;
	 case 260:
         printf("Date du vol : %02d/%02d/%02d\n", donnee_bcd[2],donnee_bcd[1],donnee_bcd[0]);
         printf("              |     %s      |\n",  "   ");
         break;
     case 310:
         printf("Latitude          : %lf\n", donnee_bnr);
		 break;
     case 311:
		 printf("Longitude         : %lf\n", donnee_bnr);
         break;
	 default:
		 printf("Donnee BNR : %lf\n", donnee_bnr);
		 printf("Donnee BCD : %d %d %d %d\n", donnee_bcd[0], donnee_bcd[1], donnee_bcd[2], donnee_bcd[3]);
		 break;
    }
}