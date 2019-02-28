#include "fichier.h"
#include "enregistrer.c"

int main(){
	int nbr_patient1 = 0, nbr_patient2 = 0, nbr_patient3 = 0, quit;
	do{
		switch(Acceuille(&nbr_patient1, &nbr_patient2, &nbr_patient3)){
			case 1:
				Enregistrer(&nbr_patient1, &nbr_patient2, &nbr_patient3);
				break;
			case 2:
				Modifier();
				break;
			case 3:
				Supprimer();
				break;
			case 4:
				Affiche(&nbr_patient1, &nbr_patient2, &nbr_patient3);
				break;
			default :
				Acceuille(&nbr_patient1, &nbr_patient2, &nbr_patient3);
				break;
		}
		printf("5 => pour quitter Quitter, autre chiffre sinon \n");
		scanf("%d", &quit);
	}while(quit != 5);

}