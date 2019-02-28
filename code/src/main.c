/*
		Auteurs										Projet de fin d'annee
	Thierno Mamoudou Sabaly							2017/2018
	Ali Housseine Silahi							Transmission des donnees et securite de l'infortion
	Cheikh Tidiane Thiam							Mathematique cryptographie

		Bienvenue
		Ici se trouve le centre du projet, c'est la fonction principale. Cette derniere fera
		appelle au autres definient dans "fonction.c"


	Date : 01/11/2018 à 14h35mn

*/


#include "fonction.c"
/*
	Inclusion des autres fonctions, bien-sur avec tous ces autres que le fichier "fonction.c"
	inclu.
*/

int main(int argc, char **argv){
	SDL_Surface *ecran = NULL, *Ligne_Vertical =  NULL;
	SDL_Event event;
	int continuer = 1, i;
	int Fenetre_Long = 1000, Fenetre_Larg = 600, Compter_clic = 0;
	SDL_Rect position, Pos_Lig_Vert;
	position.x = 50;
	position.y = 600;
	Pos_Lig_Vert.x = 250;
	Pos_Lig_Vert.y = 70;

	//Dans l'acceuille, declaration de l'ensemble des variables
	SDL_Surface *Accuille_Boutton[4] = {NULL}, *Texte_Ass_Bout_Acc[4] = {NULL};
	char* Leg_Acc_Boutton[4] = {"  Accueil ", "Espace Secretaire", "Espace_Medecin", "  A propos"};
	SDL_Rect Pos_Acc_Boutton[4], Pos_Du_Texte[4];
	SDL_Color color = {0, 0, 0};

	//les action possible seront reperées par la variable suivante
	identifiant Mes_Id = {"", ""};
	identifiant Sec_Iden = {"", ""};
	
	TTF_Init();
	SDL_Init(SDL_INIT_VIDEO);

	SDL_WM_SetCaption("Agenda Electronique", NULL);
	SDL_WM_SetIcon(IMG_Load("images/tn_logoclinique.jpg"), NULL);
	//ligne verticale

	Creation_Fenetre(&ecran, &Fenetre_Long, &Fenetre_Larg);

	// l'acceuilles

	int Val_Boutton;
	for(i=0; i<4; i++){
		if(i==0){
			Pos_Acc_Boutton[0].x = 0;
			Pos_Acc_Boutton[0].y = 0;
		}else{
			Pos_Acc_Boutton[i].x = Pos_Acc_Boutton[i-1].x + BOUT_LONG + 1;
			Pos_Acc_Boutton[i].y = Pos_Acc_Boutton[i-1].y;
		}
		Pos_Du_Texte[i].x = Pos_Acc_Boutton[i].x + 10;
		Pos_Du_Texte[i].y = Pos_Acc_Boutton[i].y + 20;
	}
	for(i=0; i<4; i++){
		Creation_Boutton(&Accuille_Boutton[i], BOUT_LONG, BOUT_LARG, Leg_Acc_Boutton[i], color, &Texte_Ass_Bout_Acc[i]);
	}
	

	char Mon_Mot[100] = "";
	int compteur_clic = 0;
	souri La_Souri;
	boutton Appui_Sur_Bout = NULL_PART;
	boutton Zone_d_avant = NULL_PART;
/*Bouttons appuye dans la zone medecin*/

	Bout_Esp_Med Bout_Med_Appuye = AUCUN;
	Bout_Esp_Med Bout_Med_AppAvant = AUCUN;
	Bout_Esp_Med Bout_Med_Survole = AUCUN;

//Ce sont les variables permettant de stocker les bouttons appuyés dans l'accueille des medecins
	Bout_Acc Bout_Surv_AccMed = NONE;
	Bout_Acc Bout_App_AccMed = NONE;
	Bout_Acc Bout_AppPrec_AccMed = NONE;

//Ici les bouttons appuyés lors de l'identification
	Bout_ID Bout_For_Iden = RIEN;
	Bout_ID Bout_For_IdenBefore = RIEN;

	//ici les bouttons appuyé lors de la creation de compte
	Bout_Creer_Compte Bout_For_CC = NUL;
	Bout_Creer_Compte Bout_For_CCBefore = NUL;

	Bout_MesDispo Bout_NouvelDispo_Surv = NOTHING;
	Bout_MesDispo Bout_NouvelDispo_App = NOTHING;
	Bout_MesDispo Bout_NouvelDispo_AppBefore = NOTHING;

	Dispo_Creation Bout_For_DC = DC_RIEN;

	/*Boutton appuye dans le zone secretaire.*/
	Bout_Esp_Sec Bout_Sec_Appuye = ESP_SEC_AUCUN;
	Bout_Esp_Sec Bout_Sec_AppAvant = ESP_SEC_AUCUN;
	Bout_Esp_Sec Bout_Sec_Survole = ESP_SEC_AUCUN;

	Bout_Connect_Sec Bout_ForConnexion_Sec = BOUT_CONNECT_RIEN;

	Bout_Compte_Sec Bout_ForCC_Sec = BOUT_COMPTE_RIEN;

	Bout_CreerPatient_Sec Bout_ForCP_Sec = AUCUN_BOUT_CP;

	Bout_VoirRv_Sec Bout_App_VoirRV_Sec = BOUT_VRV_RIEN;
	Bout_VoirRv_Sec Bout_Surv_VoirRV_Sec = BOUT_VRV_RIEN;

	boutton Pass_Sur_Bout = NULL_PART;
	Lieu Zone = ACCUEILLE;

	Clic_Droit clic_droit = AUTRE_ZONE;

	int temps_actuel = 0, temps_precedent = 0, nombre = 0, med_connected = 0, Sec_Connected = 0;
	char masque1[50] = "", masque2[50] = "", check_password[50] = "", confirm[50] = "Vous n'etes pas connecte", Dossier[50] = "";
	char Nom_Medecin_Connecte[50] = "";

	char masque1_Sec[50] = "", masque2_Sec[50] = "", check_password_Sec[50] = "", Dossier_Sec[50] = "";
	char Sec_Connecte[50] = "", Med_Pour_Rv[50] = "";


	Rendez_Vous Mes_Rv = {1, 1, 2018, 0, 0};
	time_t my_time;
	time(&my_time);
	struct tm *current_time = localtime(&my_time);
	Mes_Rv.jours = current_time->tm_mday;
	Mes_Rv.mois = current_time->tm_mon + 1;
	Mes_Rv.annee = current_time->tm_year + 1900;
	Mes_Rv.heure = current_time->tm_hour;
	Mes_Rv.minutes = current_time->tm_min;
	char day[10] = "", month[10] = "", year[50] = "", hour[10] = "", minute[10] = "";
	int Nombre_De_DispoCrees = 0;

	Patient Un_Patient = {"", "", "", "", 'M', Mes_Rv};
	int Un_Compteur = 1;
	int Nombre_De_RV = 0;
	char Un_Dossier[50] = "";
	FILE *Un_Fichier = NULL;

	SDL_Rect Pos_Clic_Droit;
	SDL_EnableKeyRepeat(30, 30);
	while(continuer){
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					continuer = 0;//Quite le programme
					break;
				case SDL_MOUSEMOTION:
					Pass_Sur_Bout = Mouse_Zone(event.motion.x, event.motion.y, Fenetre_Long, Fenetre_Larg, Pass_Sur_Bout);
					//Ici commence la gestion des bouttons survoles dans la zone medecin
					Bout_Med_Survole = Bout_survole_Med(event.motion.x, event.motion.y, Fenetre_Long, Fenetre_Larg, Bout_Med_Appuye);
					Bout_Surv_AccMed = Boutton_AccSurv(event.motion.x, event.motion.y, Fenetre_Long, Fenetre_Larg, Bout_Surv_AccMed);
					Bout_NouvelDispo_Surv = Boutton_MesDispos_Surv(event.motion.x, event.motion.y, Pos_Clic_Droit.x, Pos_Clic_Droit.y, Bout_NouvelDispo_Surv);
					//Fin de la gestion  des survole dans la zone medecin
					//Ici commence la gestion des bouttons survoles dans la zone secretaire
					Bout_Sec_Survole = Bout_Survole_Sec(event.motion.x, event.motion.y, Fenetre_Long, Fenetre_Larg);
					break;
				case SDL_MOUSEBUTTONUP:
					for(i=0; i<4; i++){
						if(event.button.x > Pos_Acc_Boutton[i].x && event.button.x < Pos_Acc_Boutton[i].x + BOUT_LONG
						 && event.button.y > Pos_Acc_Boutton[i].y && event.button.y< Pos_Acc_Boutton[i].y + BOUT_LARG){
							switch(i){
								case 0:
									Zone = ACCUEILLE;
									break;
								case 1:
									Zone = SECRETAIRE;
									break;
								case 2:
									Zone = MEDECIN;
									break;
								case 3:
									Zone = AIDE;
									break;
							}
						}else
							Zone = Zone;
					}
					Appui_Sur_Bout = Mouse_Zone(event.button.x, event.button.y, Fenetre_Long, Fenetre_Larg, Appui_Sur_Bout);

					/*Ici commence la gestion des clic dans la zone Medecin*/
					Bout_Med_Appuye = Bout_Appuye_Med(event.button.x, event.button.y, Fenetre_Long, Fenetre_Larg, Bout_Med_Appuye);
					Bout_For_Iden = Boutton_IDApp(event.button.x, event.button.y, Fenetre_Long, Fenetre_Larg, Bout_For_Iden);
					Bout_For_CCBefore = Bout_For_CC;
					Bout_For_CC = Boutton_CCApp(event.button.x, event.button.y, Fenetre_Long, Fenetre_Larg, Bout_For_CC);
					Bout_AppPrec_AccMed = Bout_App_AccMed;
					Bout_App_AccMed = Boutton_Acc(event.button.x, event.button.y, Fenetre_Long, Fenetre_Larg, Bout_App_AccMed);
					Bout_NouvelDispo_AppBefore = Bout_NouvelDispo_App;
					Bout_NouvelDispo_App = Boutton_MesDispos_App(event.button.x, event.button.y, Pos_Clic_Droit.x, Pos_Clic_Droit.y, Bout_NouvelDispo_App);
					Bout_For_DC = Boutton_App_Dispo(event.button.x, event.button.y, Fenetre_Long, Fenetre_Larg, Bout_For_DC);

					//ces blogs evitent que n'importe quel clic ouvre les fentres de connexion ou de creation de compte
					if(Bout_For_Iden != NO_ID && Bout_AppPrec_AccMed == ESP_MEDACC_BOUT_1){
						Bout_App_AccMed = Bout_AppPrec_AccMed;
					}if(Bout_For_Iden == NO_ID){
						strcpy(Mes_Id.Nom_Utilisateur, "");
						strcpy(Mes_Id.Mot_De_Pass, "");
						strcpy(masque1, "");
						Bout_App_AccMed = NONE;
					}

					if(Bout_For_CC != ANN && Bout_AppPrec_AccMed ==  ESP_MEDACC_BOUT_2){
						Bout_App_AccMed = Bout_AppPrec_AccMed;
					}else if(Bout_For_CC == ANN){
						strcpy(Mes_Id.Nom_Utilisateur, "");
						strcpy(Mes_Id.Mot_De_Pass, "");
						strcpy(masque1, "");
						strcpy(masque2, "");
						strcpy(check_password, "");
						Bout_App_AccMed = NONE;
					}

					//cette blog fait la meme chose mais pour cas de la creation de diponibilité
					if(Bout_For_DC != DC_QUIT && Bout_NouvelDispo_AppBefore == NEW_DISPO){
						Bout_NouvelDispo_App = Bout_NouvelDispo_AppBefore;
					}else if(Bout_For_DC == DC_QUIT){
						Bout_NouvelDispo_App = NOTHING;
						Mes_Rv.jours = current_time->tm_mday;
						Mes_Rv.mois = current_time->tm_mon + 1;
						Mes_Rv.annee = current_time->tm_year + 1900;
						Mes_Rv.heure = current_time->tm_hour;
						Mes_Rv.minutes = current_time->tm_min;
					}

					switch(Bout_For_DC){
						case DC_APRES_1:
							if(Mes_Rv.jours >= 1 && Mes_Rv.jours < 30)
								Mes_Rv.jours +=1;
							else
								Mes_Rv.jours = 1;
							break;
						case DC_APRES_2:
							if(Mes_Rv.mois >=1 && Mes_Rv.mois < 12)
								Mes_Rv.mois += 1;
							else
								Mes_Rv.mois = 1; 
							break;
						case DC_APRES_3:
							Mes_Rv.annee += 1;
							break;
						case DC_APRES_4:
							if(Mes_Rv.heure >= 0 && Mes_Rv.heure < 23)
								Mes_Rv.heure += 1;
							else
								Mes_Rv.heure = 0;
							break;
						case DC_APRES_5:
							if(Mes_Rv.minutes >= 0 && Mes_Rv.minutes < 59)
								Mes_Rv.minutes += 1;
							else
								Mes_Rv.minutes = 0;
							break;
						case DC_AVANT_1:
							if(Mes_Rv.jours > 1 && Mes_Rv.jours <= 30)
								Mes_Rv.jours -=1;
							else
								Mes_Rv.jours = 12;
							break;
						case DC_AVANT_2:
							if(Mes_Rv.mois > 1 && Mes_Rv.mois <= 12)
								Mes_Rv.mois -= 1;
							else
								Mes_Rv.mois = 12;
							break;
						case DC_AVANT_3:
							Mes_Rv.annee -= 1;
							break;
						case DC_AVANT_4:
							if(Mes_Rv.heure > 0 && Mes_Rv.heure <= 23)
								Mes_Rv.heure -= 1;
							else
								Mes_Rv.heure = 23;
							break;
						case DC_AVANT_5:
							if(Mes_Rv.minutes > 0 && Mes_Rv.minutes <= 59)
								Mes_Rv.minutes -= 1;
							else
								Mes_Rv.minutes = 59;
							break;
						default:
							break;
					}

					//Le suivant assure qu'une fois dans l'espace medecin les clic n'influence pas les autres parties
					if(Bout_Med_Appuye == ESP_MED_BOUT_1){
						Bout_App_AccMed = NONE;
					}else if(Bout_Med_Appuye == ESP_MED_BOUT_5){
						Bout_NouvelDispo_App = NOTHING;
					}else if(Bout_Med_Appuye == ESP_MED_BOUT_2){
						Bout_NouvelDispo_App = NOTHING;
						Bout_App_AccMed = NONE;
					}
					/*Fin des evenements de la souri en rapport avec la zone Medecin*/

					/* Clic de la souri dans la zone secretaire*/
					Bout_Sec_AppAvant = Bout_Sec_Appuye;
					Bout_Sec_Appuye = Bout_Appuye_Sec(event.button.x, event.button.y, Bout_Sec_Appuye);
					Bout_ForConnexion_Sec = App_Connexion_Sec(event.button.x, event.button.y, Bout_ForConnexion_Sec);
					Bout_ForCC_Sec = App_Compte_Sec(event.button.x, event.button.y, Bout_ForCC_Sec);
					Bout_ForCP_Sec = Bout_AppCP_Sec(event.button.x, event.button.y, Bout_ForCP_Sec);
					Bout_App_VoirRV_Sec = App_VoirRv_Sec(event.button.x, event.button.y, Bout_App_VoirRV_Sec);

					if(Bout_ForConnexion_Sec != BOUT_CONNECT_QUIT && Bout_Sec_AppAvant == ESP_SEC_BOUT_CONNECTE){
						Bout_Sec_Appuye = Bout_Sec_AppAvant;
					}else if(Bout_ForConnexion_Sec == BOUT_CONNECT_QUIT){
						strcpy(Sec_Iden.Nom_Utilisateur, "");
						strcpy(Sec_Iden.Mot_De_Pass, "");
						strcpy(masque1_Sec, "");
						Bout_Sec_Appuye = ESP_SEC_AUCUN;
					}

					if(Bout_ForCC_Sec != BOUT_COMPTE_QUIT && Bout_Sec_AppAvant == ESP_SEC_BOUT_CREERCOMPTE){
						Bout_Sec_Appuye = Bout_Sec_AppAvant;
					}else if(Bout_ForCC_Sec == BOUT_COMPTE_QUIT){
						strcpy(Sec_Iden.Nom_Utilisateur, "");
						strcpy(Sec_Iden.Mot_De_Pass, "");
						strcpy(masque1_Sec, "");
						strcpy(masque2_Sec, "");
						strcpy(check_password_Sec, "");
						Bout_Sec_Appuye = ESP_SEC_AUCUN;
					}

					if(Bout_ForCP_Sec != BOUT_CP_QUITTER && Bout_Sec_AppAvant == ESP_SEC_BOUT_CREERRV){
						Bout_Sec_Appuye = Bout_Sec_AppAvant;
					}else if(Bout_ForCP_Sec == BOUT_CP_QUITTER){
						strcpy(Med_Pour_Rv, "");
						strcpy(Un_Patient.prenom, "");
						strcpy(Un_Patient.nom, "");
						strcpy(Un_Patient.age, "");
						strcpy(Un_Patient.traitement, "");
						Un_Patient.rv = Mes_Rv;
						Un_Patient.sexe = 'M';
						Un_Compteur = 1;
						Bout_Sec_Appuye = ESP_SEC_AUCUN;
					}

					if(Bout_App_VoirRV_Sec != BOUT_VRV_QUIT && Bout_Sec_AppAvant == ESP_SEC_BOUT_VOIRRV){
						Bout_Sec_Appuye = Bout_Sec_AppAvant;
					}else if(Bout_App_VoirRV_Sec == BOUT_VRV_QUIT){
						strcpy(Med_Pour_Rv, "");
						Bout_Sec_Appuye = ESP_SEC_AUCUN;
					}

					if(Bout_Sec_Appuye == ESP_SEC_BOUT_CREERRV && Bout_ForCP_Sec == FEMME){
						Un_Patient.sexe = 'F';
					}else if(Bout_Sec_Appuye == ESP_SEC_BOUT_CREERRV && Bout_ForCP_Sec == HOMME){
						Un_Patient.sexe = 'M';
					}else if(Bout_Sec_Appuye == ESP_SEC_BOUT_CREERRV && Bout_ForCP_Sec == RV_SUIVANT){
						if(Un_Fichier != NULL){
							if(Un_Compteur < Nombre_De_DispoCrees)
								Un_Compteur++;
							else
								Un_Compteur = 1;
						}
						fclose(Un_Fichier);
					}else if(Bout_Sec_Appuye == ESP_SEC_BOUT_CREERRV && Bout_ForCP_Sec == RV_PRECEDENT){
						if(Un_Fichier != NULL){
							if(Un_Compteur > 1)
								Un_Compteur--;
							else
								Un_Compteur = Nombre_De_DispoCrees;
						}
						fclose(Un_Fichier);
					}
					//gestion de collision des zones

					if(Zone == ACCUEILLE){
						Bout_Med_Appuye = AUCUN;	
					}else if(Zone == SECRETAIRE){
						Bout_Med_Appuye = AUCUN;
					}else if(Zone == AIDE){
						Bout_Med_Appuye = AUCUN;
						Bout_Sec_Appuye = ESP_SEC_AUCUN;
					}else if(Zone == MEDECIN){
						Bout_Sec_Appuye = ESP_SEC_AUCUN;
					}

					if(event.button.button == SDL_BUTTON_RIGHT){
						if(Zone == MEDECIN && Bout_Med_Appuye == ESP_MED_BOUT_1){
							clic_droit = ZONE_DISPO;
							Pos_Clic_Droit.x = event.button.x;
							Pos_Clic_Droit.y = event.button.y;
						}else if(Zone == MEDECIN && Bout_Med_Appuye == ESP_MED_BOUT_2){
							clic_droit = ZONE_RV_MED;
						}else if(Zone == SECRETAIRE && Bout_Sec_Appuye == ESP_SEC_BOUT_VOIRRV){
							clic_droit = ZONE_RV_SEC;
						}
					}else if(Bout_NouvelDispo_App == NOTHING){
						clic_droit = AUTRE_ZONE;
					}
					break;
				case SDL_KEYDOWN:
					/*Gestion des saisi dans l'espace medecin*/
					if(Bout_App_AccMed == ESP_MEDACC_BOUT_2 && Bout_For_CC == ESP_MED_BOUT_CC1){
						strcat(Mes_Id.Nom_Utilisateur, Saisi_Chaine(event.key));
						strcat(Mes_Id.Nom_Utilisateur, Saisi_Chiffre(event.key));
					}else if(Bout_App_AccMed == ESP_MEDACC_BOUT_2 && Bout_For_CC == ESP_MED_BOUT_CC2){
						if(strcmp(Saisi_Chaine(event.key), "") != 0 || strcmp(Saisi_Chiffre(event.key), "") != 0)
							strcat(masque1, "*");
						strcat(Mes_Id.Mot_De_Pass, Saisi_Chaine(event.key));
						strcat(Mes_Id.Mot_De_Pass, Saisi_Chiffre(event.key));
					}else if(Bout_App_AccMed == ESP_MEDACC_BOUT_2 && Bout_For_CC == ESP_MED_BOUT_CC3){
						if(strcmp(Saisi_Chaine(event.key), "") != 0 || strcmp(Saisi_Chiffre(event.key), "") != 0)
							strcat(masque2, "*");
						strcat(check_password, Saisi_Chaine(event.key));
						strcat(check_password, Saisi_Chiffre(event.key));
					}else if(Bout_App_AccMed == ESP_MEDACC_BOUT_1 && Bout_For_Iden == ESP_MED_BOUT_ID1){
						strcat(Mes_Id.Nom_Utilisateur, Saisi_Chaine(event.key));
						strcat(Mes_Id.Nom_Utilisateur, Saisi_Chiffre(event.key));
					}else if(Bout_App_AccMed == ESP_MEDACC_BOUT_1 && Bout_For_Iden == ESP_MED_BOUT_ID2){
						if(strcmp(Saisi_Chaine(event.key), "") != 0 || strcmp(Saisi_Chiffre(event.key), "") != 0)
							strcat(masque1, "*");
						strcat(Mes_Id.Mot_De_Pass, Saisi_Chaine(event.key));
						strcat(Mes_Id.Mot_De_Pass, Saisi_Chiffre(event.key));
					}

					/*Gestion des saisi dans l'espace secretaire*/
					if(Bout_Sec_Appuye == ESP_SEC_BOUT_CONNECTE && Bout_ForConnexion_Sec == BOUT_CONNECT_NOM){
						strcat(Sec_Iden.Nom_Utilisateur, Saisi_Chaine(event.key));
						strcat(Sec_Iden.Nom_Utilisateur, Saisi_Chiffre(event.key));
					}else if(Bout_Sec_Appuye == ESP_SEC_BOUT_CONNECTE && Bout_ForConnexion_Sec == BOUT_CONNECT_MDP){
						if(strcmp(Saisi_Chaine(event.key), "") != 0 || strcmp(Saisi_Chiffre(event.key), "") != 0)
							strcat(masque1_Sec, "*");
						strcat(Sec_Iden.Mot_De_Pass, Saisi_Chaine(event.key));
						strcat(Sec_Iden.Mot_De_Pass, Saisi_Chiffre(event.key));
					}else if(Bout_Sec_Appuye == ESP_SEC_BOUT_CREERCOMPTE && Bout_ForCC_Sec == BOUT_COMPTE_NOM){
						strcat(Sec_Iden.Nom_Utilisateur, Saisi_Chaine(event.key));
						strcat(Sec_Iden.Nom_Utilisateur, Saisi_Chiffre(event.key));
					}else if(Bout_Sec_Appuye == ESP_SEC_BOUT_CREERCOMPTE && Bout_ForCC_Sec == BOUT_COMPTE_MDP){
						if(strcmp(Saisi_Chaine(event.key), "") != 0 || strcmp(Saisi_Chiffre(event.key), "") != 0)
							strcat(masque1_Sec, "*");
						strcat(Sec_Iden.Mot_De_Pass, Saisi_Chaine(event.key));
						strcat(Sec_Iden.Mot_De_Pass, Saisi_Chiffre(event.key));
					}else if(Bout_Sec_Appuye == ESP_SEC_BOUT_CREERCOMPTE && Bout_ForCC_Sec == BOUT_COMPTE_CMDP){
						if(strcmp(Saisi_Chaine(event.key), "") != 0 || strcmp(Saisi_Chiffre(event.key), "") != 0)
							strcat(masque2_Sec, "*");
						strcat(check_password_Sec, Saisi_Chaine(event.key));
						strcat(check_password_Sec, Saisi_Chiffre(event.key));
					}else if(Bout_Sec_Appuye == ESP_SEC_BOUT_CREERRV && Bout_ForCP_Sec == NOM_MED){
						strcat(Med_Pour_Rv, Saisi_Chaine(event.key));
					}else if(Bout_Sec_Appuye == ESP_SEC_BOUT_CREERRV && Bout_ForCP_Sec == NOM_PATIENT){
						if(Un_Fichier != NULL){
							strcat(Un_Patient.nom, Saisi_Chaine(event.key));
						}
						fclose(Un_Fichier);
					}else if(Bout_Sec_Appuye == ESP_SEC_BOUT_CREERRV && Bout_ForCP_Sec == PRENOM_PATIENT){
						if(Un_Fichier != NULL){
							strcat(Un_Patient.prenom, Saisi_Chaine(event.key));
						}
						fclose(Un_Fichier);
					}else if(Bout_Sec_Appuye == ESP_SEC_BOUT_CREERRV && Bout_ForCP_Sec == AGE_PATIENT){
						if(Un_Fichier != NULL){
							strcat(Un_Patient.age, Saisi_Chiffre(event.key));
						}
						fclose(Un_Fichier);
					}else if(Bout_Sec_Appuye == ESP_SEC_BOUT_CREERRV && Bout_ForCP_Sec == TRAITEMENT){
						if(Un_Fichier != NULL){
							strcat(Un_Patient.traitement, Saisi_Chaine(event.key));
							strcat(Un_Patient.traitement, Saisi_Chiffre(event.key));
						}
						fclose(Un_Fichier);
					}else if(Bout_Sec_Appuye == ESP_SEC_BOUT_VOIRRV && Bout_App_VoirRV_Sec == MED_NOM){
						strcat(Med_Pour_Rv, Saisi_Chaine(event.key));
					}


					switch(event.key.keysym.sym){
						case SDLK_ESCAPE:
							continuer = 0;
							break;
						case SDLK_BACKSPACE:
							if(Bout_App_AccMed == ESP_MEDACC_BOUT_2 && Bout_For_CC == ESP_MED_BOUT_CC1){
								if(strcmp(Mes_Id.Nom_Utilisateur, "") != 0){
									Mes_Id.Nom_Utilisateur[strlen(Mes_Id.Nom_Utilisateur) - 1] = '\0';
								}
							}else if(Bout_App_AccMed == ESP_MEDACC_BOUT_2 && Bout_For_CC == ESP_MED_BOUT_CC2){
								if(strcmp(masque1, "") != 0){
									masque1[strlen(masque1) - 1] = '\0';
								}
								if(strcmp(Mes_Id.Mot_De_Pass, "") != 0){
									Mes_Id.Mot_De_Pass[strlen(Mes_Id.Mot_De_Pass) - 1] = '\0';
								}
							}else if(Bout_App_AccMed == ESP_MEDACC_BOUT_2 && Bout_For_CC == ESP_MED_BOUT_CC3){
								if(strcmp(masque2, "") != 0)
									masque2[strlen(masque2) - 1] = '\0';
								if(strcmp(check_password, "") != 0){
									check_password[strlen(check_password) - 1] = '\0';
								}
							}else if(Bout_App_AccMed == ESP_MEDACC_BOUT_1 && Bout_For_Iden == ESP_MED_BOUT_ID1){
								if(strcmp(Mes_Id.Nom_Utilisateur, "") != 0){
									Mes_Id.Nom_Utilisateur[strlen(Mes_Id.Nom_Utilisateur) - 1] = '\0';
								}
							}else if(Bout_App_AccMed == ESP_MEDACC_BOUT_1 && Bout_For_Iden == ESP_MED_BOUT_ID2){
								if(strcmp(masque1, "") != 0){
									masque1[strlen(masque1) - 1] = '\0';
								}
								if(strcmp(Mes_Id.Mot_De_Pass, "") != 0){
									Mes_Id.Mot_De_Pass[strlen(Mes_Id.Mot_De_Pass) - 1] = '\0';
								}
							}

							//zone secretaire
							if(Bout_Sec_Appuye == ESP_SEC_BOUT_CONNECTE && Bout_ForConnexion_Sec == BOUT_CONNECT_NOM){
									if(strcmp(Sec_Iden.Nom_Utilisateur, "") != 0){
										Sec_Iden.Nom_Utilisateur[strlen(Sec_Iden.Nom_Utilisateur) - 1] = '\0';
									}
							}else if(Bout_Sec_Appuye == ESP_SEC_BOUT_CONNECTE && Bout_ForConnexion_Sec == BOUT_CONNECT_MDP){
								if(strcmp(masque1_Sec, "") != 0){
									masque1_Sec[strlen(masque1_Sec) - 1] = '\0';
								}
								if(strcmp(Sec_Iden.Mot_De_Pass, "") != 0){
									Sec_Iden.Mot_De_Pass[strlen(Sec_Iden.Mot_De_Pass) - 1] = '\0';
								}
							}else if(Bout_Sec_Appuye == ESP_SEC_BOUT_CREERCOMPTE && Bout_ForCC_Sec == BOUT_COMPTE_NOM){
									if(strcmp(Sec_Iden.Nom_Utilisateur, "") != 0){
										Sec_Iden.Nom_Utilisateur[strlen(Sec_Iden.Nom_Utilisateur) - 1] = '\0';
									}
							}else if(Bout_Sec_Appuye == ESP_SEC_BOUT_CREERCOMPTE && Bout_ForCC_Sec == BOUT_COMPTE_MDP){
								if(strcmp(masque1_Sec, "") != 0){
									masque1_Sec[strlen(masque1_Sec) - 1] = '\0';
								}
								if(strcmp(Sec_Iden.Mot_De_Pass, "") != 0){
									Sec_Iden.Mot_De_Pass[strlen(Sec_Iden.Mot_De_Pass) - 1] = '\0';
								}
							}else if(Bout_Sec_Appuye == ESP_SEC_BOUT_CREERCOMPTE && Bout_ForCC_Sec == BOUT_COMPTE_CMDP){
								if(strcmp(masque2_Sec, "") != 0)
									masque2_Sec[strlen(masque2_Sec) - 1] = '\0';
								if(strcmp(check_password_Sec, "") != 0){
									check_password_Sec[strlen(check_password_Sec) - 1] = '\0';
								}
							}else if(Bout_Sec_Appuye == ESP_SEC_BOUT_CREERRV && Bout_ForCP_Sec == NOM_MED){
								if(strcmp(Med_Pour_Rv, "") != 0)
									Med_Pour_Rv[strlen(Med_Pour_Rv) - 1] = '\0';
							}else if(Bout_Sec_Appuye == ESP_SEC_BOUT_CREERRV && Bout_ForCP_Sec == NOM_PATIENT){
								if(strcmp(Un_Patient.nom, "") != 0)
									Un_Patient.nom[strlen(Un_Patient.nom) - 1] = '\0';
							}else if(Bout_Sec_Appuye == ESP_SEC_BOUT_CREERRV && Bout_ForCP_Sec == PRENOM_PATIENT){
								if(strcmp(Un_Patient.prenom, "") != 0){
									Un_Patient.prenom[strlen(Un_Patient.prenom) - 1] = '\0';
								}
							}else if(Bout_Sec_Appuye == ESP_SEC_BOUT_CREERRV && Bout_ForCP_Sec == AGE_PATIENT){
								if(strcmp(Un_Patient.age, "") != 0)
									Un_Patient.age[strlen(Un_Patient.age) - 1] = '\0';
							}else if(Bout_Sec_Appuye == ESP_SEC_BOUT_CREERRV && Bout_ForCP_Sec == TRAITEMENT){
								if(strcmp(Un_Patient.traitement, "") != 0)
									Un_Patient.traitement[strlen(Un_Patient.traitement) - 1] = '\0';
							}else if(Bout_Sec_Appuye == ESP_SEC_BOUT_VOIRRV && Bout_App_VoirRV_Sec == MED_NOM){
								if(strcmp(Med_Pour_Rv, "") != 0)
									Med_Pour_Rv[strlen(Med_Pour_Rv) - 1] = '\0';
							}
							break;
						default:
							break;
					}
					break;
				case SDL_VIDEORESIZE:
					Fenetre_Long = event.resize.w;
					Fenetre_Larg = event.resize.h;
					Creation_Fenetre(&ecran, &Fenetre_Long, &Fenetre_Larg);
					break;
				default:
					break;
			}
		}
		Remplir_Surface(ecran, ecran, 255, 255, 255);
		Gauche_Anime(ecran, nombre, Fenetre_Long, Fenetre_Larg);
		Affiche_Date(ecran, Fenetre_Long, Fenetre_Larg);

		strcpy(Un_Dossier, "Medecins/");
		strcat(Un_Dossier, Med_Pour_Rv);
		strcat(Un_Dossier, "/identifiant.bin");
		Un_Fichier = fopen(Un_Dossier, "rb");
		
		strcpy(Dossier, "Medecins/");
		strcat(Dossier, Nom_Medecin_Connecte);
		temps_actuel = SDL_GetTicks();
		if(temps_actuel - temps_precedent > 5000){
			if(nombre < 5){
				nombre++;
			}
			temps_precedent = temps_actuel;
		}
		if(nombre >= 5)
			nombre = 0;

		//Plaçons les bouttons du menu
		for(i=0; i<4; i++){
			Placer_Les_Bouttons(ecran, Accuille_Boutton[i], Pos_Acc_Boutton[i]);
			Placer_Les_Bouttons(ecran, Texte_Ass_Bout_Acc[i], Pos_Du_Texte[i]);
			Remplir_Surface(ecran, Accuille_Boutton[i], 255, 255, 255);
		}
		switch(Pass_Sur_Bout){
			case ACC:
				Remplir_Surface(ecran, Accuille_Boutton[0], 200, 255, 205);
				Placer_Les_Bouttons(ecran, Texte_Ass_Bout_Acc[0], Pos_Du_Texte[0]);
				break;
			case SEC:
				Remplir_Surface(ecran, Accuille_Boutton[1], 200, 255, 205);
				Placer_Les_Bouttons(ecran, Texte_Ass_Bout_Acc[1], Pos_Du_Texte[1]);
				break;
			case MED:
				Remplir_Surface(ecran, Accuille_Boutton[2], 200, 255, 205);
				Placer_Les_Bouttons(ecran, Texte_Ass_Bout_Acc[2], Pos_Du_Texte[2]);
				break;
			case AID:
				Remplir_Surface(ecran, Accuille_Boutton[3], 200, 255, 205);
				Placer_Les_Bouttons(ecran, Texte_Ass_Bout_Acc[3], Pos_Du_Texte[3]);
				break;
			default:
				break;
		}

		switch(Zone){
			case ACCUEILLE:
				Remplir_Surface(ecran, Accuille_Boutton[0], 105, 210, 0);
				Affiche_Acceuille(ecran, Fenetre_Long, Fenetre_Larg, Appui_Sur_Bout, Mon_Mot, Pass_Sur_Bout);
				break;
			case MEDECIN:
				Remplir_Surface(ecran, Accuille_Boutton[2], 105, 210, 0);
				Espace_Medecin(ecran, Bout_Med_Survole, Bout_Med_Appuye, Mes_Id, Bout_Surv_AccMed, Bout_App_AccMed, Bout_For_Iden,
					Bout_For_CC, Bout_NouvelDispo_Surv, Bout_NouvelDispo_App, Bout_For_DC, masque1, check_password, masque2, &med_connected,
					confirm, Nom_Medecin_Connecte, Dossier, Mes_Rv, &Nombre_De_DispoCrees, Nombre_De_RV, clic_droit, Pos_Clic_Droit);
				break;
			case SECRETAIRE:
				Remplir_Surface(ecran, Accuille_Boutton[1], 105, 210, 0);
				Espace_Secretaire(ecran, Bout_Sec_Survole, Bout_Sec_Appuye, Bout_ForConnexion_Sec, Bout_ForCC_Sec, Sec_Iden, masque1_Sec, masque2_Sec,
					check_password_Sec, &Sec_Connected, Bout_ForCP_Sec, Med_Pour_Rv, Un_Patient, &Nombre_De_RV, &Un_Compteur,
					&Nombre_De_DispoCrees, Bout_App_VoirRV_Sec/*, clic_droit*/);
				break;
			case AIDE:
				Remplir_Surface(ecran, Accuille_Boutton[3], 105, 210, 0);
				break;
		}

		Ordonner_Dispos(Nom_Medecin_Connecte, Nombre_De_DispoCrees);
		if(strcmp(Med_Pour_Rv, "") != 0 && Sec_Connected == 1){
			Ordonner_Rv(Med_Pour_Rv, Nombre_De_RV);
			Suppression_Auto(Med_Pour_Rv);
		}else if(strcmp(Nom_Medecin_Connecte, "") != 0 && med_connected == 1){
			Ordonner_Rv(Nom_Medecin_Connecte, Nombre_De_DispoCrees);
			Suppression_Auto(Nom_Medecin_Connecte);
		}

		Bout_For_DC = DC_RIEN;
		fclose(Un_Fichier);
		SDL_Flip(ecran);
	}
	for(i=0; i<4; i++){
		SDL_FreeSurface(Accuille_Boutton[i]);
		SDL_FreeSurface(Texte_Ass_Bout_Acc[i]);
	}
	SDL_FreeSurface(Ligne_Vertical);
	SDL_FreeSurface(ecran);
	TTF_Quit();
	SDL_Quit();
}