#include "enregistrer.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initialement(int *nbr_p1, int *nbr_p2, int *nbr_p3){
	char* tab3[10] = {"Medecin3/p1.bin", "Medecin3/p2.bin", "Medecin3/p3.bin", "Medecin3/p4.bin", "Medecin3/p5.bin", "Medecin3/p6.bin", "Medecin3/p7.bin", "Medecin3/p8.bin", "Medecin3/p9.bin", "Medecin3/p10.bin"};
	char* tab2[10] = {"Medecin2/p1.bin", "Medecin2/p2.bin", "Medecin2/p3.bin", "Medecin2/p4.bin", "Medecin2/p5.bin", "Medecin2/p6.bin", "Medecin2/p7.bin", "Medecin2/p8.bin", "Medecin2/p9.bin", "Medecin2/p10.bin"};
	char* tab1[10] = {"Medecin1/p1.bin", "Medecin1/p2.bin", "Medecin1/p3.bin", "Medecin1/p4.bin", "Medecin1/p5.bin", "Medecin1/p6.bin", "Medecin1/p7.bin", "Medecin1/p8.bin", "Medecin1/p9.bin", "Medecin1/p10.bin"};
	int i, j = 0;
	FILE* fichier = NULL;
	for(i=0; i<10; i++){
		fichier = fopen(tab1[i], "rb");
		if(fichier != NULL)
			j++;
		fclose(fichier);
	}
	if(j!=0)
		*nbr_p1 = j;
	else
		*nbr_p1 = 0;
	j = 0;
	for(i=0; i<10; i++){
		fichier = fopen(tab2[i], "rb");
		if(fichier != NULL)
			j++;
		fclose(fichier);
	}
	if(j!=0)
		*nbr_p2 = j;
	else
		*nbr_p2 = 0;
	j = 0;
	for(i=0; i<10; i++){
		fichier = fopen(tab3[i], "rb");
		if(fichier != NULL)
			j++;
		fclose(fichier);
	}
	if(j!=0)
		*nbr_p3 = j;
	else
		*nbr_p3 = 0;
	j = 0;

}

int Acceuille(int *nombre1, int *nombre2, int *nombre3){
	int choix;
	printf("-------------GESTIONNAIRE DE RENDEZ-VOUS------------\n");
	printf("\t1.Enregistrer un rv\t2.Modifier un rv\t3.Supprimer un rv\n\t4. Voir les rv\n");
	scanf("%d", &choix);
	system("cls");
	initialement(nombre1, nombre2, nombre3);
	return choix;
}

rv Creer_Rv(){
	rv prv;
	printf("Jours : ");
	scanf("%s", prv.jours);
	printf("Heure : ");
	scanf("%d", &prv.heure);
	printf("Minutes : ");
	scanf("%d", &prv.minute);
	return prv;
}

patient Creer_Patient(){
	patient p;
	printf("----------------Renseigner les champs------------------\n");
	printf("Nom : ");
	scanf("%s", p.nom);
	printf("Prenom : ");
	scanf("%s", p.prenom);
	printf("age : ");
	scanf("%d", &p.age);
	printf("sexe(M/F) : ");
	scanf("%s", p.sexe);
	printf("------------------Son rendez-vous-----------\n");
	p.SonRv = Creer_Rv();
	return p;
}

patient Enregistrer(int *nbr_p1, int *nbr_p2, int *nbr_p3){
	int nbr_p;
	char* tab[10];
	char* tab3[10] = {"Medecin3/p1.bin", "Medecin3/p2.bin", "Medecin3/p3.bin", "Medecin3/p4.bin", "Medecin3/p5.bin", "Medecin3/p6.bin", "Medecin3/p7.bin", "Medecin3/p8.bin", "Medecin3/p9.bin", "Medecin3/p10.bin"};
	char* tab2[10] = {"Medecin2/p1.bin", "Medecin2/p2.bin", "Medecin2/p3.bin", "Medecin2/p4.bin", "Medecin2/p5.bin", "Medecin2/p6.bin", "Medecin2/p7.bin", "Medecin2/p8.bin", "Medecin2/p9.bin", "Medecin2/p10.bin"};
	char* tab1[10] = {"Medecin1/p1.bin", "Medecin1/p2.bin", "Medecin1/p3.bin", "Medecin1/p4.bin", "Medecin1/p5.bin", "Medecin1/p6.bin", "Medecin1/p7.bin", "Medecin1/p8.bin", "Medecin1/p9.bin", "Medecin1/p10.bin"};
	int i;
	printf("1. Medecin 1	2. Medecin 2	3. Medecin 3\n");
	int choix;
	scanf("%d", &choix);
	system("cls");
	switch(choix){
		case 1:
			for(i=0; i<10;i++)
				tab[i]  = tab1[i];
			nbr_p = *nbr_p1;
			break;
		case 2:
			for(i=0; i<10;i++)
				tab[i]  = tab2[i];
			nbr_p = *nbr_p2;
			break;
		case 3:
			for(i=0; i<10;i++)
				tab[i]  = tab3[i];
			nbr_p = *nbr_p3;
			break;
		default :
			printf("Vous devez indiquer avec quel medecin\n");
			main();
			break;
	}
	patient client = Creer_Patient();
	char *chaine;
	FILE *fichier = NULL;
	for(i=0; i<10; i++){
		fichier = fopen(tab[i], "rb");
		if(fichier == NULL && nbr_p !=0){
			chaine = tab[i];
			break;
		}
		fclose(fichier);
	}
	if(nbr_p == 0)
		chaine = tab[0];
	fichier = fopen(chaine, "wb");
	fwrite(&client, sizeof(client), 1, fichier);
	fclose(fichier);
	return client;
}
void show(patient p, int nbr){
	printf("patient n_%d\n", nbr+1);
	printf("Patient : Nom = %s\t Prenom = %s\tSexe = %s\tage : %dans\n", p.nom, p.prenom, p.sexe, p.age);
	printf("Rendez-vous : %s a %dh%dmn\n", p.SonRv.jours, p.SonRv.heure, p.SonRv.minute);
	printf("----------------------------------------------------\n");
}
void Affiche(int *nbr_p1, int *nbr_p2, int *nbr_p3){
	int nbr_p;
	char* tab[10];
	char* tab3[10] = {"Medecin3/p1.bin", "Medecin3/p2.bin", "Medecin3/p3.bin", "Medecin3/p4.bin", "Medecin3/p5.bin", "Medecin3/p6.bin", "Medecin3/p7.bin", "Medecin3/p8.bin", "Medecin3/p9.bin", "Medecin3/p10.bin"};
	char* tab2[10] = {"Medecin2/p1.bin", "Medecin2/p2.bin", "Medecin2/p3.bin", "Medecin2/p4.bin", "Medecin2/p5.bin", "Medecin2/p6.bin", "Medecin2/p7.bin", "Medecin2/p8.bin", "Medecin2/p9.bin", "Medecin2/p10.bin"};
	char* tab1[10] = {"Medecin1/p1.bin", "Medecin1/p2.bin", "Medecin1/p3.bin", "Medecin1/p4.bin", "Medecin1/p5.bin", "Medecin1/p6.bin", "Medecin1/p7.bin", "Medecin1/p8.bin", "Medecin1/p9.bin", "Medecin1/p10.bin"};
	int i, num, choix;
	printf("1. Medecin 1	2. Medecin 2	3. Medecin 3\n");
	scanf("%d", &choix);
	system("cls");
	switch(choix){
		case 1:
			for(i=0; i<10;i++)
				tab[i]  = tab1[i];
			nbr_p = *nbr_p1;
			break;
		case 2:
			for(i=0; i<10;i++)
				tab[i]  = tab2[i];
			nbr_p = *nbr_p2;
			break;
		case 3:
			for(i=0; i<10;i++)
				tab[i]  = tab3[i];
			nbr_p = *nbr_p3;
			break;
		default :
			printf("Vous devez indiquer avec quel medecin \n");
			main();
			break;
	}
	patient p;
	FILE *fichier = NULL;
	for(i=0; i<10; i++){
		fichier = fopen(tab[i], "rb");
		if(fichier != NULL){
			fread(&p, sizeof(p), 1, fichier);
			show(p, i);
		}
		fclose(fichier);
	}
}
void Supprimer(){
	char* tab[10];
	char* tab3[10] = {"Medecin3/p1.bin", "Medecin3/p2.bin", "Medecin3/p3.bin", "Medecin3/p4.bin", "Medecin3/p5.bin", "Medecin3/p6.bin", "Medecin3/p7.bin", "Medecin3/p8.bin", "Medecin3/p9.bin", "Medecin3/p10.bin"};
	char* tab2[10] = {"Medecin2/p1.bin", "Medecin2/p2.bin", "Medecin2/p3.bin", "Medecin2/p4.bin", "Medecin2/p5.bin", "Medecin2/p6.bin", "Medecin2/p7.bin", "Medecin2/p8.bin", "Medecin2/p9.bin", "Medecin2/p10.bin"};
	char* tab1[10] = {"Medecin1/p1.bin", "Medecin1/p2.bin", "Medecin1/p3.bin", "Medecin1/p4.bin", "Medecin1/p5.bin", "Medecin1/p6.bin", "Medecin1/p7.bin", "Medecin1/p8.bin", "Medecin1/p9.bin", "Medecin1/p10.bin"};
	int i, num, choix;
	FILE *fichier = NULL;
	printf("1. Medecin 1	2.Medecin 2		3. Medecin 3\n");
	scanf("%d", &choix);
	system("cls");
	switch(choix){
		case 1:
			for (i = 0; i < 10; i++)
			{
				tab[i] = tab1[i];
			}
			break;
		case 2:
			for (i = 0; i < 10; i++)
			{
				tab[i] = tab2[i];
			}
			break;
		case 3:
			for (i = 0; i < 10; i++)
			{
				tab[i] = tab3[i];
			}
			break;
		default :
			printf("Vous devez choisir le dossier devant subir les suppressions\n");
			main();
			break;
	}
	printf("Vous voulez supprimer un rv : (1) oui ou (2) non  : ");
	scanf("%d", &choix);
	switch(choix){
		case 1:
			printf("Donner le numero du patient : ");
			scanf("%d", &num);
			remove(tab[num-1]);
			break;
		case 2:
			break;
		default :
			break;
	}
}

void Modifier(){
	char* tab[10];
	char* tab3[10] = {"Medecin3/p1.bin", "Medecin3/p2.bin", "Medecin3/p3.bin", "Medecin3/p4.bin", "Medecin3/p5.bin", "Medecin3/p6.bin", "Medecin3/p7.bin", "Medecin3/p8.bin", "Medecin3/p9.bin", "Medecin3/p10.bin"};
	char* tab2[10] = {"Medecin2/p1.bin", "Medecin2/p2.bin", "Medecin2/p3.bin", "Medecin2/p4.bin", "Medecin2/p5.bin", "Medecin2/p6.bin", "Medecin2/p7.bin", "Medecin2/p8.bin", "Medecin2/p9.bin", "Medecin2/p10.bin"};
	char* tab1[10] = {"Medecin1/p1.bin", "Medecin1/p2.bin", "Medecin1/p3.bin", "Medecin1/p4.bin", "Medecin1/p5.bin", "Medecin1/p6.bin", "Medecin1/p7.bin", "Medecin1/p8.bin", "Medecin1/p9.bin", "Medecin1/p10.bin"};
	int i, num, choix;
	printf("1. Medecin 1	2.Medecin 2		3. Medecin 3\n");
	scanf("%d", &choix);
	system("cls");
	switch(choix){
		case 1:
			for (i = 0; i < 10; i++)
			{
				tab[i] = tab1[i];
			}
			break;
		case 2:
			for (i = 0; i < 10; i++)
			{
				tab[i] = tab2[i];
			}
			break;
		case 3:
			for (i = 0; i < 10; i++)
			{
				tab[i] = tab3[i];
			}
			break;
		default :
			printf("Pour modifier, indiquer le dossier qui doit subir les modifications\n");
			main();
			break;
	}
	printf("Indiquer le numero du patient : ");
	scanf("%d", &num);
	printf("(1) Modifier le rv\n(2) Remplacer le client \n");
	scanf("%d", &choix);
	patient p;
	FILE *fichier = fopen(tab[num - 1], "rb");
	fread(&p, sizeof(p), 1, fichier);
	fclose(fichier);
	switch(choix){
		case 1:
			printf("Jours : ");
			scanf("%s", p.SonRv.jours);
			printf("Donner l'heure : ");
			scanf("%d", &p.SonRv.heure);
			printf("Minutes: ");
			scanf("%d", &p.SonRv.minute);
			break;
		case 2:
			printf("Nom : ");
			scanf("%s", p.nom);
			printf("Prenom : ");
			scanf("%s", p.prenom);
			printf("age : ");
			scanf("%d", &p.age);
			printf("sexe(M/F) : ");
			scanf("%s", p.sexe);
			printf("-----------Rendez-vous-------------------\n");
			printf("Jours : ");
			scanf("%s", p.SonRv.jours);
			printf("Heure : ");
			scanf("%d", &p.SonRv.heure);
			printf("Minutes: ");
			scanf("%d", &p.SonRv.minute);
			break;
		default :
			printf("Vous avez deux parametre à modifier il vous faut choisir un \n");
			Modifier();
			break;
	}
	fichier = fopen(tab[num-1], "wb");
	fwrite(&p, sizeof(p), 1, fichier);
	fclose(fichier);
}