#ifndef _RV_
#define _RV_

typedef struct rv rv;
struct rv
{
	char jours[20];
	int heure;
	int minute;
};

typedef struct patient patient;
struct patient
{
	char nom[50];
	char prenom[50];
	char sexe[20];
	int age;
	rv SonRv;
};

enum mois
{
	JANVIER = 1, FEVRIER = 2, MARS = 3, AVRIL = 4,  MAI = 5, JUIN = 6, JUILLET = 7,
	AOUT = 8,  SEPTEMBRE = 9, OCTOBRE = 10, NOVEMBRE = 11, DECEMBRE = 12
};

enum Jours
{
	LUNDI, MARDI, MERCREDI, JEUDI, VENDREDI, SAMEDI, DIMANCHE
};

#endif