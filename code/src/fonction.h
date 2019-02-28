/*
		Auteurs										Projet de fin d'annee
	Thierno Mamoudou Sabaly							2017/2018
	Ali Housseine Silahi							Transmission des donnees et securite de l'infortion
	Cheikh Tidiane Thiam							Mathematique cryptographie
		
		Bienvenue
		Là nous definiront toutes les constante, les prototypes, nos structures

	Date : 01/11/2018 à 14h35mn


*/

#ifndef _MACONS_
#define _MACONS_
#define BOUT_LARG 40
#define BOUT_LONG 150
#define BOUT_CHIFF_LARG 20
#define BOUT_CHIFF_LONG 70

//un rendez-vous est une structure contenant le jours, l'heure.
typedef struct Rendez_Vous Rendez_Vous;
 struct Rendez_Vous{
 	int jours;
 	int mois;
 	int annee;
 	int heure;
 	int minutes;
};
//un patient est une atructure contenant un rendez-vous
typedef struct Patient Patient;
struct Patient{
	char prenom[50];
	char nom[50];
	char age[50];
	char traitement[50];
	char sexe;
	Rendez_Vous rv;
};

/*
	Dans le cadre de la gestion du temps, nous avons rassembler tous les mois en une 
	enumeration. 
*/
typedef enum mois mois;
enum mois{
	JANVIER, FEVRIER, MARS, AVRIL, MAI, JUIN, JUILLET, AOUT, SEPTEMBRE, OCTOBRE, NOVEMBRE, DECEMBRE
};
//Les actions possible de l'utilisateur sont notées ici dans une enumeration. 
typedef enum Lieu Lieu;
enum Lieu
{
	MEDECIN, SECRETAIRE, ACCUEILLE, AIDE
};

typedef enum boutton boutton;
enum boutton{
	ACC, MED, SEC, AID,
	//Les bouttons d'accueille
	ACC_BOUT_0, ACC_BOUT_1, ACC_BOUT_2, NULL_PART
};

//Les eums lies au secteur Medecin
typedef enum Bout_Acc Bout_Acc;
enum Bout_Acc{
	ESP_MEDACC_BOUT_1, ESP_MEDACC_BOUT_2, ESP_MEDACC_BOUT_3, DECONNECTE, ESP_MEDACC_BOUT_5, NONE
};

typedef enum Bout_Esp_Med Bout_Esp_Med;
enum Bout_Esp_Med{
	ESP_MED_BOUT_1, ESP_MED_BOUT_2, ESP_MED_BOUT_3, ESP_MED_BOUT_4, ESP_MED_BOUT_5, AUCUN
};

typedef enum Bout_Creer_Compte Bout_Creer_Compte;
enum Bout_Creer_Compte{
	ESP_MED_BOUT_CC1, ESP_MED_BOUT_CC2, ESP_MED_BOUT_CC3, ESP_MED_BOUT_CC4, ESP_MED_BOUT_CC5, ANN, NUL
};

typedef enum Bout_ID Bout_ID;
enum Bout_ID{
	ESP_MED_BOUT_ID1, ESP_MED_BOUT_ID2, ESP_MED_BOUT_ID3, NO_ID, RIEN
};

typedef enum Bout_MesDispo Bout_MesDispo;
enum Bout_MesDispo{
	NEW_DISPO, DELETE_DISPO, EDIT_DISPO, DISPO_DETAIL, ANNUL_EDITING, NOTHING
};

typedef enum Dispo_Creation Dispo_Creation;
enum Dispo_Creation{
	DC_JOURS, DC_MOIS, DC_ANNEE, DC_HEURE, DC_MINUTE, DC_VALIDE,
	DC_APRES_1, DC_APRES_2, DC_APRES_3, DC_APRES_4, DC_APRES_5,
	DC_AVANT_1, DC_AVANT_2, DC_AVANT_3, DC_AVANT_4, DC_AVANT_5,
	DC_QUIT, DC_RIEN
};

typedef enum Clic_Droit Clic_Droit;
enum Clic_Droit{
	ZONE_DISPO, ZONE_RV_MED, ZONE_RV_SEC, AUTRE_ZONE
};
//les enums lies au secteur secretaire
typedef enum Bout_Esp_Sec Bout_Esp_Sec;
enum Bout_Esp_Sec{
	ESP_SEC_BOUT_CONNECTE, ESP_SEC_BOUT_DECONNECTE, ESP_SEC_BOUT_CREERCOMPTE, ESP_SEC_BOUT_VOIRRV, ESP_SEC_BOUT_CREERRV, ESP_SEC_AUCUN 
};

typedef enum Bout_Connect_Sec Bout_Connect_Sec;
enum Bout_Connect_Sec{
	BOUT_CONNECT_NOM, BOUT_CONNECT_MDP, BOUT_CONNECT_OK, BOUT_CONNECT_QUIT, BOUT_CONNECT_RIEN
};

typedef enum Bout_Compte_Sec Bout_Compte_Sec;
enum Bout_Compte_Sec{
	BOUT_COMPTE_NOM, BOUT_COMPTE_MDP, BOUT_COMPTE_CMDP, BOUT_COMPTE_VALIDE, BOUT_COMPTE_QUIT, BOUT_COMPTE_RIEN
};

typedef enum Bout_VoirRv_Sec Bout_VoirRv_Sec;
enum Bout_VoirRv_Sec{
	MED_NOM, BOUT_VRV_QUIT, BOUT_VRV_RIEN
};
typedef enum  Bout_CreerPatient_Sec Bout_CreerPatient_Sec;
enum Bout_CreerPatient_Sec
{
	NOM_MED, CP_SUITE, NOM_PATIENT, PRENOM_PATIENT, SEXE_PATIENT, AGE_PATIENT, TRAITEMENT, FEMME, HOMME, RV_SUIVANT, RV_PRECEDENT,
	CP_BOUT_VALIDE, BOUT_CP_QUITTER, AUCUN_BOUT_CP
};

typedef enum souri souri;
enum souri{
	SURVOL, CLIC, AUTRE
};

typedef struct identifiant identifiant;
struct identifiant{
	char Nom_Utilisateur[50];
	char Mot_De_Pass[50];
};

#endif