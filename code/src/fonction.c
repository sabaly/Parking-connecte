/*
		Auteurs										Projet de fin d'annee
	Thierno Mamoudou Sabaly							2017/2018
	Ali Housseine Silahi							Transmission des donnees et securite de l'infortion
	Cheikh Tidiane Thiam							Mathematique cryptographie

		Bienvenue
		Ce fichier contient l'ensemble des fichiers auxquels nous ferons appel
		dans la fonction principale. Chacune de nos actions, enfin presque, sera 
		représentée par une fonction. Ceci pour nous permettre de mieux nous retrouver.

	Date : 01/11/2018 à 14h35mn
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <SDL\SDL.h>//Pour integrer une fenetre
#include <SDL\SDL_image.h>//permettra de charger des images de n'importe quelle extension
#include <SDL\SDL_ttf.h>//Pour pouvoir ecrire au niveau de la fenetre generee
#include "fonction.h"//inclusion des prototypes

void Creation_Fenetre(SDL_Surface **fenetre, int *longu, int *larg){

	*fenetre = SDL_SetVideoMode(*longu, *larg, 32, SDL_HWSURFACE|SDL_RESIZABLE|SDL_DOUBLEBUF);
}

void Creation_Boutton(SDL_Surface **fenetre, int longueur, int largeur, char* chaine, SDL_Color color, SDL_Surface **Surface_Texte){
	TTF_Font *police;
	police = TTF_OpenFont("polices/calibri.ttf", 14);
	*fenetre = SDL_CreateRGBSurface(SDL_HWSURFACE, longueur, largeur, 32, 0, 0, 0, 0);
	*Surface_Texte = TTF_RenderText_Blended(police, chaine, color);

	TTF_CloseFont(police);
}



void Remplir_Surface(SDL_Surface *fenetre, SDL_Surface *surface, int Val_R, int Val_G, int Val_B){
	SDL_FillRect(surface, NULL, SDL_MapRGB(fenetre->format, Val_R, Val_G, Val_B));
}

void Placer_Les_Bouttons(SDL_Surface* ecran, SDL_Surface* surface, SDL_Rect position){
	SDL_BlitSurface(surface, NULL, ecran, &position);
}

void Gauche_Anime(SDL_Surface* fenetre, int nombre, int longueur, int largeur){
	SDL_Surface *Photo = NULL, *Ligne_Verticale = NULL, *fond = NULL;
	SDL_Rect Pos_LV;
	int i;
	Pos_LV.x = 920;
	Pos_LV.y = 40;
	fond = SDL_CreateRGBSurface(SDL_HWSURFACE, 500, largeur, 32, 0, 0, 0, 0);
	SDL_FillRect(fond, NULL, SDL_MapRGB(fenetre->format, 255, 237, 173));
	SDL_BlitSurface(fond, NULL, fenetre, &Pos_LV);
	Ligne_Verticale = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, largeur, 32, 0, 0, 0, 0);
	SDL_BlitSurface(Ligne_Verticale, NULL, fenetre, &Pos_LV);
	SDL_FreeSurface(Ligne_Verticale);

	char* chaine[5] = {"photos/tn_cli.jpg", "photos/tn_cliniq.jpg", "photos/tn_cliniq2.jpg", "photos/tn_imcli.jpg", "photos/tn_clinique.jpg"};
	Photo = IMG_Load(chaine[nombre]);
	Pos_LV.x += 20;
	Pos_LV.y += 120;
	SDL_BlitSurface(Photo, NULL, fenetre, &Pos_LV);
	SDL_FreeSurface(Photo);
	SDL_FreeSurface(fond);

	SDL_Surface *Decrit = NULL;
	TTF_Font *police = TTF_OpenFont("polices/app850.fon", 36);
	SDL_Color noir = {0, 0, 0};
	Decrit = TTF_RenderText_Blended(police, "Images de photos de cliniques ou de produit medicaux....", noir);
	Pos_LV.y += 500;
	SDL_BlitSurface(Decrit, NULL, fenetre, &Pos_LV);
	SDL_FreeSurface(Decrit);

	SDL_Surface *texture[5] = {NULL};
	SDL_Rect Pos_Texture[5];
	char* les_phrase[5] = {"une clinique est un centre hospitalier", "Souvent specialisee en un ", "domaine bien preci. il y'a", "qui sont privees et d'autres",
" sont publiques."};
	TTF_Font *petit_arial = TTF_OpenFont("polices/ariali.ttf", 12);
	for(i=0; i<5; i++){
		if(i==0){
			Pos_Texture[i].x = 1160;
			Pos_Texture[i].y = 180;
		}else{
			Pos_Texture[i].x = Pos_Texture[i-1].x;
			Pos_Texture[i].y = Pos_Texture[i-1].y + 30;
		}

		texture[i] = TTF_RenderText_Blended(petit_arial, les_phrase[i], noir);
		SDL_BlitSurface(texture[i], NULL, fenetre, &Pos_Texture[i]);
		SDL_FreeSurface(texture[i]);
	}

	TTF_CloseFont(police);
	TTF_CloseFont(petit_arial);
}

void Affiche_Date(SDL_Surface* fenetre, int longueur, int largeur){
	SDL_Surface *texte1 = NULL, *texte2 = NULL, *alert_texte = NULL;
	SDL_Rect Pos_texte1, Pos_texte2, Pos_Alert;
	char *alert = "Assurez-vous que votre PC soit toujours a jours, pour la bonne gestion du temps.";
	TTF_Font *police1, *police2;
	SDL_Color noir = {0, 0, 0}, rouge = {200, 0, 0}, couleur = {140, 100, 103};

	police1 = TTF_OpenFont("polices/arial.ttf", 25);
	police2 = TTF_OpenFont("polices/arial.ttf", 14);
	TTF_SetFontStyle(police1, TTF_STYLE_UNDERLINE);

	texte1 = TTF_RenderText_Blended(police1, "DATE", couleur);
	Pos_texte1.x = longueur/3 + 100;
	Pos_texte1.y = 2*largeur/3 + 100;
	SDL_BlitSurface(texte1, NULL, fenetre, &Pos_texte1);
	SDL_FreeSurface(texte1);

	char chaine[50];
	time_t mon_temps;
	time(&mon_temps);
	sprintf(chaine, "%s", ctime(&mon_temps));
	texte2 = TTF_RenderText_Blended(police2, chaine, noir);
	Pos_texte2.x = longueur/3 + 50;
	Pos_texte2.y = 2*largeur/3 + 150;
	SDL_BlitSurface(texte2, NULL, fenetre, &Pos_texte2);
	SDL_FreeSurface(texte2);

	Pos_Alert.x = longueur/3 - 50;
	Pos_Alert.y = 2*largeur/3 + 170;
	alert_texte = TTF_RenderText_Blended(police2, alert, rouge);
	SDL_BlitSurface(alert_texte, NULL, fenetre, &Pos_Alert);
	SDL_FreeSurface(alert_texte);

	TTF_CloseFont(police1);
	TTF_CloseFont(police2);
}

void Affiche_Acceuille(SDL_Surface* fenetre, int longueur, int largeur, boutton Boutton_Appuye, char arech[100], boutton BOUT){
	char* chaine[2] = {"Les utilisateurs doivent etre reconnus en tant que personnels de la clinique",
	 	"Pour cela ils doivent disposer d'un compte d'utilisation."};
 	SDL_Surface *texte[2] = {NULL};
	SDL_Rect Pos_Texte[2];
	int i;
	Pos_Texte[0].x =  300;
	Pos_Texte[0].y = largeur/3 + 200;
	TTF_Font *police, *police1;
	police = TTF_OpenFont("polices/arial.ttf", 12);
	police1 = TTF_OpenFont("polices/arial.ttf", 20);
	SDL_Color color1 = {12, 14, 15};
	for(i=0; i<2; i++){
		if(i!=0){
			Pos_Texte[i].x = Pos_Texte[i-1].x;
			Pos_Texte[i].y = Pos_Texte[i-1].y + 30;
			texte[i] = TTF_RenderText_Blended(police, chaine[i], color1);
		}else{
			texte[i] = TTF_RenderText_Blended(police, chaine[i], color1);
		}
		SDL_BlitSurface(texte[i], NULL, fenetre, &Pos_Texte[i]);
	}

	//zone alert
	SDL_Surface *ligne = NULL, *texte_zone = NULL;
	SDL_Color couleur = {125, 12, 12};
	SDL_Rect Pos_Ligne, Pos_Texte_Alert;
	Pos_Ligne.x = 270;
	Pos_Ligne.y = 50;
	ligne = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, largeur, 16, 0, 0, 0, 0);
	SDL_BlitSurface(ligne, NULL, fenetre, &Pos_Ligne);
	SDL_FreeSurface(ligne);

	TTF_SetFontStyle(police1, TTF_STYLE_UNDERLINE);
	texte_zone = TTF_RenderText_Blended(police1, "Z o n e   d  '   i n f o s", couleur);
	Pos_Texte_Alert.x = 30;
	Pos_Texte_Alert.y = 50;
	SDL_BlitSurface(texte_zone, NULL, fenetre, &Pos_Texte_Alert);
	SDL_FreeSurface(texte_zone);

	//Logo 
	SDL_Surface *logo = NULL, *Leg_Logo[5] = {NULL};
	char* chaine1[5] = {"GESTIONNAIRE", "de", "RENDEZ-VOUS", "dans une", "CLINIQUE"};
	SDL_Rect Pos_Logo, Pos_Chaine1[5];
	SDL_Color color3 ={0, 128, 0};
	Pos_Logo.x = 300;
	Pos_Logo.y = largeur/3 - 100;
	logo = IMG_Load("images/logo.jpg");
	SDL_BlitSurface(logo, NULL, fenetre, &Pos_Logo);
	for(i=0; i<5; i++){
		if(i==0){
			Pos_Chaine1[i].x = 500;
			Pos_Chaine1[i].y = Pos_Logo.y; 
		}else{
			Pos_Chaine1[i].x = Pos_Chaine1[i-1].x;
			Pos_Chaine1[i].y = Pos_Chaine1[i-1].y + 30;
		}
	}

	for(i=0; i<5; i++){
		if(i==0 || i==2 || i==4){
			Leg_Logo[i] = TTF_RenderText_Blended(police1, chaine1[i], color3);
		}else
			Leg_Logo[i] = TTF_RenderText_Blended(police, chaine1[i], color3);

		SDL_BlitSurface(Leg_Logo[i], NULL, fenetre, &Pos_Chaine1[i]);
	}

	//Boutton de recherche
	SDL_Surface* Champ_Recherche = NULL;
	SDL_Rect Pos_ChSaisi;
	SDL_Color color2 = {0, 0, 0};
	Pos_ChSaisi.x = Pos_Texte[0].x + 20;//Abscisse ACC_BOUT_1 = 320
	Pos_ChSaisi.y = Pos_Texte[0].y - 100;//ordonnee ACC_BOUT_2 = largeur/3 + 100 
	Champ_Recherche = SDL_CreateRGBSurface(SDL_HWSURFACE, 250, 30, 16, 0, 0, 0, 0);
	SDL_FillRect(Champ_Recherche, NULL, SDL_MapRGB(fenetre->format, 214, 214, 214));
	SDL_BlitSurface(Champ_Recherche, NULL, fenetre, &Pos_ChSaisi);

	//Boutton de recherche
	SDL_Surface *recherche = NULL, *rech = NULL;
	SDL_Rect Pos_Rech;
	Pos_Rech.x = Pos_ChSaisi.x + 250 + 2;//abscisse ACC_BOUT_2 = 572
	Pos_Rech.y = Pos_ChSaisi.y;//ordonee ACC_BOUT_2 = largeur/100
	recherche = SDL_CreateRGBSurface(SDL_HWSURFACE, 104, 30, 32, 0, 0, 0, 0);
	SDL_FillRect(recherche, NULL, SDL_MapRGB(fenetre->format, 0, 79, 157));
	rech = TTF_RenderText_Blended(police1, "Rechercher", color2);
	SDL_BlitSurface(recherche, NULL, fenetre, &Pos_Rech);
	Pos_Rech.y +=5;
	SDL_BlitSurface(rech, NULL, fenetre, &Pos_Rech);

	SDL_Surface *Surf_Chaine_Arech = NULL;
	SDL_Rect Pos_Arech;
	Pos_Arech.x = Pos_ChSaisi.x;
	Pos_Arech.y = Pos_ChSaisi.y + 10;
	char Ma_Chaine[100] = "";
	switch(Boutton_Appuye){
		case ACC_BOUT_1:
			Surf_Chaine_Arech = TTF_RenderText_Blended(police, arech, color2);
			break;
		case ACC_BOUT_2:
			break;
		default:
			Surf_Chaine_Arech = TTF_RenderText_Blended(police, "", color2);
			break;
	}
	SDL_BlitSurface(Surf_Chaine_Arech, NULL, fenetre, &Pos_Arech);
	TTF_CloseFont(police1);
	TTF_CloseFont(police);
	SDL_FreeSurface(Surf_Chaine_Arech);
	for(i=0; i<2; i++){
		 SDL_FreeSurface(texte[i]);
	}
	for(i=0; i<5; i++){
		SDL_FreeSurface(Leg_Logo[i]);
	}
	SDL_FreeSurface(logo);
	SDL_FreeSurface(Champ_Recherche);
	SDL_FreeSurface(recherche);

}
/*De la commence La longue mise en place de la zone Medecin. 
Nous Creerons, ici des fonctions pour la plus part des actions qu'effectuera un medecin.
 D'abord il doit disposer d'un compte, Donc une fonction pour creer ce compte
 Ensuite s'y connecter donc une fonction pour la connexion
 Pour enfin Pouvoir creer des disponibilités (necessite aussi une fonction) et voir ses rendez-vous (une fonction aussi).
 C'est quatres fonction ,au minimum seront definies ici. Chacune de ces fonctions fera intervenir des elements necessitant des
 fonction, d'où ces autres fonctions supplementaires (tout de meme importantes).
 */
void Creation_Compte_Med(SDL_Surface* fenetre, identifiant id, Bout_Creer_Compte CC_App, char masqueur1[50], char masq_check[50],
	char masqueur2[50], char confirmation[50]){
	SDL_Surface *Surface = NULL, *text[3] = {NULL}, *Nom = NULL, *Iden = NULL, *Mdp = NULL, *Cr_Cmpt = NULL, *legende = NULL;
	SDL_Rect Pos_Surface, Pos_Nom, Pos_Iden, Pos_Mdp, Pos_Text[3], Pos_Leg;

	TTF_Font* police = TTF_OpenFont("polices/police.TTF", 14);
	SDL_Color couleur = {0, 255, 0};

	legende = SDL_CreateRGBSurface(SDL_HWSURFACE, 500, 20, 32, 0, 0, 0, 0);
	//SDL_FillRect(alert, NULL, SDL_MapRGB(fenetre->format, ))
	Cr_Cmpt = TTF_RenderText_Blended(police, "Creation de compte", couleur);
	Surface = SDL_CreateRGBSurface(SDL_HWSURFACE, 500, 200, 32, 0, 0, 0, 0);
	Pos_Surface.x = 300;
	Pos_Surface.y = 140;
	Pos_Leg.x = 300;
	Pos_Leg.y = 140;
	SDL_FillRect(Surface, NULL, SDL_MapRGB(fenetre->format, 12, 15, 200));
	SDL_BlitSurface(Surface, NULL, fenetre, &Pos_Surface);
	SDL_BlitSurface(legende, NULL, fenetre, &Pos_Leg);
	Pos_Surface.x +=150;
	SDL_BlitSurface(Cr_Cmpt, NULL, fenetre, &Pos_Surface);
	SDL_FreeSurface(Cr_Cmpt);
	SDL_FreeSurface(legende);
	SDL_FreeSurface(Surface);

	SDL_Color color = {232, 180, 0};
	Nom = TTF_RenderText_Blended(police, "Nom", color);
	Pos_Nom.x = 350;
	Pos_Nom.y = 170;
	Iden = TTF_RenderText_Blended(police, "Mot de passe", color);
	Pos_Iden.x = 350;
	Pos_Iden.y = 210;
	Mdp = TTF_RenderText_Blended(police, "Confirmez mot de passe", color);
	Pos_Mdp.x = 300;
	Pos_Mdp.y = 250;
	SDL_BlitSurface(Nom, NULL, fenetre, &Pos_Nom);
	SDL_BlitSurface(Iden, NULL, fenetre, &Pos_Iden);
	SDL_BlitSurface(Mdp, NULL, fenetre, &Pos_Mdp);

	SDL_FreeSurface(Nom);
	SDL_FreeSurface(Iden);
	SDL_FreeSurface(Mdp);

	int i;
	Pos_Text[0].x = 450;
	Pos_Text[0].y = 170;
	for(i=0; i<3; i++){
		text[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, 170, 30, 32, 0, 0, 0, 0);
		if(i!=0){
			Pos_Text[i].x  = Pos_Text[i-1].x;
			Pos_Text[i].y = Pos_Text[i-1].y + 40;
		}
	}

	for(i=0; i<3; i++){
		SDL_FillRect(text[i], NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));
		SDL_BlitSurface(text[i], NULL, fenetre, &Pos_Text[i]);
	}

	for(i=0; i<3; i++){
		SDL_FreeSurface(text[i]);
	}

	TTF_CloseFont(police);

	SDL_Surface *Bout_Annule = NULL, *Bout_Valide = NULL, *Final[2] = {NULL};
	SDL_Rect Pos_BoutVal, Pos_BoutAn;
	Pos_BoutVal.x = 520;
	Pos_BoutVal.y = 280;
	Pos_BoutAn.x = 620;
	Pos_BoutAn.y = 280;
	SDL_Color color1 = {0, 0, 0};
	TTF_Font *polic;
	polic = TTF_OpenFont("polices/arial.ttf", 12);
	Bout_Annule = IMG_Load("images/quitter.png");
	Bout_Valide = IMG_Load("images/creer.png");
	SDL_BlitSurface(Bout_Valide, NULL, fenetre, &Pos_BoutVal);
	SDL_BlitSurface(Bout_Annule, NULL, fenetre, &Pos_BoutAn);

	SDL_BlitSurface(Final[0], NULL, fenetre, &Pos_BoutVal);
	SDL_BlitSurface(Final[1], NULL, fenetre, &Pos_BoutAn);

	SDL_FreeSurface(Bout_Valide);
	SDL_FreeSurface(Bout_Annule);
	for(i=0; i<2; i++){
		SDL_FreeSurface(Final[i]);
	}

	SDL_Surface *Texte_Saisi_name = NULL, *Texte_Saisi_password = NULL, *Text_Saisi_Check = NULL, *alert = NULL, *TickWrong = NULL;
	SDL_Rect Pos_TS_NAME, Pos_TS_PASSWORD, Pos_TS_CheckPass, Pos_alert;
	FILE *fichier = NULL, *exist = NULL;
	TTF_Font *arial = TTF_OpenFont("polices/arial.ttf", 12);
	SDL_Color rouge = {255, 0, 0}, verte = {0, 255, 0};
	char name[50] = "", password[50] = "", check_password[50] = "";
	char dossier[50] = "Medecins/";
	Pos_TS_NAME.x = 450;
	Pos_TS_NAME.y = 185;
	Pos_TS_PASSWORD.x = 450;
	Pos_TS_PASSWORD.y = 225;
	Pos_TS_CheckPass.x = 450;
	Pos_TS_CheckPass.y = 265;
	Pos_alert.x = 620;
	Pos_alert.y = 270;
	identifiant mes_id = {"", ""};
	strcat(dossier, id.Nom_Utilisateur);
	strcat(dossier, "/identifiant.bin");
	switch(CC_App){
		case ESP_MED_BOUT_CC1:
			strcat(name, id.Nom_Utilisateur);
			strcat(name, "|");
			Texte_Saisi_name = TTF_RenderText_Blended(polic, name, color1);
			Texte_Saisi_password = TTF_RenderText_Blended(polic, masqueur1, color1);
			Text_Saisi_Check = TTF_RenderText_Blended(polic, masqueur2, color1);
			break;
		case ESP_MED_BOUT_CC2:
			strcat(password, masqueur1);
			strcat(password, "|");
			Texte_Saisi_password = TTF_RenderText_Blended(polic, password, color1);
			Texte_Saisi_name = TTF_RenderText_Blended(polic, id.Nom_Utilisateur, color1);
			Text_Saisi_Check = TTF_RenderText_Blended(polic, masqueur2, color1);
			break;
		case ESP_MED_BOUT_CC3:
			strcat(check_password, masqueur2);
			strcat(check_password, "|");
			Text_Saisi_Check = TTF_RenderText_Blended(polic, check_password, color1);
			Texte_Saisi_name = TTF_RenderText_Blended(polic, id.Nom_Utilisateur, color1);
			Texte_Saisi_password = TTF_RenderText_Blended(polic, masqueur1, color1);
			break;
		case ESP_MED_BOUT_CC4:
			exist = fopen(dossier, "rb");
			if(exist == NULL && strcmp(id.Nom_Utilisateur, "") != 0 && strcmp(id.Mot_De_Pass, masq_check) == 0){
				fichier = fopen(dossier, "wb");
				fwrite(&id, sizeof(identifiant), 1, fichier);
				fclose(fichier);
				fclose(exist);
				exist = fopen(dossier, "rb");
				if(exist != NULL){
					alert = TTF_RenderText_Blended(arial, "account created", verte);
					TickWrong = IMG_Load("images/tick.png");
				}else{
					alert = TTF_RenderText_Blended(arial, "No such folder", rouge);
					TickWrong = IMG_Load("images/wrong.png");
				}
				fclose(exist);
			}else if(exist != NULL){
					fread(&mes_id, sizeof(identifiant), 1, exist);
					alert = TTF_RenderText_Blended(arial, "account created", verte);
					if(strcmp(id.Mot_De_Pass, mes_id.Mot_De_Pass) != 0)
						alert = TTF_RenderText_Blended(arial, "already exist", rouge);
					TickWrong = IMG_Load("images/wrong.png");
					fclose(exist);
			}else if(strcmp(id.Nom_Utilisateur, "") != 0 && strcmp(id.Mot_De_Pass, masq_check) != 0){
				alert = TTF_RenderText_Blended(arial, "Mot de passe differents", rouge);
				TickWrong = IMG_Load("images/wrong.png");
				fclose(exist);
			}
			if(strcmp(id.Mot_De_Pass, "") == 0 || strcmp("", masq_check) == 0 || strcmp(id.Nom_Utilisateur, "") == 0){
				alert = TTF_RenderText_Blended(arial, "Don't let fields empty", rouge);
				TickWrong = IMG_Load("images/wrong.png");
				fclose(exist);
			}
			break;
		default:
			Texte_Saisi_name = TTF_RenderText_Blended(polic, id.Nom_Utilisateur, color1);
			Text_Saisi_Check = TTF_RenderText_Blended(polic, masqueur2, color1);
			Texte_Saisi_password = TTF_RenderText_Blended(polic, masqueur1, color1);
			break;
	}
	SDL_BlitSurface(Texte_Saisi_name, NULL, fenetre, &Pos_TS_NAME);
	SDL_BlitSurface(Texte_Saisi_password, NULL, fenetre, &Pos_TS_PASSWORD);
	SDL_BlitSurface(Text_Saisi_Check, NULL, fenetre, &Pos_TS_CheckPass);
	Pos_alert.y -= 10;
	SDL_BlitSurface(TickWrong, NULL, fenetre, &Pos_alert);
	Pos_alert.x +=17;
	SDL_BlitSurface(alert, NULL, fenetre, &Pos_alert);
	SDL_FreeSurface(alert);
	SDL_FreeSurface(TickWrong);
	SDL_FreeSurface(Texte_Saisi_name);
	SDL_FreeSurface(Texte_Saisi_password);
	SDL_FreeSurface(Text_Saisi_Check);
	TTF_CloseFont(polic);
	TTF_CloseFont(arial);

}

void Info_connectivite(SDL_Surface* fenetre, char chaine[100], int booleen){
	//une zone pour signaler la validation de l'incription ou le succe d'une connexion
	SDL_Surface *zone = NULL;
	TTF_Font *police = TTF_OpenFont("polices/arial.ttf", 15);
	SDL_Rect Pos_Zone;
	Pos_Zone.x = 300;
	Pos_Zone.y = 90;
	zone = SDL_CreateRGBSurface(SDL_HWSURFACE, 500, 50, 32, 0, 0, 0, 0);
	SDL_FillRect(zone, NULL, SDL_MapRGB(fenetre->format, 231, 230, 211));
	SDL_BlitSurface(zone, NULL, fenetre, &Pos_Zone);
	SDL_FreeSurface(zone);

	SDL_Surface *texte_sur_Zone = NULL;
	SDL_Rect Pos_TSZ;
	Pos_TSZ.x = 400;
	Pos_TSZ.y = 120;
	SDL_Color verte = {0, 255, 0}, rouge = {255, 0, 0};
	if(booleen){
		texte_sur_Zone = TTF_RenderText_Blended(police, chaine, verte);
	}else
		texte_sur_Zone = TTF_RenderText_Blended(police, chaine, rouge);
	SDL_BlitSurface(texte_sur_Zone, NULL, fenetre, &Pos_TSZ);
	SDL_FreeSurface(texte_sur_Zone);
	TTF_CloseFont(police);
}

void connecte(SDL_Surface* fenetre, identifiant* id, Bout_ID ID_App, char masqueur1[50], int *connected, char confirmation[50],
	char Med_Conn_Nom[50]){
	SDL_Surface *Surface = NULL, *Nom_Utilisateur = NULL, *Mdp = NULL, *Ok = NULL, *Annuler = NULL, *Legende = NULL, *text_leg = NULL;
	SDL_Rect Pos_Surface, Pos_NU, Pos_Mdp, Pos_Ok, Pos_Ann, Pos_Leg;
	TTF_Font* police = TTF_OpenFont("polices/police.TTF", 14);
	SDL_Color Ma_Couleur = {0, 0, 0}, Couleur = {255, 255, 255};
	Pos_Surface.x = 400;
	Pos_Surface.y = 90;
	Pos_Leg.x = 400;
	Pos_Leg.y = 90;
	Pos_NU.x = 420;
	Pos_NU.y = 180;
	Pos_Mdp.x = 420;
	Pos_Mdp.y = 240;
	Pos_Ok.x = 530;
	Pos_Ok.y = 400;
	Pos_Ann.x = 600;
	Pos_Ann.y = 400;
	SDL_Surface *Surface_NU = NULL, *Surface_Mdp = NULL, *Surface_Ok = NULL, *Surface_Ann = NULL;
	Nom_Utilisateur = TTF_RenderText_Blended(police, "Nom", Ma_Couleur);
	Mdp = TTF_RenderText_Blended(police, "Mot de passe", Ma_Couleur);
	Ok = TTF_RenderText_Blended(police, "Ok", Ma_Couleur);
	Annuler = TTF_RenderText_Blended(police, " Quitter", Ma_Couleur);
	Surface = SDL_CreateRGBSurface(SDL_HWSURFACE, 300, 350, 32, 0, 0, 0, 0);
	Legende = SDL_CreateRGBSurface(SDL_HWSURFACE, 300, 20, 32, 0, 0, 0, 0);
	text_leg = TTF_RenderText_Blended(police, "Connexion : Medecin", Couleur);
	SDL_FillRect(Legende, NULL, SDL_MapRGB(fenetre->format, 0, 81, 0));
	SDL_FillRect(Surface, NULL, SDL_MapRGB(fenetre->format, 74, 255, 165));
	SDL_BlitSurface(Surface, NULL, fenetre, &Pos_Surface);
	SDL_BlitSurface(Legende, NULL, fenetre, &Pos_Leg);
	Pos_Leg.x += 50;
	SDL_BlitSurface(text_leg, NULL, fenetre, &Pos_Leg);
	SDL_BlitSurface(Nom_Utilisateur, NULL, fenetre, &Pos_NU);
	SDL_BlitSurface(Mdp, NULL, fenetre, &Pos_Mdp);
	Surface_NU = SDL_CreateRGBSurface(SDL_HWSURFACE, 150, 30, 32, 0, 0, 0, 0);
	Surface_Mdp = SDL_CreateRGBSurface(SDL_HWSURFACE, 150, 30, 32, 0, 0, 0, 0);
	Surface_Ok = SDL_CreateRGBSurface(SDL_HWSURFACE, 50, 30, 32, 0, 0, 0, 0);
	Surface_Ann = SDL_CreateRGBSurface(SDL_HWSURFACE, 80, 30, 32, 0, 0, 0, 0);
	SDL_FillRect(Surface_Ann, NULL, SDL_MapRGB(fenetre->format, 255, 0, 0));
	SDL_FillRect(Surface_NU, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));
	SDL_FillRect(Surface_Mdp, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));
	SDL_FillRect(Surface_Ok, NULL, SDL_MapRGB(fenetre->format, 181, 230, 29));
	Pos_NU.x += 90;
	Pos_NU.y += 5;
	Pos_Mdp.x += 90;
	Pos_Mdp.y += 5;
	SDL_BlitSurface(Surface_NU, NULL, fenetre, &Pos_NU);
	SDL_BlitSurface(Surface_Mdp, NULL, fenetre, &Pos_Mdp);
	SDL_BlitSurface(Surface_Ok, NULL, fenetre, &Pos_Ok);
	SDL_BlitSurface(Surface_Ann, NULL, fenetre, &Pos_Ann);
	Pos_Ok.x += 7;
	Pos_Ok.y += 5;
	Pos_Ann.x += 5;
	Pos_Ann.y += 7;
	SDL_BlitSurface(Ok, NULL, fenetre, &Pos_Ok);
	SDL_BlitSurface(Annuler, NULL, fenetre, &Pos_Ann);

	SDL_FreeSurface(Nom_Utilisateur);
	SDL_FreeSurface(Mdp);
	SDL_FreeSurface(Ok);
	SDL_FreeSurface(Annuler);
	SDL_FreeSurface(Surface_Ann);
	SDL_FreeSurface(Surface_Ok);
	SDL_FreeSurface(Surface_Mdp);
	SDL_FreeSurface(Surface_NU);
	TTF_CloseFont(police);
	SDL_FreeSurface(Surface);
	SDL_FreeSurface(Legende);
	SDL_FreeSurface(text_leg);

	SDL_Surface *Saisi_NU = NULL, *Saisi_password = NULL, *tickWrong = NULL, *TW_Message = NULL;
	SDL_Rect Pos_Saisi_NU, Pos_Saisi_pssword, Pos_TickWrong;
	Pos_TickWrong.x = 460;
	Pos_TickWrong.y = 150;
	TTF_Font *police1 = TTF_OpenFont("polices/arial.ttf", 12);
	Pos_Saisi_NU.x = 510;
	Pos_Saisi_NU.y = 200;
	Pos_Saisi_pssword.x = 510;
	Pos_Saisi_pssword.y = 255;
	SDL_Color noire = {0, 0, 0}, green = {34, 177, 76}, red = {255, 0, 0};
	char dossier[50] = "Medecins/", user_name[50] = "", user_psswrd[50] = "";
	FILE* fichier = NULL;
	identifiant Mes_Id = {"", ""};
	strcat(dossier, id->Nom_Utilisateur);
	strcat(dossier, "/identifiant.bin");

	if(*connected == 1){
		SDL_BlitSurface(tickWrong, NULL, fenetre, &Pos_TickWrong);
		if(strcmp(id->Nom_Utilisateur, Med_Conn_Nom) ==0){
			TW_Message = TTF_RenderText_Blended(police1, " connected successfuly", green);
			tickWrong = IMG_Load("images/tick.png");
			SDL_BlitSurface(tickWrong, NULL, fenetre, &Pos_TickWrong);
			Pos_TickWrong.x += 15;
			SDL_BlitSurface(TW_Message, NULL, fenetre, &Pos_TickWrong);
		}else{
			TW_Message = TTF_RenderText_Blended(police1, " A user is already connected", red);
			tickWrong = IMG_Load("images/wrong.png");
			SDL_BlitSurface(tickWrong, NULL, fenetre, &Pos_TickWrong);
			Pos_TickWrong.x += 15;
			SDL_BlitSurface(TW_Message, NULL, fenetre, &Pos_TickWrong);
		}
		return;
	}
	switch(ID_App){
		case ESP_MED_BOUT_ID1:
			strcat(user_name, id->Nom_Utilisateur);
			strcat(user_name, "|");
			Saisi_NU = TTF_RenderText_Blended(police1, user_name, noire);
			Saisi_password = TTF_RenderText_Blended(police1, masqueur1, noire);
			break;
		case ESP_MED_BOUT_ID2:
			strcat(user_psswrd, masqueur1);
			strcat(user_psswrd, "|");
			Saisi_NU = TTF_RenderText_Blended(police1, id->Nom_Utilisateur, noire);
			Saisi_password = TTF_RenderText_Blended(police1, user_psswrd, noire);
			break;
		case ESP_MED_BOUT_ID3:
			fichier = fopen(dossier, "rb");
			if(fichier != NULL){
				fread(&Mes_Id, sizeof(identifiant), 1, fichier);
				if(strcmp(id->Nom_Utilisateur, Mes_Id.Nom_Utilisateur) == 0 && strcmp(id->Mot_De_Pass, Mes_Id.Mot_De_Pass) == 0){
					*connected = 1;
					sprintf(confirmation, "Docteur %s est connecte", Mes_Id.Nom_Utilisateur);
					strcpy(Med_Conn_Nom, Mes_Id.Nom_Utilisateur);
					TW_Message = TTF_RenderText_Blended(police1, "connected successfuly", green);
					tickWrong = IMG_Load("images/tick.png");
				}else{
					strcpy(confirmation, "Nom ou Mot de Passe incorrecte");
					TW_Message = TTF_RenderText_Blended(police1, "password or username incorrect", red);
					tickWrong = IMG_Load("images/wrong.png");
				}
			}else{
				if(*connected == 0){
					strcpy(confirmation, "Vous n'etes pas connecte");
				}
				TW_Message = TTF_RenderText_Blended(police1, "Please create an account", red);
			}
			if(strcmp(id->Nom_Utilisateur, "") == 0 || strcmp(id->Mot_De_Pass, "") == 0){
					TW_Message = TTF_RenderText_Blended(police1, "Empty fields", red);
					tickWrong = IMG_Load("images/wrong.png");
			}
			fclose(fichier);
			SDL_BlitSurface(tickWrong, NULL, fenetre, &Pos_TickWrong);
			break;
		default:
			Saisi_NU = TTF_RenderText_Blended(police1, id->Nom_Utilisateur, noire);
			Saisi_password = TTF_RenderText_Blended(police1, masqueur1, noire);
			SDL_BlitSurface(TW_Message, NULL, fenetre, &Pos_TickWrong);
			Pos_TickWrong.x += 18;
			SDL_BlitSurface(tickWrong, NULL, fenetre, &Pos_TickWrong);
			break;
	}
	SDL_BlitSurface(Saisi_NU, NULL, fenetre, &Pos_Saisi_NU);
	SDL_BlitSurface(Saisi_password, NULL, fenetre, &Pos_Saisi_pssword);
	Pos_TickWrong.x += 18;
	SDL_BlitSurface(TW_Message, NULL, fenetre, &Pos_TickWrong);
	SDL_FreeSurface(tickWrong);
	SDL_FreeSurface(TW_Message);
	SDL_FreeSurface(Saisi_password);
	SDL_FreeSurface(Saisi_NU);
	TTF_CloseFont(police1);
}


void Acceuille_Medecin(SDL_Surface* fenetre, identifiant ID, Bout_Acc AccMed_Surv, Bout_Acc AccMed_App, Bout_ID ID_App, 
	Bout_Creer_Compte CC_App, char masqueur1[50], char masq_check[50], char masqueur2[50], int *connected, char confirmation[50],
	char Med_Conn_Nom[50]){
	if(*connected){
		Info_connectivite(fenetre, confirmation, 1);
	}else
		Info_connectivite(fenetre, confirmation, 0);
	TTF_Font *police = TTF_OpenFont("polices/arial.ttf", 12);
	SDL_Color color = {0, 36, 72};
	int i;
	//message
	char* messages[3] = {"Apres Identification, chaque medecin pourra renseigner ses disponibilites en indiquant seulement",
				" la date(le jours et l'heure). Le secretariat se chargera de creer les rendez-vous pour chaque date",
				"  indiquee. Avant tous cela, il faut d'abord un compte d'utilisateur."};
	SDL_Surface* messag[3] = {NULL};
	TTF_Font *police1 = TTF_OpenFont("polices/BRADHITC.TTF", 15);
	SDL_Color color1 = {0, 0, 0};
	SDL_Rect Pos_Mess[3];
	Pos_Mess[0].x = 300;
	Pos_Mess[0].y = 150;
	for(i=0; i<3; i++){
		if(i!=0){
			Pos_Mess[i].x = Pos_Mess[i-1].x;
			Pos_Mess[i].y = Pos_Mess[i-1].y + 30;
		}
		messag[i] = TTF_RenderText_Blended(police1, messages[i], color);
		SDL_BlitSurface(messag[i], NULL, fenetre, &Pos_Mess[i]);
	}
	TTF_CloseFont(police1);
	//Boutton creer_compte et connectez_vous
	SDL_Surface *connexion = NULL, *CreerCompte = NULL, *Log_Conn = NULL, *deconnexion = NULL;
	SDL_Rect Pos_Conn, Pos_LogConn, Pos_LogCrCpt, Pos_Dec;
	TTF_Font *police2 = NULL;
	SDL_Color color2 = {0, 0, 255}, red = {255, 0, 0};
	switch(AccMed_Surv){
		case ESP_MEDACC_BOUT_1:
			police2 = TTF_OpenFont("polices/calibri.ttf", 20);
			TTF_SetFontStyle(police2, TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE | TTF_STYLE_BOLD);
			connexion = TTF_RenderText_Blended(police2, "Connectez-vous", color2);
			CreerCompte = TTF_RenderText_Blended(police, "Creer un compte", color2);
			deconnexion = TTF_RenderText_Blended(police, "Se deconnecter", red);
			break;
		case ESP_MEDACC_BOUT_2:
			police2 = TTF_OpenFont("polices/calibri.ttf", 20);
			TTF_SetFontStyle(police2, TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE | TTF_STYLE_BOLD);
			CreerCompte = TTF_RenderText_Blended(police2, "Creer un compte", color2);
			connexion = TTF_RenderText_Blended(police, "Connectez-vous", color2);
			deconnexion = TTF_RenderText_Blended(police, "Se deconnecter", red);
			break;
		case DECONNECTE:
			police2 = TTF_OpenFont("polices/calibri.ttf", 20);
			TTF_SetFontStyle(police2, TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE | TTF_STYLE_BOLD);
			CreerCompte = TTF_RenderText_Blended(police, "Creer un compte", color2);
			connexion = TTF_RenderText_Blended(police, "Connectez-vous", color2);
			deconnexion = TTF_RenderText_Blended(police2, "Se deconnecter", red);
			break;
		case NONE:
			connexion = TTF_RenderText_Blended(police, "Connectez-vous", color2);
			CreerCompte = TTF_RenderText_Blended(police, "Creer un compte", color2);
			deconnexion = TTF_RenderText_Blended(police, "Se deconnecter", red);
			break;
	}
	Log_Conn = IMG_Load("images/tn_connexion.jpg");
	Pos_LogConn.x = 300;
	Pos_LogConn.y = 250;
	SDL_BlitSurface(Log_Conn, NULL, fenetre, &Pos_LogConn);
	SDL_FreeSurface(Log_Conn);
	Pos_Conn.x = 500;//abscisse du BOUT_MED_3 et 4 500
	Pos_Conn.y = 250;//ordonnee du BOUT_MED_3 250
	SDL_BlitSurface(connexion, NULL, fenetre, &Pos_Conn);
	Pos_Conn.y = 295;//ordonnee du BOUT_MED_4 300
	SDL_BlitSurface(CreerCompte, NULL, fenetre, &Pos_Conn);
	Pos_Dec.x = 770;
	Pos_Dec.y = 430;
	SDL_BlitSurface(deconnexion, NULL, fenetre, &Pos_Dec);
	SDL_FreeSurface(connexion);
	SDL_FreeSurface(CreerCompte);
	SDL_FreeSurface(deconnexion);
	TTF_CloseFont(police2);

	switch(AccMed_App){
		case ESP_MEDACC_BOUT_1:
			if(ID_App != NO_ID){
				connecte(fenetre, &ID, ID_App, masqueur1, connected, confirmation, Med_Conn_Nom);
			}
			break;
		case ESP_MEDACC_BOUT_2:
			if(CC_App != ANN){
				Creation_Compte_Med(fenetre, ID, CC_App, masqueur1, masq_check, masqueur2, confirmation);
			}
			break;
		case DECONNECTE:
			if(*connected){
				strcpy(confirmation, "deconnecte");
			}
			*connected = 0;
		case NONE:
			break;
	}

	for(i=0; i<3; i++){	
		SDL_FreeSurface(messag[i]);
	}
	TTF_CloseFont(police);
}

int If_Repeat(char Dossier[50], int nombre_dispo, Rendez_Vous rv){
	int i;
	char le_dossier[50] = "", chiff[5] = "";
	Rendez_Vous myRv;
	FILE *fichier = NULL;
	for(i=0; i < nombre_dispo; i++){
		//strcpy(le_dossier, "");
		strcpy(le_dossier, Dossier);
		strcat(le_dossier, "/disponibilites/dispo");
		sprintf(chiff, "%d", i+1);
		strcat(le_dossier, chiff);
		strcat(le_dossier, ".bin");
		fichier = fopen(le_dossier, "rb");
		if(fichier == NULL){
			fclose(fichier);
			return 0;
		}else{
			fread(&myRv, sizeof(Rendez_Vous), 1, fichier);
			if(myRv.jours == rv.jours && myRv.mois == rv.mois && myRv.annee == rv.annee && myRv.heure == rv.heure && myRv.minutes==rv.minutes){
				fclose(fichier);
				return 1;
			}else{
				fclose(fichier);
			}
		}
	}
	return 0;
}

void Entrer_Dispo(SDL_Surface* fenetre, char dossier[50],Rendez_Vous Cr_Rv, Dispo_Creation DC_App, int *nombre_Dispo,
 char Dossier_En_Cours[50]){
	SDL_Surface* Surf_Fond = NULL, *legende = NULL, *text_leg = NULL;
	SDL_Surface *Surf_Jours = NULL, *Surf_Mois = NULL, *Surf_Annee = NULL;
	SDL_Rect Pos_JMA, Pos_Fond, Pos_leg;
	Pos_Fond.x = 400;
	Pos_Fond.y = 120;
	Surf_Fond = SDL_CreateRGBSurface(SDL_HWSURFACE, 400, 200, 32, 0, 0, 0, 0);
	SDL_FillRect(Surf_Fond, NULL, SDL_MapRGB(fenetre->format, 0, 255, 255));
	SDL_BlitSurface(Surf_Fond, NULL, fenetre, &Pos_Fond);
	SDL_FreeSurface(Surf_Fond);

	SDL_Surface *Surf_Heure = NULL, *Surf_Min = NULL;
	SDL_Rect Pos_HM;
	Surf_Jours = SDL_CreateRGBSurface(SDL_HWSURFACE, 50, 30, 32, 0, 0, 0, 0);
	Surf_Mois = SDL_CreateRGBSurface(SDL_HWSURFACE, 50, 30, 32, 0, 0, 0, 0);
	Surf_Annee = SDL_CreateRGBSurface(SDL_HWSURFACE, 50, 30, 32, 0, 0, 0, 0);
	Surf_Heure = SDL_CreateRGBSurface(SDL_HWSURFACE, 50, 30, 32, 0, 0, 0, 0);
	Surf_Min = SDL_CreateRGBSurface(SDL_HWSURFACE, 50, 30, 32, 0, 0, 0, 0);
	SDL_FillRect(Surf_Jours, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));
	SDL_FillRect(Surf_Mois, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));
	SDL_FillRect(Surf_Annee, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));
	SDL_FillRect(Surf_Heure, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));
	SDL_FillRect(Surf_Min, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));
	Pos_JMA.x = 460;
	Pos_JMA.y = 145;
	SDL_BlitSurface(Surf_Jours, NULL, fenetre, &Pos_JMA);
	Pos_JMA.y += 40;
	SDL_BlitSurface(Surf_Mois, NULL, fenetre, &Pos_JMA);
	Pos_JMA.y += 40;
	SDL_BlitSurface(Surf_Annee, NULL, fenetre, &Pos_JMA);
	Pos_HM.x = 700;
	Pos_HM.y = 145;
	SDL_BlitSurface(Surf_Heure, NULL, fenetre, &Pos_HM);
	Pos_HM.y += 40;
	SDL_BlitSurface(Surf_Min, NULL, fenetre, &Pos_HM);
	SDL_FreeSurface(Surf_Jours);
	SDL_FreeSurface(Surf_Mois);
	SDL_FreeSurface(Surf_Annee);
	SDL_FreeSurface(Surf_Heure);
	SDL_FreeSurface(Surf_Min);

	SDL_Surface* Legende[5] = {NULL};
	char* Mot_Leg[5] = {"jours", "mois", "annee", "heure", "minutes"};
	TTF_Font *police1 = TTF_OpenFont("polices/arial.ttf", 14);
	SDL_Rect Pos_Leg[5];
	int i;
	SDL_Color color1 = {0, 0, 0};
	for(i=0; i<5; i++){
		Legende[i] = TTF_RenderText_Blended(police1, Mot_Leg[i], color1);
		if(i==0){
			Pos_Leg[i].x = 400;
			Pos_Leg[i].y = 155;
		}else if(i==3){
			Pos_Leg[i].x = 650;
			Pos_Leg[i].y = 155;
		}else{
			Pos_Leg[i].x = Pos_Leg[i-1].x;
			Pos_Leg[i].y = Pos_Leg[i-1].y + 40;
		}
		SDL_BlitSurface(Legende[i], NULL, fenetre, &Pos_Leg[i]);
		SDL_FreeSurface(Legende[i]);
	}

	SDL_Surface *Bout_Valid = NULL, *Bout_Annule = NULL, *Leg_Valid = NULL;
	SDL_Rect Pos_Val, Pos_Ann;
	Pos_Val.x = 550;
	Pos_Val.y = 280;
	Bout_Valid = IMG_Load("images/valider.png");
	//SDL_FillRect(Bout_Valid, NULL, SDL_MapRGB(fenetre->format, 0, 255, 0));
	Bout_Annule = IMG_Load("images/tn_ferme.jpg");
	Pos_Ann.x = 780;
	Pos_Ann.y = 110;
	//Leg_Valid = TTF_RenderText_Blended(police1, "Valider", color1);
	Pos_leg.x = 400;
	Pos_leg.y = 110;
	legende = SDL_CreateRGBSurface(SDL_HWSURFACE, 400, 20, 32, 0, 0, 0, 0);
	SDL_FillRect(legende, NULL, SDL_MapRGB(fenetre->format, 0, 0, 255));
	text_leg = TTF_RenderText_Blended(police1, " Indiquez la date et l'heure ", color1);
	SDL_BlitSurface(legende, NULL, fenetre, &Pos_leg);
	Pos_leg.x += 100;
	SDL_BlitSurface(text_leg, NULL, fenetre, &Pos_leg);
	SDL_BlitSurface(Bout_Valid, NULL, fenetre, &Pos_Val);
	Pos_Val.y +=5;
	Pos_Val.x +=5;
	//SDL_BlitSurface(Leg_Valid, NULL, fenetre, &Pos_Val);
	SDL_BlitSurface(Bout_Annule, NULL, fenetre, &Pos_Ann);

	SDL_FreeSurface(legende);
	SDL_FreeSurface(text_leg);
	SDL_FreeSurface(Bout_Valid);
	SDL_FreeSurface(Leg_Valid);
	SDL_FreeSurface(Bout_Annule);

	SDL_Surface *Bout_Apres = NULL, *Bout_Avant = NULL;
	SDL_Rect Pos_Apres[5], Pos_Avant[5];
	Bout_Apres = IMG_Load("images/avant.png");
	Bout_Avant = IMG_Load("images/apres.png");
	for(i=0; i<5; i++){
		if(i==0){
			Pos_Apres[i].x = 510;
			Pos_Apres[i].y = 145;
		}else if(i == 3){
			Pos_Apres[i].x = 750;
			Pos_Apres[i].y = 145;
		}else{
			Pos_Apres[i].x = Pos_Apres[i-1].x;
			Pos_Apres[i].y = Pos_Apres[i-1].y + 40;
		}
		Pos_Avant[i].x = Pos_Apres[i].x;
		Pos_Avant[i].y = Pos_Apres[i].y + 20;
		SDL_BlitSurface(Bout_Apres, NULL, fenetre, &Pos_Apres[i]);
		SDL_BlitSurface(Bout_Avant, NULL, fenetre, &Pos_Avant[i]);
	}
	SDL_FreeSurface(Bout_Apres);
	SDL_FreeSurface(Bout_Avant);

	SDL_Surface *Saisi_Des_Rv[5] = {NULL};
	SDL_Rect Pos_Saisi_Des_Rv[5];
	for(i=0; i<5; i++){
		if(i==0){
			Pos_Saisi_Des_Rv[i].x = 460;
			Pos_Saisi_Des_Rv[i].y = 160;
		}else if(i==3){
			Pos_Saisi_Des_Rv[i].x = 700;
			Pos_Saisi_Des_Rv[i].y = 160;
		}else{
			Pos_Saisi_Des_Rv[i].x = Pos_Saisi_Des_Rv[i-1].x;
			Pos_Saisi_Des_Rv[i].y = Pos_Saisi_Des_Rv[i-1].y + 40;
		}
	}
	char curseur_jours[50] = "", curseur_mois[50] = "", curseur_annee[50] = "", curseur_heure[50] = "", curseur_minutes[50] = "";
	SDL_Color noire = {0, 0, 0};
	char le_dossier[50] = "", nbr_dispos[10] = "", fich_dispo[50] = "";
	SDL_Surface *alert = NULL;
	SDL_Rect Pos_alert;
	Pos_alert.x = 600;
	Pos_alert.y = 240;
	SDL_Color rouge = {255, 0, 0}, verte = {0, 255, 0};
	FILE *file = NULL, *fichier = NULL;
	int repeat = 1;
	strcpy(le_dossier, Dossier_En_Cours);
	strcat(le_dossier, "/disponibilites/dispo");
	strcpy(fich_dispo, Dossier_En_Cours);
	strcat(fich_dispo, "/nbrDispo.bin");
	switch(DC_App){
		case DC_JOURS:
			sprintf(curseur_jours, "%d", Cr_Rv.jours);
			sprintf(curseur_mois, "%d", Cr_Rv.mois);
			sprintf(curseur_annee, "%d", Cr_Rv.annee);
			sprintf(curseur_heure, "%d", Cr_Rv.heure);
			sprintf(curseur_minutes, "%d", Cr_Rv.minutes);
			strcat(curseur_jours, "|");
			Saisi_Des_Rv[0] = TTF_RenderText_Blended(police1, curseur_jours, noire);
			Saisi_Des_Rv[1] = TTF_RenderText_Blended(police1, curseur_mois, noire);
			Saisi_Des_Rv[2] = TTF_RenderText_Blended(police1, curseur_annee, noire);
			Saisi_Des_Rv[3] = TTF_RenderText_Blended(police1, curseur_heure, noire);
			Saisi_Des_Rv[4] = TTF_RenderText_Blended(police1, curseur_minutes, noire);
			break;
		case DC_APRES_1:
			sprintf(curseur_jours, "%d", Cr_Rv.jours);
			sprintf(curseur_mois, "%d", Cr_Rv.mois);
			sprintf(curseur_annee, "%d", Cr_Rv.annee);
			sprintf(curseur_heure, "%d", Cr_Rv.heure);
			sprintf(curseur_minutes, "%d", Cr_Rv.minutes);
			Saisi_Des_Rv[0] = TTF_RenderText_Blended(police1, curseur_jours, noire);
			Saisi_Des_Rv[1] = TTF_RenderText_Blended(police1, curseur_mois, noire);
			Saisi_Des_Rv[2] = TTF_RenderText_Blended(police1, curseur_annee, noire);
			Saisi_Des_Rv[3] = TTF_RenderText_Blended(police1, curseur_heure, noire);
			Saisi_Des_Rv[4] = TTF_RenderText_Blended(police1, curseur_minutes, noire);
			break;
		case DC_AVANT_1:
			sprintf(curseur_jours, "%d", Cr_Rv.jours);
			sprintf(curseur_mois, "%d", Cr_Rv.mois);
			sprintf(curseur_annee, "%d", Cr_Rv.annee);
			sprintf(curseur_heure, "%d", Cr_Rv.heure);
			sprintf(curseur_minutes, "%d", Cr_Rv.minutes);
			Saisi_Des_Rv[0] = TTF_RenderText_Blended(police1, curseur_jours, noire);
			Saisi_Des_Rv[1] = TTF_RenderText_Blended(police1, curseur_mois, noire);
			Saisi_Des_Rv[2] = TTF_RenderText_Blended(police1, curseur_annee, noire);
			Saisi_Des_Rv[3] = TTF_RenderText_Blended(police1, curseur_heure, noire);
			Saisi_Des_Rv[4] = TTF_RenderText_Blended(police1, curseur_minutes, noire);
			break;
		case DC_MOIS:
			sprintf(curseur_jours, "%d", Cr_Rv.jours);
			sprintf(curseur_mois, "%d", Cr_Rv.mois);
			sprintf(curseur_annee, "%d", Cr_Rv.annee);
			sprintf(curseur_heure, "%d", Cr_Rv.heure);
			sprintf(curseur_minutes, "%d", Cr_Rv.minutes);
			strcat(curseur_mois, "|");
			Saisi_Des_Rv[0] = TTF_RenderText_Blended(police1, curseur_jours, noire);
			Saisi_Des_Rv[1] = TTF_RenderText_Blended(police1, curseur_mois, noire);
			Saisi_Des_Rv[2] = TTF_RenderText_Blended(police1, curseur_annee, noire);
			Saisi_Des_Rv[3] = TTF_RenderText_Blended(police1, curseur_heure, noire);
			Saisi_Des_Rv[4] = TTF_RenderText_Blended(police1, curseur_minutes, noire);
			break;
		case DC_APRES_2:
			sprintf(curseur_jours, "%d", Cr_Rv.jours);
			sprintf(curseur_mois, "%d", Cr_Rv.mois);
			sprintf(curseur_annee, "%d", Cr_Rv.annee);
			sprintf(curseur_heure, "%d", Cr_Rv.heure);
			sprintf(curseur_minutes, "%d", Cr_Rv.minutes);
			Saisi_Des_Rv[0] = TTF_RenderText_Blended(police1, curseur_jours, noire);
			Saisi_Des_Rv[1] = TTF_RenderText_Blended(police1, curseur_mois, noire);
			Saisi_Des_Rv[2] = TTF_RenderText_Blended(police1, curseur_annee, noire);
			Saisi_Des_Rv[3] = TTF_RenderText_Blended(police1, curseur_heure, noire);
			Saisi_Des_Rv[4] = TTF_RenderText_Blended(police1, curseur_minutes, noire);
			break;
		case DC_AVANT_2:
			sprintf(curseur_jours, "%d", Cr_Rv.jours);
			sprintf(curseur_mois, "%d", Cr_Rv.mois);
			sprintf(curseur_annee, "%d", Cr_Rv.annee);
			sprintf(curseur_heure, "%d", Cr_Rv.heure);
			sprintf(curseur_minutes, "%d", Cr_Rv.minutes);
			Saisi_Des_Rv[0] = TTF_RenderText_Blended(police1, curseur_jours, noire);
			Saisi_Des_Rv[1] = TTF_RenderText_Blended(police1, curseur_mois, noire);
			Saisi_Des_Rv[2] = TTF_RenderText_Blended(police1, curseur_annee, noire);
			Saisi_Des_Rv[3] = TTF_RenderText_Blended(police1, curseur_heure, noire);
			Saisi_Des_Rv[4] = TTF_RenderText_Blended(police1, curseur_minutes, noire);
			break;
		case DC_ANNEE:
			sprintf(curseur_jours, "%d", Cr_Rv.jours);
			sprintf(curseur_mois, "%d", Cr_Rv.mois);
			sprintf(curseur_annee, "%d", Cr_Rv.annee);
			sprintf(curseur_heure, "%d", Cr_Rv.heure);
			sprintf(curseur_minutes, "%d", Cr_Rv.minutes);
			strcat(curseur_annee, "|");
			Saisi_Des_Rv[0] = TTF_RenderText_Blended(police1, curseur_jours, noire);
			Saisi_Des_Rv[1] = TTF_RenderText_Blended(police1, curseur_mois, noire);
			Saisi_Des_Rv[2] = TTF_RenderText_Blended(police1, curseur_annee, noire);
			Saisi_Des_Rv[3] = TTF_RenderText_Blended(police1, curseur_heure, noire);
			Saisi_Des_Rv[4] = TTF_RenderText_Blended(police1, curseur_minutes, noire);
			break;
		case DC_APRES_3:
			sprintf(curseur_jours, "%d", Cr_Rv.jours);
			sprintf(curseur_mois, "%d", Cr_Rv.mois);
			sprintf(curseur_annee, "%d", Cr_Rv.annee);
			sprintf(curseur_heure, "%d", Cr_Rv.heure);
			sprintf(curseur_minutes, "%d", Cr_Rv.minutes);
			Saisi_Des_Rv[0] = TTF_RenderText_Blended(police1, curseur_jours, noire);
			Saisi_Des_Rv[1] = TTF_RenderText_Blended(police1, curseur_mois, noire);
			Saisi_Des_Rv[2] = TTF_RenderText_Blended(police1, curseur_annee, noire);
			Saisi_Des_Rv[3] = TTF_RenderText_Blended(police1, curseur_heure, noire);
			Saisi_Des_Rv[4] = TTF_RenderText_Blended(police1, curseur_minutes, noire);
			break;
		case DC_AVANT_3:
			sprintf(curseur_jours, "%d", Cr_Rv.jours);
			sprintf(curseur_mois, "%d", Cr_Rv.mois);
			sprintf(curseur_annee, "%d", Cr_Rv.annee);
			sprintf(curseur_heure, "%d", Cr_Rv.heure);
			sprintf(curseur_minutes, "%d", Cr_Rv.minutes);
			Saisi_Des_Rv[0] = TTF_RenderText_Blended(police1, curseur_jours, noire);
			Saisi_Des_Rv[1] = TTF_RenderText_Blended(police1, curseur_mois, noire);
			Saisi_Des_Rv[2] = TTF_RenderText_Blended(police1, curseur_annee, noire);
			Saisi_Des_Rv[3] = TTF_RenderText_Blended(police1, curseur_heure, noire);
			Saisi_Des_Rv[4] = TTF_RenderText_Blended(police1, curseur_minutes, noire);
			break;
		case DC_HEURE:
			sprintf(curseur_jours, "%d", Cr_Rv.jours);
			sprintf(curseur_mois, "%d", Cr_Rv.mois);
			sprintf(curseur_annee, "%d", Cr_Rv.annee);
			sprintf(curseur_heure, "%d", Cr_Rv.heure);
			sprintf(curseur_minutes, "%d", Cr_Rv.minutes);
			strcat(curseur_heure, "|");
			Saisi_Des_Rv[0] = TTF_RenderText_Blended(police1, curseur_jours, noire);
			Saisi_Des_Rv[1] = TTF_RenderText_Blended(police1, curseur_mois, noire);
			Saisi_Des_Rv[2] = TTF_RenderText_Blended(police1, curseur_annee, noire);
			Saisi_Des_Rv[3] = TTF_RenderText_Blended(police1, curseur_heure, noire);
			Saisi_Des_Rv[4] = TTF_RenderText_Blended(police1, curseur_minutes, noire);
			break;
		case DC_APRES_4:
			sprintf(curseur_jours, "%d", Cr_Rv.jours);
			sprintf(curseur_mois, "%d", Cr_Rv.mois);
			sprintf(curseur_annee, "%d", Cr_Rv.annee);
			sprintf(curseur_heure, "%d", Cr_Rv.heure);
			sprintf(curseur_minutes, "%d", Cr_Rv.minutes);
			Saisi_Des_Rv[0] = TTF_RenderText_Blended(police1, curseur_jours, noire);
			Saisi_Des_Rv[1] = TTF_RenderText_Blended(police1, curseur_mois, noire);
			Saisi_Des_Rv[2] = TTF_RenderText_Blended(police1, curseur_annee, noire);
			Saisi_Des_Rv[3] = TTF_RenderText_Blended(police1, curseur_heure, noire);
			Saisi_Des_Rv[4] = TTF_RenderText_Blended(police1, curseur_minutes, noire);
			break;
		case DC_AVANT_4:
			sprintf(curseur_jours, "%d", Cr_Rv.jours);
			sprintf(curseur_mois, "%d", Cr_Rv.mois);
			sprintf(curseur_annee, "%d", Cr_Rv.annee);
			sprintf(curseur_heure, "%d", Cr_Rv.heure);
			sprintf(curseur_minutes, "%d", Cr_Rv.minutes);
			Saisi_Des_Rv[0] = TTF_RenderText_Blended(police1, curseur_jours, noire);
			Saisi_Des_Rv[1] = TTF_RenderText_Blended(police1, curseur_mois, noire);
			Saisi_Des_Rv[2] = TTF_RenderText_Blended(police1, curseur_annee, noire);
			Saisi_Des_Rv[3] = TTF_RenderText_Blended(police1, curseur_heure, noire);
			Saisi_Des_Rv[4] = TTF_RenderText_Blended(police1, curseur_minutes, noire);
			break;
		case DC_MINUTE:
			sprintf(curseur_jours, "%d", Cr_Rv.jours);
			sprintf(curseur_mois, "%d", Cr_Rv.mois);
			sprintf(curseur_annee, "%d", Cr_Rv.annee);
			sprintf(curseur_heure, "%d", Cr_Rv.heure);
			sprintf(curseur_minutes, "%d", Cr_Rv.minutes);
			strcat(curseur_minutes, "|");
			Saisi_Des_Rv[0] = TTF_RenderText_Blended(police1, curseur_jours, noire);
			Saisi_Des_Rv[1] = TTF_RenderText_Blended(police1, curseur_mois, noire);
			Saisi_Des_Rv[2] = TTF_RenderText_Blended(police1, curseur_annee, noire);
			Saisi_Des_Rv[3] = TTF_RenderText_Blended(police1, curseur_heure, noire);
			Saisi_Des_Rv[4] = TTF_RenderText_Blended(police1, curseur_minutes, noire);
			break;
		case DC_APRES_5:
			sprintf(curseur_jours, "%d", Cr_Rv.jours);
			sprintf(curseur_mois, "%d", Cr_Rv.mois);
			sprintf(curseur_annee, "%d", Cr_Rv.annee);
			sprintf(curseur_heure, "%d", Cr_Rv.heure);
			sprintf(curseur_minutes, "%d", Cr_Rv.minutes);
			Saisi_Des_Rv[0] = TTF_RenderText_Blended(police1, curseur_jours, noire);
			Saisi_Des_Rv[1] = TTF_RenderText_Blended(police1, curseur_mois, noire);
			Saisi_Des_Rv[2] = TTF_RenderText_Blended(police1, curseur_annee, noire);
			Saisi_Des_Rv[3] = TTF_RenderText_Blended(police1, curseur_heure, noire);
			Saisi_Des_Rv[4] = TTF_RenderText_Blended(police1, curseur_minutes, noire);
			break;
		case DC_AVANT_5:
			sprintf(curseur_jours, "%d", Cr_Rv.jours);
			sprintf(curseur_mois, "%d", Cr_Rv.mois);
			sprintf(curseur_annee, "%d", Cr_Rv.annee);
			sprintf(curseur_heure, "%d", Cr_Rv.heure);
			sprintf(curseur_minutes, "%d", Cr_Rv.minutes);
			Saisi_Des_Rv[0] = TTF_RenderText_Blended(police1, curseur_jours, noire);
			Saisi_Des_Rv[1] = TTF_RenderText_Blended(police1, curseur_mois, noire);
			Saisi_Des_Rv[2] = TTF_RenderText_Blended(police1, curseur_annee, noire);
			Saisi_Des_Rv[3] = TTF_RenderText_Blended(police1, curseur_heure, noire);
			Saisi_Des_Rv[4] = TTF_RenderText_Blended(police1, curseur_minutes, noire);
			break;
		case DC_VALIDE:
			repeat = If_Repeat(Dossier_En_Cours, *nombre_Dispo, Cr_Rv);
			if(repeat == 0){
				*nombre_Dispo += 1;
				fichier = fopen(fich_dispo ,"wb");
				fwrite(nombre_Dispo, sizeof(int), 1, fichier);
				fclose(fichier);
				sprintf(nbr_dispos, "%d", *nombre_Dispo);
				strcat(nbr_dispos, ".bin");
				strcat(le_dossier, nbr_dispos);
				file = fopen(le_dossier, "wb");
				fwrite(&Cr_Rv, sizeof(Rendez_Vous), 1, file);
				fclose(file);
				alert = TTF_RenderText_Blended(police1, "Cree avec succes", verte);
			}else{
				alert = TTF_RenderText_Blended(police1, "Deja existante", rouge);
			}
			SDL_BlitSurface(alert, NULL, fenetre, &Pos_alert);
			break;
		case DC_RIEN:
			sprintf(curseur_jours, "%d", Cr_Rv.jours);
			sprintf(curseur_mois, "%d", Cr_Rv.mois);
			sprintf(curseur_annee, "%d", Cr_Rv.annee);
			sprintf(curseur_heure, "%d", Cr_Rv.heure);
			sprintf(curseur_minutes, "%d", Cr_Rv.minutes);
			Saisi_Des_Rv[0] = TTF_RenderText_Blended(police1, curseur_jours, noire);
			Saisi_Des_Rv[1] = TTF_RenderText_Blended(police1, curseur_mois, noire);
			Saisi_Des_Rv[2] = TTF_RenderText_Blended(police1, curseur_annee, noire);
			Saisi_Des_Rv[3] = TTF_RenderText_Blended(police1, curseur_heure, noire);
			Saisi_Des_Rv[4] = TTF_RenderText_Blended(police1, curseur_minutes, noire);
			break;
	}
	for(i=0; i<5; i++){
		SDL_BlitSurface(Saisi_Des_Rv[i], NULL, fenetre, &Pos_Saisi_Des_Rv[i]);
		SDL_FreeSurface(Saisi_Des_Rv[i]);
	}
	SDL_FreeSurface(alert);
	SDL_Delay(200);
	TTF_CloseFont(police1);
}

void BlitDispo(SDL_Surface* fenetre, char Dossier[50], int nombre_Dispo){
	char le_dossier[50] = "", Point_bin[20] = "", date[25] = "", hour[25] = "";
	Rendez_Vous rv;
	int i;
	FILE *fichier = NULL;
	SDL_Surface **Dispo_Surface =  {NULL}, *Surf_Date = NULL, *Surf_hour = NULL, *verticale = NULL, *horizontale = NULL,
	*Pas_Dispo = NULL;
	SDL_Rect *Position, Pos_No_Dispo;
	Pos_No_Dispo.x = 530;
	Pos_No_Dispo.y = 400;
	SDL_Color red = {125, 0, 0};
	TTF_Font *police = TTF_OpenFont("polices/arial.ttf", 12);
	TTF_SetFontStyle(police, TTF_STYLE_ITALIC);
	Dispo_Surface = malloc(sizeof(SDL_Surface)*nombre_Dispo);
	Position = malloc(sizeof(SDL_Rect)*nombre_Dispo);
	SDL_Color noir = {0, 0, 0};
	verticale = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 50, 32, 0, 0, 0, 0);
	horizontale = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 1, 32, 0, 0, 0, 0);
	TTF_Font *police1 = TTF_OpenFont("polices/police.TTF", 30);
	TTF_SetFontStyle(police1, TTF_STYLE_ITALIC);
	if(nombre_Dispo == 0){
		Pas_Dispo = TTF_RenderText_Blended(police1, "Aucune", red);
		SDL_BlitSurface(Pas_Dispo, NULL, fenetre, &Pos_No_Dispo);
		return;
	}
	TTF_CloseFont(police1);
	for(i=0; i<nombre_Dispo; i++){
		strcpy(le_dossier, "");
		strcpy(date, "");
		strcpy(hour, "");
		strcpy(le_dossier, Dossier);
		strcat(le_dossier, "/disponibilites/dispo");
		sprintf(Point_bin, "%d", i+1);
		strcat(Point_bin, ".bin");
		strcat(le_dossier, Point_bin);
		if(i==0){
			Position[i].x = 300;
			Position[i].y = 150;
		}else if(i==5 || i==10 || i==15 || i==20){
			Position[i].x = Position[0].x;
			if(i==5){
				Position[i].y = Position[0].y + 51;
			}else if(i==10)
				Position[i].y = Position[0].y + 2*51;
			else if(i==15)
				Position[i].y = Position[0].y + 51*3;
			else
				Position[i].y = Position[0].y + 51*4;
		}else{
			Position[i].x = Position[i-1].x + 100 + 1;
			Position[i].y = Position[i-1].y;
		}
		Dispo_Surface[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 50, 32, 0, 0, 0, 0);
		SDL_FillRect(Dispo_Surface[i], NULL, SDL_MapRGB(fenetre->format, 250, 250, 250));
		SDL_SetColorKey(Dispo_Surface[i], SDL_SRCCOLORKEY, SDL_MapRGB(fenetre->format, 250, 250, 250));
		fichier = fopen(le_dossier, "rb");
		if(fichier != NULL){
			fread(&rv, sizeof(Rendez_Vous), 1, fichier);
			fclose(fichier);
			sprintf(date, "Le %d/%d/%d", rv.jours, rv.mois, rv.annee);
			sprintf(hour, " a %dh %dmin", rv.heure, rv.minutes);
			Surf_Date = TTF_RenderText_Blended(police, date, noir);
			Surf_hour = TTF_RenderText_Blended(police, hour, noir);
			SDL_BlitSurface(Dispo_Surface[i], NULL, fenetre, &Position[i]);
			Position[i].x += 10;
			Position[i].y += 10;
			SDL_BlitSurface(Surf_Date, NULL, fenetre, &Position[i]);
			Position[i].x +=5;
			Position[i].y += 15;
			SDL_BlitSurface(Surf_hour, NULL, fenetre, &Position[i]);
			Position[i].x -= 15;
			Position[i].y -= 25;
			SDL_BlitSurface(verticale, NULL, fenetre, &Position[i]);
			Position[i].y += 50;
			SDL_BlitSurface(horizontale, NULL, fenetre, &Position[i]);
		}else{
			fclose(fichier);
			break;
		}
		Position[i].y -= 50;
		SDL_FreeSurface(Surf_Date);
		SDL_FreeSurface(Surf_hour);
	}
	for(i=0; i<nombre_Dispo; i++){
		SDL_FreeSurface(Dispo_Surface[i]);
	}
	SDL_FreeSurface(Pas_Dispo);
	SDL_FreeSurface(verticale);
	SDL_FreeSurface(horizontale);
	TTF_CloseFont(police);
	free(Dispo_Surface);
	free(Position);
}

void Affichier_Details(SDL_Surface* fenetre, int *Nbr_Dispo, char dossier[50], int Numero){
	char Dossier[50] = "", chiffre[5] = "";
	strcpy(Dossier, dossier);
	strcat(Dossier, "/disponibilites/dispo");
	sprintf(chiffre, "%d", Numero);
	strcat(Dossier, chiffre);
	strcat(Dossier, ".bin");

	Rendez_Vous rv;
	FILE* fichier = fopen(Dossier, "rb");
	if(fichier != NULL){
		fread(&rv, sizeof(Rendez_Vous), 1, fichier);
	}
	fclose(fichier);

	SDL_Surface *Surface = NULL, *Jours = NULL, *Mois = NULL, *Annee  = NULL, *Heure = NULL, *Minutes = NULL;
	SDL_Rect Pos_Surface, Pos_Date;
	char day[50] = "", month[50] = "", year[50] = "", hour[50] = "", minute[50] = "";
	Pos_Surface.x = 520;Pos_Surface.y = 150;
	Surface = SDL_CreateRGBSurface(SDL_HWSURFACE, 150, 300, 32, 0, 0, 0, 0);
	SDL_FillRect(Surface, NULL, SDL_MapRGB(fenetre->format, 0, 183, 183));
	SDL_BlitSurface(Surface, NULL, fenetre, &Pos_Surface);
	TTF_Font *police = TTF_OpenFont("polices/arial.ttf", 14);
	SDL_Color Noir = {0, 0, 0};
	sprintf(day, "Jours : le %d", rv.jours);
	sprintf(month, "Mois : %d", rv.mois);
	sprintf(year, "Annee : %d", rv.annee);
	sprintf(hour, "Heure : %d", rv.heure);
	sprintf(minute, "Minutes : %d", rv.minutes);
	Jours = TTF_RenderText_Blended(police, day, Noir);
	Mois = TTF_RenderText_Blended(police, month, Noir);
	Annee = TTF_RenderText_Blended(police, year, Noir);
	Heure = TTF_RenderText_Blended(police, hour, Noir);
	Minutes = TTF_RenderText_Blended(police, minute, Noir);
	Pos_Date.x =  530;Pos_Date.y = 170;
	SDL_BlitSurface(Jours, NULL, fenetre, &Pos_Date);
	Pos_Date.y += 50;
	SDL_BlitSurface(Mois, NULL, fenetre, &Pos_Date);
	Pos_Date.y += 50;
	SDL_BlitSurface(Annee, NULL, fenetre, &Pos_Date);
	Pos_Date.y += 50;
	SDL_BlitSurface(Heure, NULL, fenetre, &Pos_Date);
	Pos_Date.y += 50;
	SDL_BlitSurface(Minutes, NULL, fenetre, &Pos_Date);
	SDL_FreeSurface(Jours);
	SDL_FreeSurface(Mois);
	SDL_FreeSurface(Annee);
	SDL_FreeSurface(Heure);
	SDL_FreeSurface(Minutes);
	SDL_FreeSurface(Surface);
	TTF_CloseFont(police);
}

void Mes_Dispo(SDL_Surface* fenetre, Bout_MesDispo Surv_MesDispo, Bout_MesDispo App_MesDispo, Dispo_Creation DC_App, char dossier[50],
	Rendez_Vous Cr_Rv, int *nombre_Dispo, Clic_Droit clic_droit, SDL_Rect Pos_Clic_Droit){
	SDL_Surface *background = NULL;
	SDL_Rect Pos_Bg;
	Pos_Bg.x = 400;
	Pos_Bg.y = 200;
	background = IMG_Load("images/tn_logoclinique.jpg");
	SDL_BlitSurface(background, NULL, fenetre, &Pos_Bg);
	Pos_Bg.x += 200;
	SDL_BlitSurface(background, NULL, fenetre, &Pos_Bg);
	SDL_FreeSurface(background);

	SDL_Surface *Bout_New_Dispo = NULL, *Text_New_Dispo = NULL;
	SDL_Rect Pos_Bout_ND;
	Pos_Bout_ND.x  = 500;
	Pos_Bout_ND.y = 90;
	TTF_Font* police = TTF_OpenFont("polices/police.TTF", 14);
	SDL_Color color1 = {154, 154, 154}, color2 = {49, 49, 49}, noir = {0, 0, 0};


	SDL_Surface *Surf_Modifier = NULL, *Surf_Supprimer = NULL, *Surf_Details = NULL, *Modifier = NULL, *Supprimer = NULL,
	*Details = NULL;
	SDL_Rect Pos_MSD;
	TTF_Font *myarial = TTF_OpenFont("polices/arial.ttf", 11);

	Surf_Modifier = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 30, 32, 0, 0, 0, 0);
	SDL_FillRect(Surf_Modifier, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));
	Surf_Supprimer = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 30, 32, 0, 0, 0, 0);
	SDL_FillRect(Surf_Supprimer, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));
	Surf_Details = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 30, 32, 0, 0, 0, 0);
	SDL_FillRect(Surf_Details, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));

	Modifier = TTF_RenderText_Blended(myarial, "Modifier", noir);
	Supprimer = TTF_RenderText_Blended(myarial, "Supprimer", noir);
	Details = TTF_RenderText_Blended(myarial, "Details", noir);

	switch(Surv_MesDispo){
		case NEW_DISPO:
			Bout_New_Dispo = IMG_Load("images/Nouvelle.png");
			Text_New_Dispo = TTF_RenderText_Blended(police, "Nouvelle Disponibilite", color2);
			break;
		case EDIT_DISPO:
			SDL_FillRect(Surf_Modifier, NULL, SDL_MapRGB(fenetre->format, 0, 255, 0));
			Bout_New_Dispo = IMG_Load("images/New.png");
			Text_New_Dispo = TTF_RenderText_Blended(police, "Nouvelle Disponibilite", color1);
			break;
		case DELETE_DISPO:
			SDL_FillRect(Surf_Supprimer, NULL, SDL_MapRGB(fenetre->format, 0, 255, 0));
			Bout_New_Dispo = IMG_Load("images/New.png");
			Text_New_Dispo = TTF_RenderText_Blended(police, "Nouvelle Disponibilite", color1);
			break;
		case DISPO_DETAIL:
			SDL_FillRect(Surf_Details, NULL, SDL_MapRGB(fenetre->format, 0, 255, 0));
			Bout_New_Dispo = IMG_Load("images/New.png");
			Text_New_Dispo = TTF_RenderText_Blended(police, "Nouvelle Disponibilite", color1);
			break;
		default:
			Bout_New_Dispo = IMG_Load("images/New.png");
			Text_New_Dispo = TTF_RenderText_Blended(police, "Nouvelle Disponibilite", color1);
			break;
	}


	switch(clic_droit){
		case ZONE_DISPO:
			Pos_MSD.x = Pos_Clic_Droit.x;
			Pos_MSD.y = Pos_Clic_Droit.y;
			SDL_BlitSurface(Surf_Modifier, NULL, fenetre, &Pos_MSD);
			Pos_MSD.y += 15;
			SDL_BlitSurface(Modifier, NULL, fenetre, &Pos_MSD);
			Pos_MSD.y += 15;
			SDL_BlitSurface(Surf_Supprimer, NULL, fenetre, &Pos_MSD);
			Pos_MSD.y += 15;
			SDL_BlitSurface(Supprimer, NULL, fenetre, &Pos_MSD);
			Pos_MSD.y += 15;
			SDL_BlitSurface(Surf_Details, NULL, fenetre, &Pos_MSD);
			Pos_MSD.y += 15;
			SDL_BlitSurface(Details, NULL, fenetre, &Pos_MSD);
			break;
		default :
			break;
	}

	SDL_BlitSurface(Bout_New_Dispo, NULL, fenetre, &Pos_Bout_ND);
	Pos_Bout_ND.x = 550;
	Pos_Bout_ND.y = 110;
	SDL_BlitSurface(Text_New_Dispo, NULL, fenetre, &Pos_Bout_ND);
	SDL_FreeSurface(Bout_New_Dispo);
	SDL_FreeSurface(Text_New_Dispo);

	SDL_FreeSurface(Surf_Modifier);
	SDL_FreeSurface(Surf_Supprimer);
	SDL_FreeSurface(Surf_Details);
	SDL_FreeSurface(Modifier);
	SDL_FreeSurface(Supprimer);
	SDL_FreeSurface(Details);
	TTF_CloseFont(myarial);

	int Dispo_Numero = 0, i, j = 1, I = -1;
	for(i=1; i <= *nombre_Dispo; i++){
		if(i == 6 || i == 11 || i == 17){
			I = 0;
		}else{
			I++;
		}

		if( i <= 5 && Pos_Clic_Droit.x > (I+3)*100 && Pos_Clic_Droit.x < (I+4)*100 && Pos_Clic_Droit.y > 150 && Pos_Clic_Droit.y < 200){
			Dispo_Numero = i;
			break;
		}else if( i <= 10 && Pos_Clic_Droit.x > (I+3)*100 && Pos_Clic_Droit.x < (I+4)*100 && Pos_Clic_Droit.y > 200 && Pos_Clic_Droit.y < 250){
			Dispo_Numero = i;
			break;
		}else if( i <= 15 && Pos_Clic_Droit.x > (I+3)*100 && Pos_Clic_Droit.x < (I+4)*100 && Pos_Clic_Droit.y > 250 && Pos_Clic_Droit.y < 300){
			Dispo_Numero = i;
			break;
		}else if(i <= 15 && Pos_Clic_Droit.x > (I+3)*100 && Pos_Clic_Droit.x < (I+4)*100 && Pos_Clic_Droit.y > 300 && Pos_Clic_Droit.y < 350){
			Dispo_Numero = i;
			break;
		}

	}

	BlitDispo(fenetre, dossier, *nombre_Dispo);

	switch(App_MesDispo){
		case NEW_DISPO:
			if(DC_App != DC_QUIT){
				Entrer_Dispo(fenetre, dossier, Cr_Rv, DC_App, nombre_Dispo, dossier);
			}
			break;
		case EDIT_DISPO:
			break;
		case DELETE_DISPO:
			break;
		case DISPO_DETAIL:
			Affichier_Details(fenetre, nombre_Dispo, dossier, Dispo_Numero);
			break;
		default:
			break;
	}

}

int Compteur_RvJours(char Dossier[50], int nombre_rv){
	char dossier[50] = "", chiff[5] = "";
	Patient p;
	int i, j, m, a, compteur = 0;
	FILE* fichier = NULL;
	time_t my_time;
	time(&my_time);
	struct tm *currenttime = localtime(&my_time);
	j = currenttime->tm_mday;
	m = currenttime->tm_mon + 1;
	a = currenttime->tm_year + 1900;
	for(i=0; i<nombre_rv; i++){
		strcpy(dossier, Dossier);
		strcat(dossier, "/RendezVous/rv");
		sprintf(chiff, "%d", i+1);
		strcat(dossier, chiff);
		strcat(dossier, ".bin");
		fichier = fopen(dossier, "rb");
		if(fichier != NULL){
			fread(&p, sizeof(Patient), 1, fichier);
			fclose(fichier);
			if(p.rv.jours == j && p.rv.mois == m && p.rv.annee == a)
				compteur++;
		}
	}

	return compteur;
}

void BlitRv(SDL_Surface* fenetre, int Nbr_Rv, char Dossier[50]){
	int Nbr_Rv_Jours = 0, autres = 0;
	Nbr_Rv_Jours = Compteur_RvJours(Dossier, Nbr_Rv);
	autres = Nbr_Rv - Nbr_Rv_Jours;

	int i, l, q;
	//jours_j
	SDL_Surface **RvJ_Surface = {NULL}, **Rv_Surface = {NULL}, *Date_Surf = NULL, *Hour_Surf = NULL, *Verticale = NULL, *Horizontale = NULL, *Pas_Rv = NULL,
	*Pas_Rv_Jours = NULL;
	SDL_Rect *Position_Jours, Pos_No_RvJours, *Position;
	Pos_No_RvJours.x = 520;Pos_No_RvJours.y = 280;
	RvJ_Surface = malloc(sizeof(SDL_Surface)*Nbr_Rv_Jours);
	Position_Jours = malloc(sizeof(SDL_Rect)*Nbr_Rv_Jours);
	Rv_Surface = malloc(sizeof(SDL_Surface)*autres);
	Position = malloc(sizeof(SDL_Rect)*autres);
	SDL_Color noir = {0, 0, 0};
	SDL_Color red = {125, 0, 0};
	Verticale = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 50, 32, 0, 0, 0, 0);
	Horizontale = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 1, 32, 0, 0, 0, 0);
	TTF_Font *arial = TTF_OpenFont("polices/arial.ttf", 12);
	TTF_SetFontStyle(arial, TTF_STYLE_ITALIC);
	char dossier[50] = "", chiffre[5] = "", date[25] = "", hour[25] = "";
	FILE *fichier = NULL;
	Patient p;
	TTF_Font *police = TTF_OpenFont("polices/police.TTF", 20);
	TTF_SetFontStyle(police, TTF_STYLE_ITALIC | TTF_STYLE_BOLD | TTF_STYLE_UNDERLINE);
	if(Nbr_Rv == 0){
		Pas_Rv = TTF_RenderText_Blended(police, "AUCUN", red);
		SDL_BlitSurface(Pas_Rv, NULL, fenetre, &Pos_No_RvJours);
		SDL_FreeSurface(Pas_Rv);
		return;
	}
	time_t currenttime;
	time(&currenttime);
	struct tm *mytime = localtime(&currenttime);
	int j, m, a, k = 0, n = 0;
	j = mytime->tm_mday;
	m = mytime->tm_mon + 1;
	a = mytime->tm_year + 1900;
	for(i=0; i < Nbr_Rv; i++){
		strcpy(dossier, "");
		strcpy(date, "");
		strcpy(hour, "");
		strcpy(dossier, Dossier);
		strcat(dossier, "/RendezVous/rv");
		sprintf(chiffre, "%d", i+1);
		strcat(dossier, chiffre);
		strcat(dossier, ".bin");
		fichier = fopen(dossier, "rb");
		if(fichier != NULL){
			fread(&p, sizeof(Patient), 1, fichier);
			fclose(fichier);
			if(p.rv.jours == j && p.rv.mois == m && p.rv.annee == a){
				//les coordonees de blittage
				for(l=0; l < Nbr_Rv_Jours; l++){
					if(l==0){
						Position_Jours[l].x = 300;
						Position_Jours[l].y = 120;
					}else if(l == 6 || l == 12 || l == 18){
						Position_Jours[l].x = Position_Jours[0].x;
						if(l == 6){
							Position_Jours[l].y = Position_Jours[0].y + 51;
						}else if(l==12){
							Position_Jours[l].y = Position_Jours[0].y + 2*51;
						}else if(l==18)
							Position_Jours[l].y = Position_Jours[0].y + 3*51;
					}else{
						Position_Jours[l].x = Position_Jours[l-1].x + 100 +1;
						Position_Jours[l].y = Position_Jours[l-1].y;
					}
				}
				RvJ_Surface[k] = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 50, 32, 0, 0, 0, 0);
				SDL_FillRect(RvJ_Surface[k], NULL, SDL_MapRGB(fenetre->format, 0, 255, 0));
				sprintf(date, "Le %d/%d/%d", p.rv.jours, p.rv.mois, p.rv.annee);
				sprintf(hour, "a %dh %dmin %d", p.rv.heure, p.rv.minutes, i+1);
				Date_Surf = TTF_RenderText_Blended(arial, date, noir);
				Hour_Surf = TTF_RenderText_Blended(arial, hour, noir);
				SDL_BlitSurface(RvJ_Surface[k], NULL, fenetre, &Position_Jours[k]);
				Position_Jours[k].x += 10;
				Position_Jours[k].y += 10;
				SDL_BlitSurface(Date_Surf, NULL, fenetre, &Position_Jours[k]);
				Position_Jours[k].x +=5;
				Position_Jours[k].y += 15;
				SDL_BlitSurface(Hour_Surf, NULL, fenetre, &Position_Jours[k]);
				Position_Jours[k].x -= 15;
				Position_Jours[k].y -= 25;
				SDL_BlitSurface(Verticale, NULL, fenetre, &Position_Jours[k]);
				Position_Jours[k].y += 50;
				SDL_BlitSurface(Horizontale, NULL, fenetre, &Position_Jours[k]);
				k++;
			}else{
				//les coordonnees
				for(q = 0; q < autres; q++){
					if(q==0){
						Position[q].x = 300;
						Position[q].y = 320;
					}else if(q == 6 || q == 12 || q == 18){
						Position[q].x = Position[0].x;
						if(q == 6){
							Position[q].y = Position[0].y + 51;
						}else if(q==12){
							Position[q].y = Position[0].y + 2*51;
						}else if(q==18)
							Position[q].y = Position[0].y + 3*51;
					}else{
						Position[q].x = Position[q-1].x + 100 +1;
						Position[q].y = Position[q-1].y;
					}	
				}
				Rv_Surface[n] = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 50, 32, 0, 0, 0, 0);
				SDL_FillRect(Rv_Surface[n], NULL, SDL_MapRGB(fenetre->format, 154, 159, 228));
				sprintf(date, "Le %d/%d/%d", p.rv.jours, p.rv.mois, p.rv.annee);
				sprintf(hour, "a %dh %dmin", p.rv.heure, p.rv.minutes);
				Date_Surf = TTF_RenderText_Blended(arial, date, noir);
				Hour_Surf = TTF_RenderText_Blended(arial, hour, noir);
				SDL_BlitSurface(Rv_Surface[n], NULL, fenetre, &Position[n]);
				Position[n].x += 10;
				Position[n].y += 10;
				SDL_BlitSurface(Date_Surf, NULL, fenetre, &Position[n]);
				Position[n].x +=5;
				Position[n].y += 15;
				SDL_BlitSurface(Hour_Surf, NULL, fenetre, &Position[n]);
				Position[n].x -= 15;
				Position[n].y -= 25;
				SDL_BlitSurface(Verticale, NULL, fenetre, &Position[n]);
				Position[n].y += 50;
				SDL_BlitSurface(Horizontale, NULL, fenetre, &Position[n]);
				n++;
			}
		}else{
			fclose(fichier);
		}
		SDL_FreeSurface(Date_Surf);
		SDL_FreeSurface(Hour_Surf);
	}
	for(i=0; i < Nbr_Rv_Jours; i++){
		SDL_FreeSurface(RvJ_Surface[i]);
	}
	SDL_FreeSurface(Verticale);
	SDL_FreeSurface(Horizontale);
	TTF_CloseFont(arial);
	TTF_CloseFont(police);
	free(RvJ_Surface);
	free(Position_Jours);
}

void Mes_Rv(SDL_Surface* fenetre, int Nbr_Rv, char Dossier[50]){
	SDL_Surface *background = NULL;
	SDL_Rect Pos_Bg;
	Pos_Bg.x = 400;
	Pos_Bg.y = 200;
	background = IMG_Load("images/tn_logoclinique.jpg");
	SDL_BlitSurface(background, NULL, fenetre, &Pos_Bg);
	Pos_Bg.x += 200;
	SDL_BlitSurface(background, NULL, fenetre, &Pos_Bg);
	SDL_FreeSurface(background);

	SDL_Surface *Rv_Jours = NULL, *TRV_Jours = NULL, *Autres_Rv = NULL;
	SDL_Rect Pos_RVJ;
	TTF_Font* police1 = TTF_OpenFont("polices/police.TTF", 14);
	TTF_SetFontStyle(police1, TTF_STYLE_UNDERLINE|TTF_STYLE_BOLD);
	SDL_Color color1 = {0, 0, 0};
	Pos_RVJ.x = 300;
	Pos_RVJ.y = 100;
	Rv_Jours = SDL_CreateRGBSurface(SDL_HWSURFACE, 610, 180, 32, 0, 0, 0, 0);
	Autres_Rv = SDL_CreateRGBSurface(SDL_HWSURFACE, 610, 200, 32, 0, 0, 0, 0);
	SDL_FillRect(Rv_Jours, NULL, SDL_MapRGB(fenetre->format, 158, 203, 55));
	SDL_FillRect(Autres_Rv, NULL, SDL_MapRGB(fenetre->format, 84, 84, 140));
	TRV_Jours = TTF_RenderText_Blended(police1, "Les rendez-vous du jours", color1);
	SDL_BlitSurface(Rv_Jours, NULL, fenetre, &Pos_RVJ);
	SDL_BlitSurface(TRV_Jours, NULL, fenetre, &Pos_RVJ);
	TRV_Jours = TTF_RenderText_Blended(police1, "Les autres rendez-vous", color1);
	Pos_RVJ.y +=200;
	SDL_BlitSurface(Autres_Rv, NULL, fenetre, &Pos_RVJ);
	SDL_BlitSurface(TRV_Jours, NULL, fenetre, &Pos_RVJ);
	SDL_FreeSurface(Rv_Jours);
	SDL_FreeSurface(Autres_Rv);
	SDL_FreeSurface(TRV_Jours);
	TTF_CloseFont(police1);

	BlitRv(fenetre, Nbr_Rv, Dossier);

}

void Message_Welcome(SDL_Surface* fenetre){
	SDL_Surface *background = NULL;
	SDL_Rect Pos_Bg;
	Pos_Bg.x = 400;
	Pos_Bg.y = 200;
	background = IMG_Load("images/tn_logoclinique.jpg");
	SDL_BlitSurface(background, NULL, fenetre, &Pos_Bg);
	Pos_Bg.x += 200;
	SDL_BlitSurface(background, NULL, fenetre, &Pos_Bg);
	SDL_FreeSurface(background);

	SDL_Surface *Texte = NULL, *espace_med = NULL, *Alle_Acc = NULL;
	TTF_Font *police = TTF_OpenFont("polices/GIGI.TTF", 50);
	SDL_Color aqua = {0, 162, 232}, noiratre = {125, 100, 20}, bleu = {0, 0, 255};
	Texte = TTF_RenderText_Blended(police, "BIENVENUE", aqua);
	TTF_CloseFont(police);
	police = TTF_OpenFont("polices/police.TTF", 20);
	TTF_SetFontStyle(police, TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE);
	Pos_Bg.x -= 200;
	espace_med = TTF_RenderText_Blended(police, "Dans l'espace Medecin", noiratre);
	Alle_Acc = TTF_RenderText_Blended(police, "Rendez-vous a l'accueille", bleu);
	Pos_Bg.x += 20;
	Pos_Bg.y -=100; 
	SDL_BlitSurface(Texte, NULL, fenetre, &Pos_Bg);
	Pos_Bg.y += 60;
	SDL_BlitSurface(espace_med, NULL, fenetre, &Pos_Bg);
	Pos_Bg.x += 250;
	Pos_Bg.y += 280;
	SDL_BlitSurface(Alle_Acc, NULL, fenetre, &Pos_Bg);
	SDL_FreeSurface(Alle_Acc); 
	SDL_FreeSurface(Texte);
	SDL_FreeSurface(espace_med);
}

void Pas_Connecter(SDL_Surface* fenetre){
	SDL_Surface* Texte = NULL;
	TTF_Font *police = TTF_OpenFont("polices/arial.ttf", 20);
	SDL_Rect Pos_Texte;
	Pos_Texte.x = 400;
	Pos_Texte.y = 300;
	TTF_SetFontStyle(police, TTF_STYLE_UNDERLINE | TTF_STYLE_ITALIC);
	SDL_Color rouge = {255, 0, 0};
	Texte = TTF_RenderText_Blended(police, "Rendez-vous a l'accueille, vous n'etes pas connecter", rouge);
	SDL_BlitSurface(Texte, NULL, fenetre, &Pos_Texte);
	SDL_FreeSurface(Texte);
	TTF_CloseFont(police);
}
void Espace_Medecin(SDL_Surface* fenetre, Bout_Esp_Med SURV, Bout_Esp_Med Bout_Appuye, identifiant mes_iden, Bout_Acc AccMed_Surv,
	Bout_Acc AccMed_App, Bout_ID ID_App, Bout_Creer_Compte CC_App, Bout_MesDispo Surv_MesDispo, Bout_MesDispo App_MesDispo,
	Dispo_Creation DC_App, char masqueur1[50], char masq_check[50], char masqueur2[50], int *connected, char confirmation[50],
	char Med_Conn_Nom[50], char Dossier_En_Cours[50], Rendez_Vous Cr_Rv, int *Nbr_Dispo, int Nbr_Rv, Clic_Droit clic_droit,
	SDL_Rect Pos_Clic_Droit){
	//Les bouttons
	FILE *fichier_nbrDispo = NULL, *fichier = NULL, *file = NULL;
	char le_dossier1[50] = "", le_dossier2[50] = "", le_dossier3[50] = "";
	int Pas_de_dispo = 0;
	strcpy(le_dossier1, Dossier_En_Cours);
	strcat(le_dossier1, "/disponibilites/dispo1.bin");

	strcpy(le_dossier2, Dossier_En_Cours);
	strcat(le_dossier2, "/nbrDispo.bin");

	strcpy(le_dossier3, Dossier_En_Cours);
	strcat(le_dossier3, "/nbr_rv.bin");

	if(*connected){

		fichier = fopen(le_dossier1, "rb");
		if(fichier == NULL){
			remove(le_dossier2);
			*Nbr_Dispo = 0;
			fclose(fichier);
		}else{
			fclose(fichier);
		}
		fichier_nbrDispo = fopen(le_dossier2, "rb");
		if(fichier_nbrDispo == NULL){
			fclose(fichier_nbrDispo);
			fichier_nbrDispo = fopen(le_dossier2, "wb");
			fwrite(Nbr_Dispo, sizeof(int), 1, fichier_nbrDispo);
			fclose(fichier_nbrDispo);
		}else{
			fread(Nbr_Dispo, sizeof(int), 1, fichier_nbrDispo);
			fclose(fichier_nbrDispo);
		}


		file = fopen(le_dossier3, "rb");
		if(file != NULL){
			fread(&Nbr_Rv, sizeof(int), 1, file);
			fclose(file);
		}else{
			Nbr_Rv = 0;
			fclose(file);
		}

	}
	
	SDL_Surface *Mes_Bouttons[2] = {NULL}, *Mes_Text[2] = {NULL};
	SDL_Color color={0, 0, 0};
	int i;
	SDL_Rect Pos_Bouttons[2], Pos_Texte[2];
	Pos_Bouttons[0].x = 2*BOUT_LONG;//abscisse ESP_MED_BOUT_2 300
	Pos_Bouttons[0].y = 40;//ordonne ESP_MED_BOUT_1 40
	Pos_Bouttons[1].x = 3*BOUT_LONG;//abscisse ESP_MED_BOUT_2 450
	Pos_Bouttons[1].y = 40;//Ordonnee ESP_MED_BOUT_2 40
	Pos_Texte[0].x = 2*BOUT_LONG;
	Pos_Texte[0].y = 60;
	Pos_Texte[1].x = 3*BOUT_LONG;
	Pos_Texte[1].y = 60;
	char *menu[2] = {"Mes Disponibilites", "Mes Rendez-Vous"};
	for(i=0; i<2; i++){
		Creation_Boutton(&Mes_Bouttons[i], BOUT_LONG, BOUT_LARG, menu[i], color, &Mes_Text[i]);
		Remplir_Surface(fenetre, Mes_Bouttons[i], 200, 200, 200);
	}

	switch(SURV){
		case ESP_MED_BOUT_1:
			Remplir_Surface(fenetre, Mes_Bouttons[0], 125, 125, 125);
			break;
		case ESP_MED_BOUT_2:
			Remplir_Surface(fenetre, Mes_Bouttons[1], 125, 125, 125);
			break;
	}

	for(i=0; i<2; i++){
		Placer_Les_Bouttons(fenetre, Mes_Bouttons[i], Pos_Bouttons[i]);
		Placer_Les_Bouttons(fenetre, Mes_Text[i], Pos_Texte[i]);
	}

	switch(Bout_Appuye){
		case ESP_MED_BOUT_1:
			if(*connected){
				Mes_Dispo(fenetre, Surv_MesDispo, App_MesDispo, DC_App, Dossier_En_Cours, Cr_Rv, Nbr_Dispo, clic_droit,
					Pos_Clic_Droit);
			}else{
				Pas_Connecter(fenetre);
			}
			break;
		case ESP_MED_BOUT_2:
			if(*connected){
				Mes_Rv(fenetre, Nbr_Rv, Dossier_En_Cours);
			}else
				Pas_Connecter(fenetre);
			break;
		case ESP_MED_BOUT_5:
			Acceuille_Medecin(fenetre, mes_iden, AccMed_Surv, AccMed_App, ID_App, CC_App, masqueur1, masq_check, masqueur2, connected,
				confirmation, Med_Conn_Nom);
			break;
		default:
			Message_Welcome(fenetre);
			break;
	}
	for(i=0; i<2; i++){
		SDL_FreeSurface(Mes_Bouttons[i]);
		SDL_FreeSurface(Mes_Text[i]);
	}


	SDL_Surface *message[7] = {NULL}, *logo = NULL;
	char* sms[7] = {"Bienvenue Dans l'espace des medecins", "Voici quelques elements a savoir :", " La creation d'un compte est equivaut",
				"a la creation d'un dossier.", "Pour que chaque medecin n'accede qu'a", "son dossier, il doit lui creer un", "compte d'utilisateur"};
	SDL_Rect Pos_message[7];
	TTF_Font *police;

	//Mise en place du logo
	SDL_Rect Pos_Log;
	Pos_Log.x = 0;
	Pos_Log.y = 80;
	logo = IMG_Load("images/logodoct.jpg");
	SDL_BlitSurface(logo, NULL, fenetre, &Pos_Log);
	SDL_FreeSurface(logo);


	Pos_message[0].x = 0;
	Pos_message[0].y = Pos_Log.y + 170;
	for(i=1; i<7; i++){
		Pos_message[i].x = Pos_message[i-1].x;
		Pos_message[i].y = Pos_message[i-1].y + 30;
	}
	police = TTF_OpenFont("polices/arial.ttf", 12);
	SDL_Color color1 = {0, 36, 72};
	for(i=0; i<7; i++){
		message[i] = TTF_RenderText_Blended(police, sms[i], color1);
	}

	for(i=0; i<7; i++){
		SDL_BlitSurface(message[i], NULL, fenetre, &Pos_message[i]);
	}

	for(i=0; i<7; i++){
		SDL_FreeSurface(message[i]);
	}

	//Boutton retour à l'accueille
	SDL_Surface *Retour = NULL, *img = NULL, *ici = NULL;
	SDL_Rect Pos_Retour;
	TTF_Font *MaPolice;
	Pos_Retour.x = 0;
	Pos_Retour.y = 460;
	img = IMG_Load("images/accueille.jpg");
	SDL_BlitSurface(img, NULL, fenetre, &Pos_Retour);
	Retour = TTF_RenderText_Blended(police, "Accueille Medecin", color);
	MaPolice = TTF_OpenFont("polices/ALGER.TTF", 30);
	ici = TTF_RenderText_Blended(MaPolice, "ICI", color);
	SDL_BlitSurface(Retour, NULL, fenetre, &Pos_Retour);
	Pos_Retour.x = 40;
	Pos_Retour.y = 490;
	SDL_BlitSurface(ici, NULL, fenetre, &Pos_Retour);
	SDL_FreeSurface(img);
	SDL_FreeSurface(Retour);
	SDL_FreeSurface(ici);
	TTF_CloseFont(police);
}

void Ordonner_Dispos(char medecin[50], int nbrDispo){
	char dossier1[50] = "", dossier2[50] = "", chiffre[5] = "";
	int i, j;

	if(nbrDispo == 0)
		return;
	FILE *fichier1 = NULL, *fichier2 = NULL;
	Rendez_Vous rv1 = {1, 1, 1900, 12, 00}, rv2 = {2, 1, 1900, 12, 00};
	for(i=0; i < nbrDispo - 1; i++){
		strcpy(dossier1, "Medecins/");
		strcat(dossier1, medecin);
		strcat(dossier1, "/disponibilites");
		strcat(dossier1, "/dispo");
		sprintf(chiffre, "%d", i+1);
		strcat(dossier1, chiffre);
		strcat(dossier1, ".bin");
		fichier1 = fopen(dossier1, "rb");
		if(fichier1 != NULL){
			fread(&rv1, sizeof(Rendez_Vous), 1, fichier1);
			fclose(fichier1);
		}else{
			fclose(fichier1);
			return;
		}
		for(j=i+1; j < nbrDispo; j++){
			strcpy(dossier2, "Medecins/");
			strcat(dossier2, medecin);
			strcat(dossier2, "/disponibilites");
			strcat(dossier2, "/dispo");
			sprintf(chiffre, "%d", j+1);
			strcat(dossier2, chiffre);
			strcat(dossier2, ".bin");
			fichier2 = fopen(dossier2, "rb");
			if(fichier2 != NULL){
				fread(&rv2, sizeof(Rendez_Vous), 1, fichier2);
				fclose(fichier2);
			}else{
				fclose(fichier2);
			}

			if(rv2.annee < rv1.annee ||(rv2.annee == rv1.annee && rv2.mois < rv1.mois) || (rv2.annee == rv1.annee && rv2.mois == rv1.mois && rv2.jours < rv1.jours) 
				|| (rv2.annee == rv1.annee && rv2.mois == rv1.annee && rv2.jours == rv1.jours && rv2.heure < rv1.heure) 
				|| (rv2.annee == rv1.annee && rv2.mois == rv1.mois && rv2.jours == rv1.jours && rv2.heure == rv1.heure && rv2.minutes < rv1.minutes)){
				fichier1 = fopen(dossier1, "wb");
				fwrite(&rv2, sizeof(Rendez_Vous), 1, fichier1);
				fclose(fichier1);
				fichier2 = fopen(dossier2, "wb");
				fwrite(&rv1, sizeof(Rendez_Vous), 1, fichier2);
				fclose(fichier2);
			}

		}
	}
}

void Ordonner_Rv(char Medecin[50], int Nbr_Rv){
	char dossier1[50] = "", dossier2[50] = "", chiffre[5] = "";
	int i, j;

	if(Nbr_Rv == 0){
		return;
	}
	FILE *fichier1 = NULL, *fichier2 = NULL;
	Patient p1, p2;
	for(i=0; i < Nbr_Rv - 1; i++){
		strcpy(dossier1, "Medecins/");
		strcat(dossier1, Medecin);
		strcat(dossier1, "/RendezVous");
		strcat(dossier1, "/rv");
		sprintf(chiffre, "%d", i+1);
		strcat(dossier1, chiffre);
		strcat(dossier1, ".bin");
		fichier1 = fopen(dossier1, "rb");
		if(fichier1 != NULL){
			fread(&p1, sizeof(Patient), 1, fichier1);
			fclose(fichier1);
		}else{
			fclose(fichier1);
			return;
		}
		for(j=i+1; j < Nbr_Rv; j++){
			strcpy(dossier2, "Medecins/");
			strcat(dossier2, Medecin);
			strcat(dossier2, "/RendezVous");
			strcat(dossier2, "/rv");
			sprintf(chiffre, "%d", j+1);
			strcat(dossier2, chiffre);
			strcat(dossier2, ".bin");
			fichier2 = fopen(dossier2, "rb");
			if(fichier2 != NULL){
				fread(&p2, sizeof(Patient), 1, fichier2);
				fclose(fichier2);
			}else{
				fclose(fichier2);
			}

			if(p2.rv.annee < p1.rv.annee ||(p2.rv.annee == p1.rv.annee && p2.rv.mois < p1.rv.mois) || (p2.rv.annee == p1.rv.annee && p2.rv.mois == p1.rv.mois && p2.rv.jours < p1.rv.jours) 
				|| (p2.rv.annee == p1.rv.annee && p2.rv.mois == p1.rv.annee && p2.rv.jours == p1.rv.jours && p2.rv.heure < p1.rv.heure) 
				|| (p2.rv.annee == p1.rv.annee && p2.rv.mois == p1.rv.mois && p2.rv.jours == p1.rv.jours && p2.rv.heure == p1.rv.heure && p2.rv.minutes < p1.rv.minutes)){
				fichier1 = fopen(dossier1, "wb");
				fwrite(&p2, sizeof(Patient), 1, fichier1);
				fclose(fichier1);
				fichier2 = fopen(dossier2, "wb");
				fwrite(&p1, sizeof(Patient), 1, fichier2);
				fclose(fichier2);
			}
		}
	}
}


//Ces fonctions qui suivent reperent les positions de la souri zone medecin.
boutton Mouse_Zone(int abscisse, int ordonnee, int longueur, int largeur, boutton Bout_Appuye){
	if(abscisse > 320 && abscisse < 770 && ordonnee > largeur/3 + 100 && ordonnee < largeur/3 + 100 + BOUT_LARG){
		return ACC_BOUT_1;
	}else if(abscisse > 572 && abscisse < 676 && ordonnee > largeur/3 + 100 && ordonnee < largeur/3 + 130){
		return ACC_BOUT_2;
	}else if(abscisse > 0 && abscisse < 150 && ordonnee > 0 && ordonnee < 40){
		return ACC;
	}else if(abscisse > 151 && abscisse < 151 + BOUT_LONG && ordonnee > 0 && ordonnee < 40){
		return SEC;
	}else if(abscisse > 302 && abscisse < 302 + BOUT_LONG && ordonnee > 0 && ordonnee < 40){
		return MED;
	}else if(abscisse > 453 && abscisse < 453 + BOUT_LONG && ordonnee >0 && ordonnee < 40){
		return AID;
	}else
		return Bout_Appuye;
}

Bout_Esp_Med Bout_survole_Med(int abscisse, int ordonnee, int longueur, int largeur, Bout_Esp_Med Bout_Appuye){
	if(abscisse > 300 && abscisse < 300 + BOUT_LONG && ordonnee > 40 && ordonnee < 40 + BOUT_LARG){
		return ESP_MED_BOUT_1;
	}else if(abscisse > 450 && abscisse < 450 +BOUT_LONG && ordonnee > 40 && ordonnee < 40 + BOUT_LARG){
		return ESP_MED_BOUT_2;
	}else if(abscisse > 0 && abscisse < 100 && ordonnee > 460 && ordonnee < 560){
		return ESP_MED_BOUT_5;
	}else
		return AUCUN;
}

Bout_Esp_Med Bout_Appuye_Med(int abscisse, int ordonnee, int longueur, int largeur, Bout_Esp_Med Bout_Appuye){
	if(abscisse > 300 && abscisse < 300 + BOUT_LONG && ordonnee > 40 && ordonnee < 40 + BOUT_LARG){
		return ESP_MED_BOUT_1;
	}else if(abscisse > 450 && abscisse < 450 +BOUT_LONG && ordonnee > 40 && ordonnee < 40 + BOUT_LARG){
		return ESP_MED_BOUT_2;
	}else if(abscisse > 0 && abscisse < 100 && ordonnee > 460 && ordonnee < 560){
		return ESP_MED_BOUT_5;
	}else
		return Bout_Appuye;
}


Bout_Acc Boutton_AccSurv(int abscisse, int ordonnee, int longueur, int largeur, Bout_Acc Bout_Appuye){
	if(abscisse > 500 && abscisse < 600 && ordonnee > 250 && ordonnee < 275){
		return ESP_MEDACC_BOUT_1;
	}else if(abscisse > 500 && abscisse < 600 && ordonnee > 295 && ordonnee < 315){
		return ESP_MEDACC_BOUT_2;
	}else if(abscisse > 770 && abscisse < 870 && ordonnee > 430 && ordonnee < 455){
		return DECONNECTE;
	}else
		return NONE;
}

Bout_Acc Boutton_Acc(int abscisse, int ordonnee, int longueur, int largeur, Bout_Acc Bout_Appuye){
	if(abscisse > 500 && abscisse < 600 && ordonnee > 250 && ordonnee < 275){
		return ESP_MEDACC_BOUT_1;
	}else if(abscisse > 500 && abscisse < 600 && ordonnee > 295 && ordonnee < 315){
		return ESP_MEDACC_BOUT_2;
	}else if(abscisse > 770 && abscisse < 870 && ordonnee > 430 && ordonnee < 455){
		return DECONNECTE;
	}else
		return Bout_Appuye;
}

Bout_ID Boutton_IDApp(int abscisse, int ordonnee, int longueur, int largeur, Bout_ID Bout_Appuye){
	if(abscisse > 600 && abscisse < 680 && ordonnee > 400 && ordonnee < 430){
		return NO_ID;
	}else if(abscisse > 530 && abscisse < 580 && ordonnee > 400 && ordonnee < 430){
		return ESP_MED_BOUT_ID3;
	}else if(abscisse > 510 && abscisse < 660 && ordonnee > 185 && ordonnee < 215){
		return ESP_MED_BOUT_ID1;
	}else if(abscisse > 510 && abscisse < 660 && ordonnee > 240 && ordonnee < 270){
		return ESP_MED_BOUT_ID2;
	}else if(Bout_Appuye == NO_ID){
		return RIEN;
	}else
		return Bout_Appuye;
}

Bout_Creer_Compte Boutton_CCApp(int abscisse, int ordonnee, int longueur, int largeur, Bout_Creer_Compte Bout_Appuye){
	if(abscisse > 550 && abscisse < 625 && ordonnee > 280 && ordonnee < 323){
		return ESP_MED_BOUT_CC4;
	}else if(abscisse > 620 && ordonnee < 695 && ordonnee > 280 && ordonnee < 323){
		return ANN;
	}else if(abscisse > 450 && abscisse < 620 && ordonnee > 170 && ordonnee < 200){
		return ESP_MED_BOUT_CC1;
	}else if(abscisse > 450 && abscisse < 620 && ordonnee > 210 && ordonnee < 240){
		return ESP_MED_BOUT_CC2;
	}else if(abscisse > 450 && abscisse < 620 && ordonnee > 250 && ordonnee < 280){
		return ESP_MED_BOUT_CC3;
	}else if(Bout_Appuye == ANN){
		return NUL;
	}else
		return Bout_Appuye;
}

Bout_MesDispo Boutton_MesDispos_Surv(int abscisse, int ordonnee, int droit_x, int droit_y, Bout_MesDispo Bout_Appuye){
	if(abscisse > 500 && abscisse < 700 && ordonnee > 90 && ordonnee < 130){
		return NEW_DISPO;
	}else if(abscisse > droit_x && abscisse < droit_x + 100 && ordonnee > droit_y && ordonnee < droit_y + 30){
		return EDIT_DISPO;
	}else if(abscisse > droit_x && abscisse < droit_x + 100 && ordonnee > droit_y + 30 && ordonnee < droit_y + 60){
		return DELETE_DISPO;
	}else if(abscisse > droit_x && abscisse < droit_x + 100 && ordonnee > droit_y + 60 && ordonnee < droit_y + 90){
		return DISPO_DETAIL;
	}else
		return NOTHING;
}

Bout_MesDispo Boutton_MesDispos_App(int abscisse, int ordonnee, int droit_x, int droit_y, Bout_MesDispo Bout_Appuye){
	if(abscisse > 500 && abscisse < 700 && ordonnee > 90 && ordonnee < 130){
		return NEW_DISPO;
	}else if(abscisse > droit_x && abscisse < droit_x + 100 && ordonnee > droit_y && ordonnee < droit_y + 30){
		return EDIT_DISPO;
	}else if(abscisse > droit_x && abscisse < droit_x + 100 && ordonnee > droit_y + 30 && ordonnee < droit_y + 60){
		return DELETE_DISPO;
	}else if(abscisse > droit_x && abscisse < droit_x + 100 && ordonnee > droit_y + 60 && ordonnee < droit_y + 90){
		return DISPO_DETAIL;
	}else
		return NOTHING;
}

Dispo_Creation Boutton_App_Dispo(int abscisse, int ordonnee, int longueur, int largeur, Dispo_Creation Bout_Appuye){
	if(abscisse > 550 && abscisse < 620 && ordonnee > 280 && ordonnee < 305){
		return DC_VALIDE;
	}else if(abscisse > 780 && abscisse < 800 && ordonnee > 110 && ordonnee < 130){
		return DC_QUIT;
	}else if(abscisse > 460 && abscisse < 510 && ordonnee > 145 && ordonnee < 175){
		return DC_JOURS;
	}else if(abscisse > 460 && abscisse < 510 && ordonnee > 185 && ordonnee < 215){
		return DC_MOIS;
	}else if(abscisse > 460 && abscisse < 510 && ordonnee > 225 && ordonnee < 255){
		return DC_ANNEE;
	}else if(abscisse > 700 && abscisse < 750 && ordonnee > 145 && ordonnee < 175){
		return DC_HEURE;
	}else if(abscisse > 700 && abscisse < 750 && ordonnee > 185 && ordonnee < 215){
		return DC_MINUTE;
	}else if(abscisse > 510 && abscisse < 526 && ordonnee > 145 && ordonnee < 156){
		return DC_APRES_1;
	}else if(abscisse > 510 && abscisse < 526 && ordonnee > 185 && ordonnee < 196){
		return DC_APRES_2;
	}else if(abscisse > 510 && abscisse < 526 && ordonnee > 225 && ordonnee < 236){
		return DC_APRES_3;
	}else if(abscisse > 750 && abscisse < 766 && ordonnee > 145 && ordonnee < 156){
		return DC_APRES_4;
	}else if(abscisse > 750 && abscisse < 766 && ordonnee > 185 && ordonnee < 196){
		return DC_APRES_5;
	}else if(abscisse > 510 && abscisse < 526 && ordonnee > 165 && ordonnee < 176){
		return DC_AVANT_1;
	}else if(abscisse > 510 && abscisse < 526 && ordonnee > 205 && ordonnee < 216){
		return DC_AVANT_2;
	}else if(abscisse > 510 && abscisse < 526 && ordonnee > 245 && ordonnee < 256){
		return DC_AVANT_3;
	}else if(abscisse > 750 && abscisse < 766 && ordonnee > 165 && ordonnee < 176){
		return DC_AVANT_4;
	}else if(abscisse > 750 && abscisse < 766 && ordonnee > 205 && ordonnee < 216){
		return DC_AVANT_5;
	}else if(Bout_Appuye == DC_QUIT){
		return DC_RIEN;
	}else if(Bout_Appuye == DC_VALIDE){
		return DC_QUIT;
	}else
		return Bout_Appuye;
}
//reperage position souri fini ici.

//Fin pour la zone medecin

/*
	Meme chose pour la zone secretariat
*/

void Zone_Alerte(SDL_Surface* fenetre){
	SDL_Surface *Zone = NULL, *T_Zone = NULL;
	SDL_Rect Pos_Zone;
	TTF_Font *police1 = TTF_OpenFont("polices/arial.ttf", 20);
	TTF_SetFontStyle(police1, TTF_STYLE_UNDERLINE | TTF_STYLE_BOLD | TTF_STYLE_ITALIC);
	SDL_Color rouge = {255, 0, 0};
	Pos_Zone.x = 0;
	Pos_Zone.y = 40;
	Zone = SDL_CreateRGBSurface(SDL_HWSURFACE, 280, 700, 32, 0, 0, 0, 0);
	SDL_FillRect(Zone, NULL, SDL_MapRGB(fenetre->format, 255, 217, 179));
	T_Zone = TTF_RenderText_Blended(police1, "Z o n e  d ' A l e r t e", rouge);
	SDL_BlitSurface(Zone, NULL, fenetre, &Pos_Zone);
	SDL_BlitSurface(T_Zone, NULL, fenetre, &Pos_Zone);
	SDL_FreeSurface(Zone);
	SDL_FreeSurface(T_Zone);
	TTF_CloseFont(police1);

	SDL_Surface* Ligne = NULL;
	SDL_Rect Pos_Ligne;
	Pos_Ligne.x = 280;
	Pos_Ligne.y = 40;
	Ligne = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 700, 32, 0, 0, 0, 0);
	SDL_BlitSurface(Ligne, NULL, fenetre, &Pos_Ligne);
	SDL_FreeSurface(Ligne);

	SDL_Surface *Logo_Secretaire = NULL;
	SDL_Rect Pos_LogSec;
	Pos_LogSec.x = 320;
	Pos_LogSec.y = 150;
	Logo_Secretaire = IMG_Load("images/tn_logosecretaire.jpg");
	SDL_BlitSurface(Logo_Secretaire, NULL, fenetre, &Pos_LogSec);
	SDL_FreeSurface(Logo_Secretaire);
}

void Texte_Accueille(SDL_Surface* fenetre){
	SDL_Surface *phrase[5] = {NULL}, *Message_Bienvenue = NULL;
	char* Mon_Texte[5] = {"Les secretaires ont acces au dossier de chaque medecin.", "Comme ces derniers, ils doivent aussi disposer",
	"d'un code de securite, donc d'un compte(dossier).", "Ils pourront creer des rendez-vous pour les medecins selon",
	"les disponibilites indiquees."};
	SDL_Rect Pos_Phrase[5], Pos_MBV;
	Pos_MBV.x = 450;
	Pos_MBV.y = 80;
	SDL_Color noir = {0, 0, 0}, noiratre = {20, 20, 20};
	TTF_Font *police_1 = NULL, *police_2 = NULL;
	police_1 = TTF_OpenFont("polices/arial.ttf", 14);
	police_2 = TTF_OpenFont("polices/police.TTF", 30);
	TTF_SetFontStyle(police_2, TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE | TTF_STYLE_BOLD);
	int i;
	for(i=0; i<5; i++){
		if(i==0){
			Pos_Phrase[i].x = 519;
			Pos_Phrase[i].y = 150;
		}else{
			Pos_Phrase[i].x = Pos_Phrase[i-1].x;
			Pos_Phrase[i].y = Pos_Phrase[i-1].y + 40;
		}

		phrase[i] = TTF_RenderText_Blended(police_1, Mon_Texte[i], noir);
		SDL_BlitSurface(phrase[i], NULL, fenetre, &Pos_Phrase[i]);
		SDL_FreeSurface(phrase[i]);
	}

	Message_Bienvenue = TTF_RenderText_Blended(police_2, "S E C R E T A R I A T", noiratre);
	SDL_BlitSurface(Message_Bienvenue, NULL, fenetre, &Pos_MBV);
	SDL_FreeSurface(Message_Bienvenue);

	TTF_CloseFont(police_1);
	TTF_CloseFont(police_2);
}

void Creation_Compte_Sec(SDL_Surface* fenetre, Bout_Compte_Sec Bout_Appuye, identifiant id, char masqueur1[50],
 char masqueur2[50], char verifie[50]){
	SDL_Surface *Nom = NULL, *Mdp = NULL, *CMdp = NULL, *Surface = NULL;
	SDL_Rect Pos_Nom, Pos_Mdp, Pos_CMdp, Pos_Surface;
	SDL_Color noire = {0, 0, 0};
	TTF_Font *arial = TTF_OpenFont("polices/arial.ttf", 14);
	Nom = TTF_RenderText_Blended(arial, " Nom ", noire);
	Mdp = TTF_RenderText_Blended(arial, " Mot de passe", noire);
	CMdp = TTF_RenderText_Blended(arial, "Confirmer mot de passe ", noire);
	Surface = SDL_CreateRGBSurface(SDL_HWSURFACE, 400, 200, 32, 0, 0, 0, 0);
	SDL_FillRect(Surface, NULL, SDL_MapRGB(fenetre->format, 74, 255, 165));

	Pos_Surface.x = 519;
	Pos_Surface.y = 150;
	Pos_Nom.x = 529;
	Pos_Nom.y = 180;
	Pos_Mdp.x = 529;
	Pos_Mdp.y = 220;
	Pos_CMdp.x = 519;
	Pos_CMdp.y = 260;

	SDL_BlitSurface(Surface, NULL, fenetre, &Pos_Surface);
	SDL_BlitSurface(Nom, NULL, fenetre, &Pos_Nom);
	SDL_BlitSurface(Mdp, NULL, fenetre, &Pos_Mdp);
	SDL_BlitSurface(CMdp, NULL, fenetre, &Pos_CMdp);

	SDL_FreeSurface(Surface);
	SDL_FreeSurface(Nom);
	SDL_FreeSurface(Mdp);
	SDL_FreeSurface(CMdp);

	SDL_Surface *Surf_Nom = NULL, *Surf_Mdp = NULL, *Surf_CMdp = NULL;
	Surf_Nom = SDL_CreateRGBSurface(SDL_HWSURFACE, 170, 30, 32, 0, 0, 0, 0);
	Surf_Mdp = SDL_CreateRGBSurface(SDL_HWSURFACE, 170, 30, 32, 0, 0, 0, 0);
	Surf_CMdp = SDL_CreateRGBSurface(SDL_HWSURFACE, 170, 30, 32, 0, 0, 0, 0);
	SDL_FillRect(Surf_Nom, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));
	SDL_FillRect(Surf_Mdp, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));
	SDL_FillRect(Surf_CMdp, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));
	Pos_Nom.x += 50;
	Pos_Nom.y -=10;
	SDL_BlitSurface(Surf_Nom, NULL, fenetre, &Pos_Nom);
	Pos_Mdp.x += 100;
	Pos_Mdp.y -=10;
	SDL_BlitSurface(Surf_Mdp, NULL, fenetre, &Pos_Mdp);
	Pos_CMdp.x += 160;
	Pos_CMdp.y -= 10;
	SDL_BlitSurface(Surf_CMdp, NULL, fenetre, &Pos_CMdp);

	SDL_FreeSurface(Surf_Nom);
	SDL_FreeSurface(Surf_Mdp);
	SDL_FreeSurface(Surf_CMdp);


	SDL_Surface *Bout_Valider = NULL, *Bout_Quitter = NULL, *Surface_Val = NULL, *Surf_legende = NULL, *legende = NULL;
	SDL_Rect Pos_Valide, Pos_Quitte, Pos_SurfLeg;
	Pos_SurfLeg.x = 519;
	Pos_SurfLeg.y = 130;
	TTF_Font *Leg_Police = TTF_OpenFont("polices/police.TTF", 12);
	SDL_Color blanc = {255, 255, 255}, noir = {0, 0, 0};
	legende = TTF_RenderText_Blended(Leg_Police, "Secretariat : Creation de compte", blanc);
	Surf_legende = SDL_CreateRGBSurface(SDL_HWSURFACE, 400, 20, 32, 0, 0, 0, 0);
	SDL_FillRect(Surf_legende, NULL, SDL_MapRGB(fenetre->format, 136, 0, 21));
	SDL_BlitSurface(Surf_legende, NULL, fenetre, &Pos_SurfLeg);
	Pos_SurfLeg.x += 100;
	SDL_BlitSurface(legende, NULL, fenetre, &Pos_SurfLeg);
	Pos_Valide.x = 689;
	Pos_Valide.y = 290;
	Surface_Val = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 25, 32, 0, 0, 0, 0);
	SDL_FillRect(Surface_Val, NULL, SDL_MapRGB(fenetre->format, 0, 255, 0));
	Bout_Valider = IMG_Load("images/valide.png");
	SDL_BlitSurface(Bout_Valider, NULL, fenetre, &Pos_Valide);
	Bout_Quitter = IMG_Load("images/ferme.jpg");
	Pos_Quitte.x = 899;
	Pos_Quitte.y = 130;
	SDL_BlitSurface(Bout_Quitter, NULL, fenetre ,&Pos_Quitte);

	SDL_FreeSurface(Bout_Valider);
	SDL_FreeSurface(Bout_Quitter);
	SDL_FreeSurface(legende);
	SDL_FreeSurface(Surf_legende);

	SDL_Surface *Blit_Nom = NULL, *Blit_Mdp = NULL,  *Blit_CMdp = NULL;
	char name[50] = "",password[50] = "", check[50] = "";
	Pos_Nom.y += 15;
	Pos_Mdp.y += 15;
	Pos_CMdp.y += 15;

	SDL_Surface *alert = NULL, *TickWrong = NULL;
	SDL_Rect Pos_alert;
	Pos_alert.x = 519;
	Pos_alert.y = 280;
	SDL_Color red = {255, 0, 0}, green = {34, 177, 76}; 
	char dossier[50] = "Secretaires/";
	TTF_Font *petit_arial = TTF_OpenFont("polices/arial.ttf", 12);
	FILE *exist = NULL, *fichier = NULL;

	strcat(dossier, id.Nom_Utilisateur);
	strcat(dossier, "/identifiants.bin");

	identifiant mes_id = {"", ""};
	switch(Bout_Appuye){
		case BOUT_COMPTE_NOM:
			strcpy(name, id.Nom_Utilisateur);
			strcat(name, "|");
			Blit_Nom = TTF_RenderText_Blended(arial, name, noir);
			Blit_Mdp = TTF_RenderText_Blended(arial, masqueur1, noir);
			Blit_CMdp = TTF_RenderText_Blended(arial, masqueur2, noir);
			break;
		case BOUT_COMPTE_MDP:
			strcpy(password, masqueur1);
			strcat(password, "|");
			Blit_Nom = TTF_RenderText_Blended(arial, id.Nom_Utilisateur, noir);
			Blit_Mdp = TTF_RenderText_Blended(arial, password, noir);
			Blit_CMdp = TTF_RenderText_Blended(arial, masqueur2, noir);
			break;
		case BOUT_COMPTE_CMDP:
			strcpy(check, masqueur2);
			strcat(check, "|");
			Blit_Nom = TTF_RenderText_Blended(arial, id.Nom_Utilisateur, noir);
			Blit_Mdp = TTF_RenderText_Blended(arial, masqueur1, noir);
			Blit_CMdp = TTF_RenderText_Blended(arial, check, noir);
			break;
		case BOUT_COMPTE_VALIDE:
			exist = fopen(dossier, "rb");
			if(exist == NULL && strcmp(id.Nom_Utilisateur, "") != 0 && strcmp(id.Mot_De_Pass, verifie) == 0){
				fichier = fopen(dossier, "wb");
				fwrite(&id, sizeof(identifiant), 1, fichier);
				fclose(exist);
				exist = fopen(dossier, "rb");
				if(exist !=NULL){
					alert = TTF_RenderText_Blended(petit_arial, "accout created", green);
					TickWrong = IMG_Load("images/tick.png");
				}else{
					alert = TTF_RenderText_Blended(petit_arial, "No such folder", red);
					TickWrong = IMG_Load("images/wrong.png");
				}
				fclose(exist);
			}else if(exist != NULL){
				fread(&mes_id, sizeof(identifiant),1, exist);
				alert = TTF_RenderText_Blended(petit_arial, "account created", green);
				if(strcmp(mes_id.Mot_De_Pass, id.Mot_De_Pass) != 0)
					alert = TTF_RenderText_Blended(petit_arial, "already exist", green);
				TickWrong = IMG_Load("images/tick.png");
				fclose(exist);
			}else if(strcmp(id.Nom_Utilisateur, "") != 0 && strcmp(id.Mot_De_Pass, verifie) != 0){
					alert = TTF_RenderText_Blended(petit_arial, "differents passwords", red);
					TickWrong = IMG_Load("images/wrong.png");
					fclose(exist);
			}

			if(strcmp(id.Nom_Utilisateur, "") == 0 || strcmp(id.Mot_De_Pass, "") == 0 || strcmp(verifie, "") == 0){
				alert = TTF_RenderText_Blended(petit_arial, "empty fields", red);
				TickWrong = IMG_Load("images/wrong.png");
			}
			fclose(fichier);
		default:
			Blit_Nom = TTF_RenderText_Blended(arial, id.Nom_Utilisateur, noir);
			Blit_Mdp = TTF_RenderText_Blended(arial, masqueur1, noir);
			Blit_CMdp = TTF_RenderText_Blended(arial, masqueur2, noir);
			break;
	}
	SDL_BlitSurface(Blit_Nom, NULL, fenetre, &Pos_Nom);
	SDL_BlitSurface(Blit_Mdp, NULL, fenetre, &Pos_Mdp);
	SDL_BlitSurface(Blit_CMdp, NULL, fenetre, &Pos_CMdp);
	Pos_alert.x += 30;
	SDL_BlitSurface(TickWrong, NULL, fenetre, &Pos_alert);
	Pos_alert.y +=16;
	Pos_alert.x -= 30;
	SDL_BlitSurface(alert, NULL, fenetre, &Pos_alert);
	SDL_FreeSurface(alert);
	SDL_FreeSurface(TickWrong);
	TTF_CloseFont(petit_arial);

	SDL_FreeSurface(Blit_Nom);
	SDL_FreeSurface(Blit_Mdp);
	SDL_FreeSurface(Blit_CMdp);
	TTF_CloseFont(arial);
	TTF_CloseFont(Leg_Police);
}

void Connexion_Sec(SDL_Surface* fenetre, Bout_Connect_Sec Bout_Appuye, identifiant id, char masqueur1[50], int *connected){
	SDL_Surface *Nom = NULL, *Mdp = NULL, *Ok = NULL, *Surface = NULL, *Surf_legende = NULL, *legende = NULL, *Quit = NULL;
	SDL_Rect Pos_Nom, Pos_Mdp, Pos_Surface, Pos_LegSurf, Pos_Ok, Pos_Quit;
	Pos_Surface.x = 519;
	Pos_Surface.y = 150;
	Pos_LegSurf.x = 519;
	Pos_LegSurf.y = 130;
	Surface = SDL_CreateRGBSurface(SDL_HWSURFACE, 400, 200, 32, 0, 0, 0, 0);
	Surf_legende = SDL_CreateRGBSurface(SDL_HWSURFACE, 400, 20, 32, 0, 0, 0, 0);
	SDL_FillRect(Surf_legende, NULL, SDL_MapRGB(fenetre->format, 136, 0, 21));
	SDL_FillRect(Surface, NULL, SDL_MapRGB(fenetre->format, 0, 255, 255));
	SDL_BlitSurface(Surface, NULL, fenetre, &Pos_Surface);
	SDL_BlitSurface(Surf_legende, NULL, fenetre, &Pos_LegSurf);

	TTF_Font *arial = TTF_OpenFont("polices/arial.ttf", 14);
	TTF_Font *Leg_Police = TTF_OpenFont("polices/police.TTF", 12);
	SDL_Color noir = {0, 0, 0}, blanc = {255, 255, 255};
	Nom = TTF_RenderText_Blended(arial, " Nom ", noir);
	Mdp = TTF_RenderText_Blended(arial, " Mot de passe ", noir);
	Ok = IMG_Load("images/ok.png");
	Pos_Nom.x = 529;
	Pos_Nom.y = 180;
	Pos_Mdp.x = 529;
	Pos_Mdp.y = 250;
	Pos_Ok.x = 650;
	Pos_Ok.y = 300;
	SDL_BlitSurface(Nom, NULL, fenetre, &Pos_Nom);
	SDL_BlitSurface(Mdp, NULL, fenetre, &Pos_Mdp);
	SDL_BlitSurface(Ok, NULL, fenetre, &Pos_Ok);

	legende = TTF_RenderText_Blended(Leg_Police, " Secretariat : connexion ", blanc);
	Pos_LegSurf.x += 100;
	SDL_BlitSurface(legende, NULL, fenetre, &Pos_LegSurf);
	Quit = IMG_Load("images/ferme.jpg");
	Pos_Quit.x = 899;
	Pos_Quit.y = 130;
	SDL_BlitSurface(Quit, NULL, fenetre, &Pos_Quit);

	SDL_Surface *Surf_Nom = NULL, *Surf_Mdp = NULL;
	Surf_Nom = SDL_CreateRGBSurface(SDL_HWSURFACE, 170, 30, 32, 0, 0, 0, 0);
	Surf_Mdp = SDL_CreateRGBSurface(SDL_HWSURFACE, 170, 30, 32, 0, 0, 0, 0);
	SDL_FillRect(Surf_Nom, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));
	SDL_FillRect(Surf_Mdp, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));
	Pos_Nom.x += 50;
	Pos_Nom.y -=15;
	Pos_Mdp.x +=100;
	Pos_Mdp.y -= 15;
	SDL_BlitSurface(Surf_Nom, NULL, fenetre, &Pos_Nom);
	SDL_BlitSurface(Surf_Mdp, NULL, fenetre, &Pos_Mdp); 

	SDL_FreeSurface(Surface);
	SDL_FreeSurface(Nom);
	SDL_FreeSurface(Mdp);
	SDL_FreeSurface(Ok);
	SDL_FreeSurface(Surf_legende);
	SDL_FreeSurface(legende);
	SDL_FreeSurface(Quit);
	SDL_FreeSurface(Surf_Mdp);
	SDL_FreeSurface(Surf_Nom);


	SDL_Surface *Blit_Nom = NULL, *Blit_Mdp = NULL, *alert = NULL, *TickWrong = NULL;
	SDL_Rect Pos_alert;
	SDL_Color red = {255, 0, 0}, green = {34, 177, 76};
	char name[50] = "", password[50] = "";
	Pos_Nom.y += 15;
	Pos_Mdp.y += 15;
	Pos_alert.x = 720;
	Pos_alert.y = 280;
	FILE *fichier = NULL;
	char dossier[50] = "Secretaires/";
	strcat(dossier, id.Nom_Utilisateur);
	strcat(dossier, "/identifiants.bin");
	identifiant Mes_Id = {"", ""};
	TTF_Font *petit_arial = TTF_OpenFont("polices/arial.ttf", 12);
	switch(Bout_Appuye){
		case BOUT_CONNECT_NOM:
			strcpy(name, id.Nom_Utilisateur);
			strcat(name, "|");
			Blit_Nom = TTF_RenderText_Blended(arial, name, noir);
			Blit_Mdp = TTF_RenderText_Blended(arial, masqueur1, noir);
			break;
		case BOUT_CONNECT_MDP:
			strcpy(password, masqueur1);
			strcat(password, "|");
			Blit_Mdp = TTF_RenderText_Blended(arial, password, noir);
			Blit_Nom = TTF_RenderText_Blended(arial, id.Nom_Utilisateur, noir);
			break;
		case BOUT_CONNECT_OK:
			fichier = fopen(dossier, "rb");
			if(fichier != NULL){
				fread(&Mes_Id, sizeof(identifiant), 1, fichier);
				if(strcmp(Mes_Id.Nom_Utilisateur, id.Nom_Utilisateur) == 0 && strcmp(Mes_Id.Mot_De_Pass, id.Mot_De_Pass) == 0){
					*connected = 1;
					alert = TTF_RenderText_Blended(petit_arial, " Connected successfuly ", green);
					TickWrong = IMG_Load("images/tick.png");
				}else{
					alert = TTF_RenderText_Blended(petit_arial, "password or username incorrect", red);
					TickWrong = IMG_Load("images/wrong.png");
				}
			}else{
				alert = TTF_RenderText_Blended(petit_arial, " Please create an account ", green);
				TickWrong = IMG_Load("images/wrong.png");
			}
			fclose(fichier);
		default:
			Blit_Mdp = TTF_RenderText_Blended(arial, masqueur1, noir);
			Blit_Nom = TTF_RenderText_Blended(arial, id.Nom_Utilisateur, noir);
			break;
	}
	SDL_BlitSurface(Blit_Nom, NULL, fenetre, &Pos_Nom);
	SDL_BlitSurface(Blit_Mdp, NULL, fenetre, &Pos_Mdp);
	SDL_BlitSurface(TickWrong, NULL, fenetre, &Pos_alert);
	Pos_alert.x += 18;
	SDL_BlitSurface(alert, NULL, fenetre, &Pos_alert);
	SDL_FreeSurface(Blit_Nom);
	SDL_FreeSurface(Blit_Mdp);
	SDL_FreeSurface(alert);
	SDL_FreeSurface(TickWrong);
	TTF_CloseFont(petit_arial);

	TTF_CloseFont(arial);
	TTF_CloseFont(Leg_Police);
}

int If_Rv_Repeat(char Medecin[50], int Nombre_Rv, Patient patient){
	char le_dossier[50] = "", le_chiffre[5] = "";
	int i;
	FILE *fichier = NULL;
	Patient p;
	for(i=0; i<Nombre_Rv; i++){
		strcpy(le_dossier, "Medecins/");
		strcat(le_dossier, Medecin);
		strcat(le_dossier, "/RendezVous/rv");
		sprintf(le_chiffre, "%d", i+1);
		strcat(le_dossier, le_chiffre);
		strcat(le_dossier, ".bin");

		fichier = fopen(le_dossier, "rb");
		if(fichier != NULL){
			fread(&p, sizeof(Patient), 1, fichier);
			fclose(fichier);
			if(strcmp(patient.nom, p.nom) == 0 && strcmp(patient.prenom, p.prenom) == 0 && strcmp(patient.age, p.age) == 0 && patient.sexe == p.sexe
				&& strcmp(patient.traitement, p.traitement) == 0 && patient.rv.jours == p.rv.jours && patient.rv.mois == p.rv.mois && patient.rv.annee == p.rv.annee
				&& patient.rv.heure == p.rv.heure && patient.rv.minutes == p.rv.minutes){
				return 1;
			}else if(patient.rv.jours == p.rv.jours && patient.rv.mois == p.rv.mois && patient.rv.annee == p.rv.annee
				&& patient.rv.heure == p.rv.heure && patient.rv.minutes == p.rv.minutes){
				return 2;
			}else if(strcmp(patient.nom, p.nom) == 0 && strcmp(patient.prenom, p.prenom) == 0 && strcmp(patient.age, p.age) == 0 && patient.sexe == p.sexe
				&& strcmp(patient.traitement, p.traitement) == 0){
				return 3;
			}
		}else
			fclose(fichier);
	}

	return 0;
}

void Creer_Patient(SDL_Surface *fenetre, Bout_CreerPatient_Sec Bout_Appuye, char Medecin[50], Patient patient, int *compteur,
		int *Nbr_Rv, int *Nbr_Dispo){
	SDL_Surface *background = NULL, *En_tete = NULL, *Leg_Entete = NULL;
	SDL_Rect Bg_Pos;
	Bg_Pos.x = 300;
	Bg_Pos.y = 70;
	background = SDL_CreateRGBSurface(SDL_HWSURFACE, 600, 500, 32, 0, 0, 0, 0);
	SDL_FillRect(background, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));
	En_tete = SDL_CreateRGBSurface(SDL_HWSURFACE, 600, 20, 32, 0, 0, 0, 0);
	SDL_BlitSurface(background, NULL, fenetre, &Bg_Pos);
	SDL_BlitSurface(En_tete, NULL, fenetre, &Bg_Pos);
	SDL_FreeSurface(background);
	SDL_FreeSurface(En_tete);
	TTF_Font *arial_12 = TTF_OpenFont("polices/arial.ttf", 12);
	SDL_Color blanc = {255, 255, 255};
	Leg_Entete = TTF_RenderText_Blended(arial_12, "Creation d'un patient", blanc);
	Bg_Pos.x += 220;
	Bg_Pos.y += 5;
	SDL_BlitSurface(Leg_Entete, NULL, fenetre, &Bg_Pos);
	SDL_FreeSurface(Leg_Entete);


	SDL_Surface *Surf_Transparente = NULL;
	Surf_Transparente = SDL_CreateRGBSurface(SDL_HWSURFACE, 600, 390, 32, 0, 0, 0, 0);
	SDL_FillRect(Surf_Transparente, NULL, SDL_MapRGB(fenetre->format, 255, 0, 0));
	SDL_Rect Pos_Trans;
	Pos_Trans.x = 300;
	Pos_Trans.y = 180;

	SDL_Surface *Limite_Gauche = NULL, *Limite_Droite = NULL, *Limite_Bas = NULL;
	SDL_Rect Position;
	Position.x = 300;
	Position.y = 70;
	Limite_Gauche = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 500, 32, 0, 0, 0, 0);
	Limite_Droite = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 500, 32, 0, 0, 0, 0);
	Limite_Bas = SDL_CreateRGBSurface(SDL_HWSURFACE, 600, 1, 32, 0, 0, 0, 0);
	SDL_BlitSurface(Limite_Gauche, NULL, fenetre, &Position);
	SDL_FreeSurface(Limite_Gauche);
	Position.x += 600;
	SDL_BlitSurface(Limite_Droite, NULL, fenetre, &Position);
	SDL_FreeSurface(Limite_Droite);
	Position.x -= 600;
	Position.y += 500;
	SDL_BlitSurface(Limite_Bas, NULL, fenetre, &Position);
	SDL_FreeSurface(Limite_Bas);

	SDL_Surface *Quit = NULL;
	SDL_Rect Pos_Quit;
	Pos_Quit.x = 880;
	Pos_Quit.y = 70;
	Quit = IMG_Load("images/tn_ferme.jpg");
	SDL_BlitSurface(Quit, NULL, fenetre, &Pos_Quit);
	SDL_FreeSurface(Quit);

	SDL_Surface *Nom_Med = NULL, *Surf_Nom_Med = NULL, *next = NULL;
	SDL_Rect Pos_Nom_Med;
	Pos_Nom_Med.x = 350;
	Pos_Nom_Med.y = 90;
	TTF_Font *arial_14 = TTF_OpenFont("polices/arial.ttf", 14);
	SDL_Color noir = {0, 0, 0};
	Nom_Med = TTF_RenderText_Blended(arial_14, "Indiquez ci-dessous le nom du medecin pour lequel vous creez le rendez-vous", noir);
	Surf_Nom_Med = SDL_CreateRGBSurface(SDL_HWSURFACE, 150, 1, 32, 0, 0, 0, 0);
	SDL_BlitSurface(Nom_Med, NULL, fenetre, &Pos_Nom_Med);
	Pos_Nom_Med.y += 70;
	Pos_Nom_Med.x += 100;
	SDL_BlitSurface(Surf_Nom_Med, NULL, fenetre, &Pos_Nom_Med);
	SDL_FreeSurface(Nom_Med);
	SDL_FreeSurface(Surf_Nom_Med);

	next = IMG_Load("images/suivant.png");
	Pos_Nom_Med.x += 160;
	Pos_Nom_Med.y -= 30;
	SDL_SetColorKey(next, SDL_SRCCOLORKEY, SDL_MapRGB(fenetre->format, 255, 255, 255));
	SDL_BlitSurface(next, NULL, fenetre, &Pos_Nom_Med);
	SDL_FreeSurface(next);

	/*-------------Informations Patients-----------------------*/
	SDL_Surface *Nom_Patient = NULL, *Prenom_Patient = NULL, *Age_Patient = NULL, *F = NULL, *H = NULL,
	*Traitement = NULL, *Rv_Patient = NULL, *Info_Patient = NULL;
	SDL_Rect Pos_Info_Patient;
	Info_Patient = IMG_Load("images/inf_patient.png");
	SDL_SetColorKey(Info_Patient, SDL_SRCCOLORKEY, SDL_MapRGB(fenetre->format, 255, 255, 255));
	Pos_Info_Patient.x = 320;
	Pos_Info_Patient.y = 190;
	SDL_BlitSurface(Info_Patient, NULL, fenetre, &Pos_Info_Patient);
	SDL_FreeSurface(Info_Patient);
	Pos_Info_Patient.x = 310;
	Pos_Info_Patient.y = 250;
	Nom_Patient = TTF_RenderText_Blended(arial_14, "Nom", noir);
	Prenom_Patient = TTF_RenderText_Blended(arial_14, "Prenom", noir);
	Age_Patient = TTF_RenderText_Blended(arial_14, "Age", noir);
	Traitement = TTF_RenderText_Blended(arial_14, "Traitement", noir);
	F = TTF_RenderText_Blended(arial_14, "Femme", noir);
	H = TTF_RenderText_Blended(arial_14, "Homme", noir);
	SDL_BlitSurface(Nom_Patient, NULL, fenetre, &Pos_Info_Patient);
	Pos_Info_Patient.x += 250;
	SDL_BlitSurface(Prenom_Patient, NULL, fenetre, &Pos_Info_Patient);
	Pos_Info_Patient.x -= 250;
	Pos_Info_Patient.y += 40;
	SDL_BlitSurface(Age_Patient, NULL, fenetre, &Pos_Info_Patient);
	Pos_Info_Patient.x += 250;
	SDL_BlitSurface(F, NULL, fenetre, &Pos_Info_Patient);
	Pos_Info_Patient.x += 100;
	SDL_BlitSurface(H, NULL, fenetre, &Pos_Info_Patient);
	Pos_Info_Patient.x -= 350;
	Pos_Info_Patient.y += 40;
	SDL_BlitSurface(Traitement, NULL, fenetre, &Pos_Info_Patient);
	SDL_FreeSurface(Nom_Patient);
	SDL_FreeSurface(Prenom_Patient);
	SDL_FreeSurface(Age_Patient);
	SDL_FreeSurface(Traitement);

	SDL_Surface *Surf_Nom_Patient = NULL, *Surf_Prenom_Patient = NULL, *Surf_Age_Patient = NULL, *Surf_Traite_Patient = NULL,
	*Surf_F = NULL, *Surf_H = NULL;
	SDL_Rect Pos_Surf_Inf_Patient;
	Pos_Surf_Inf_Patient.x = 400;
	Pos_Surf_Inf_Patient.y = 250;
	Surf_Nom_Patient = SDL_CreateRGBSurface(SDL_HWSURFACE, 150, 30, 32, 0, 0, 0, 0);
	SDL_FillRect(Surf_Nom_Patient, NULL, SDL_MapRGB(fenetre->format, 210, 240, 121));
	Surf_Prenom_Patient = SDL_CreateRGBSurface(SDL_HWSURFACE, 150, 30, 32, 0, 0, 0, 0);
	SDL_FillRect(Surf_Prenom_Patient, NULL, SDL_MapRGB(fenetre->format, 210, 240, 121));
	Surf_Age_Patient = SDL_CreateRGBSurface(SDL_HWSURFACE, 50, 30, 32, 0, 0, 0, 0);
	SDL_FillRect(Surf_Age_Patient, NULL, SDL_MapRGB(fenetre->format, 210, 240, 121));
	Surf_Traite_Patient = SDL_CreateRGBSurface(SDL_HWSURFACE, 200, 30, 32, 0, 0, 0, 0);
	SDL_FillRect(Surf_Traite_Patient, NULL, SDL_MapRGB(fenetre->format, 210, 240, 121));
	Surf_F = SDL_CreateRGBSurface(SDL_HWSURFACE, 20, 20, 32, 0, 0, 0, 0);
	SDL_FillRect(Surf_F, NULL, SDL_MapRGB(fenetre->format, 210, 240, 121));
	Surf_H = SDL_CreateRGBSurface(SDL_HWSURFACE, 20, 20, 32, 0, 0, 0, 0);
	SDL_FillRect(Surf_H, NULL, SDL_MapRGB(fenetre->format, 210, 240, 121));

	SDL_BlitSurface(Surf_Nom_Patient, NULL, fenetre, &Pos_Surf_Inf_Patient);
	Pos_Surf_Inf_Patient.x += 220;
	SDL_BlitSurface(Surf_Prenom_Patient, NULL, fenetre, &Pos_Surf_Inf_Patient);
	Pos_Surf_Inf_Patient.x -= 220;
	Pos_Surf_Inf_Patient.y += 40;
	SDL_BlitSurface(Surf_Age_Patient, NULL, fenetre, &Pos_Surf_Inf_Patient);
	Pos_Surf_Inf_Patient.x += 220;
	SDL_BlitSurface(Surf_F, NULL, fenetre, &Pos_Surf_Inf_Patient);
	Pos_Surf_Inf_Patient.x += 100;
	SDL_BlitSurface(Surf_H, NULL, fenetre, &Pos_Surf_Inf_Patient);
	Pos_Surf_Inf_Patient.x -= 320;
	Pos_Surf_Inf_Patient.y += 40;
	SDL_BlitSurface(Surf_Traite_Patient, NULL, fenetre, &Pos_Surf_Inf_Patient);

	SDL_FreeSurface(Surf_Nom_Patient);
	SDL_FreeSurface(Surf_Prenom_Patient);
	SDL_FreeSurface(Surf_Age_Patient);
	SDL_FreeSurface(Surf_F);
	SDL_FreeSurface(Surf_H);
	SDL_FreeSurface(Surf_Traite_Patient);

	SDL_Surface *Disponibilite = NULL;
	SDL_Rect Pos_Dispo;
	Disponibilite = IMG_Load("images/date_rv.png");
	SDL_SetColorKey(Disponibilite, SDL_SRCCOLORKEY, SDL_MapRGB(fenetre->format, 255, 255, 255));
	Pos_Dispo.x = 320;
	Pos_Dispo.y = 380;
	SDL_BlitSurface(Disponibilite, NULL, fenetre, &Pos_Dispo);
	SDL_FreeSurface(Disponibilite);

	SDL_Surface *Suivant = NULL, *Precedent = NULL;
	SDL_Rect Pos_SuivPrec;
	Pos_SuivPrec.x = 350;
	Pos_SuivPrec.y = 460;
	Suivant = IMG_Load("images/suiv.png");
	Precedent = IMG_Load("images/prec.png");
	SDL_BlitSurface(Precedent, NULL, fenetre, &Pos_SuivPrec);
	Pos_SuivPrec.x += 300;
	SDL_BlitSurface(Suivant, NULL, fenetre, &Pos_SuivPrec);
	SDL_FreeSurface(Suivant);
	SDL_FreeSurface(Precedent);

	SDL_Surface *Valider = NULL;
	Valider = IMG_Load("images/creerp.png");
	SDL_SetColorKey(Valider, SDL_SRCCOLORKEY, SDL_MapRGB(fenetre->format, 255, 255, 255));
	Pos_SuivPrec.x += 150;
	Pos_SuivPrec.y += 70;
	SDL_BlitSurface(Valider, NULL, fenetre, &Pos_SuivPrec);
	SDL_FreeSurface(Valider);

	SDL_Surface *Saisi_Nom_Med = NULL;
	TTF_Font *arial_20 = TTF_OpenFont("polices/arial.ttf", 20);
	char Doctor_Name[50] = "----------";
	SDL_Color gris = {195, 195, 195};
	Saisi_Nom_Med = TTF_RenderText_Blended(arial_20, Doctor_Name, gris);
	Pos_Nom_Med.y += 10;
	Pos_Nom_Med.x -= 160;

	SDL_Surface *Saisi_Nom = NULL, *Saisi_Prenom = NULL, *Saisi_Age = NULL, *Saisi_Sexe = NULL, *Saisi_Traitement = NULL, *Saisi_Rv = NULL;
	SDL_Rect Pos_Nom, Pos_Prenom, Pos_Sexe, Pos_Traitement, Pos_Age, Pos_RV;
	Pos_Nom.x = 400;Pos_Nom.y = 265;
	Pos_Prenom.x = 620;Pos_Prenom.y = 265;
	Pos_Age.x = 400;Pos_Age.y = 305;
	Pos_Traitement.x = 400;Pos_Traitement.y = 345;
	Pos_RV.x = 420; Pos_RV.y = 465;

	char Dossier_Dispo[50] = "Medecins/", chiffre[5] = "", Date_Rv[50] = "";
	Rendez_Vous rv;
	FILE *file = NULL;
	strcat(Dossier_Dispo, Medecin);
	strcat(Dossier_Dispo, "/disponibilites/dispo");
	sprintf(chiffre, "%d", *compteur);
	strcat(Dossier_Dispo, chiffre);
	strcat(Dossier_Dispo, ".bin");
	file = fopen(Dossier_Dispo, "rb");
	if(file != NULL){
		fread(&rv, sizeof(Rendez_Vous), 1, file);
		patient.rv = rv;
		fclose(file);
		sprintf(Date_Rv, "Le %d/%d/%d à %dh %dmin", rv.jours, rv.mois, rv.annee, rv.heure, rv.minutes);
	}else{
		if(*Nbr_Dispo == 0){
			strcpy(Date_Rv, "Aucune disponibilite");
		}
		fclose(file);
	}
	

	char chaine_Nom[50] = "", chaine_Prenom[50] = "", chaine_Age[50] = "", chaine_Traitement[50] = "", chaine_sexe[50] = "";

	char dossier[50] = "Medecins/", dossier_rv[50] = "Medecins/", nombre_rv[5] = "", Note_Rv[50] = "Medecins/";
	strcat(dossier, Medecin);
	strcat(dossier, "/identifiant.bin");
	FILE* fichier = NULL, *fichier_rv = NULL;
	fichier = fopen(dossier, "rb");
	FILE *NoteRv = NULL;

	int repeat = 0;
	SDL_Surface *alert = NULL;
	SDL_Rect Pos_alert;
	SDL_Color rouge = {255, 0, 0}, verte = {34, 177, 76};
	Pos_alert.x = 420;Pos_alert.y = 490;

	switch(Bout_Appuye){
		case NOM_MED:
			strcpy(Doctor_Name, Medecin);
			strcat(Doctor_Name, "|");
			Saisi_Nom_Med = TTF_RenderText_Blended(arial_14, Doctor_Name, noir);
			if(fichier != NULL){
				SDL_SetAlpha(Surf_Transparente, SDL_SRCALPHA, 0);
				Saisi_Sexe = IMG_Load("images/tick.png");
				Saisi_Prenom = TTF_RenderText_Blended(arial_14, patient.prenom, noir);
				Saisi_Nom = TTF_RenderText_Blended(arial_14, patient.nom, noir);
				Saisi_Age = TTF_RenderText_Blended(arial_14, patient.age, noir);
				Saisi_Traitement = TTF_RenderText_Blended(arial_14, patient.traitement, noir);
				Saisi_Rv = TTF_RenderText_Blended(arial_14, Date_Rv, noir);
			}else
				SDL_SetAlpha(Surf_Transparente, SDL_SRCALPHA, 100);
			break;
		case NOM_PATIENT:
			Saisi_Nom_Med = TTF_RenderText_Blended(arial_14, Medecin, noir);
			if(fichier != NULL){
				SDL_SetAlpha(Surf_Transparente, SDL_SRCALPHA, 0);
			}else
				SDL_SetAlpha(Surf_Transparente, SDL_SRCALPHA, 100);

			if(fichier != NULL){
				strcpy(chaine_Nom, patient.nom);
				strcat(chaine_Nom, "|");
				Saisi_Sexe = IMG_Load("images/tick.png");
				Saisi_Prenom = TTF_RenderText_Blended(arial_14, patient.prenom, noir);
				Saisi_Nom = TTF_RenderText_Blended(arial_14, chaine_Nom, noir);
				Saisi_Age = TTF_RenderText_Blended(arial_14, patient.age, noir);
				Saisi_Traitement = TTF_RenderText_Blended(arial_14, patient.traitement, noir);
				Saisi_Rv = TTF_RenderText_Blended(arial_14, Date_Rv, noir);
			}
			break;
		case PRENOM_PATIENT:
			Saisi_Nom_Med = TTF_RenderText_Blended(arial_14, Medecin, noir);
			if(fichier != NULL){
				SDL_SetAlpha(Surf_Transparente, SDL_SRCALPHA, 0);
			}else
				SDL_SetAlpha(Surf_Transparente, SDL_SRCALPHA, 100);
			if(fichier != NULL){
				strcpy(chaine_Prenom, patient.prenom);
				strcat(chaine_Prenom, "|");
				Saisi_Sexe = IMG_Load("images/tick.png");
				Saisi_Age = TTF_RenderText_Blended(arial_14, patient.age, noir);
				Saisi_Nom = TTF_RenderText_Blended(arial_14, patient.nom, noir);
				Saisi_Prenom = TTF_RenderText_Blended(arial_14, chaine_Prenom, noir);
				Saisi_Traitement = TTF_RenderText_Blended(arial_14, patient.traitement, noir);
				Saisi_Rv = TTF_RenderText_Blended(arial_14, Date_Rv, noir);
			}
			break;
		case AGE_PATIENT:
			Saisi_Nom_Med = TTF_RenderText_Blended(arial_14, Medecin, noir);
			if(fichier != NULL){
				SDL_SetAlpha(Surf_Transparente, SDL_SRCALPHA, 0);
			}else
				SDL_SetAlpha(Surf_Transparente, SDL_SRCALPHA, 100);
			if(fichier != NULL){
				strcpy(chaine_Age, patient.age);
				strcat(chaine_Age, "|");
				Saisi_Sexe = IMG_Load("images/tick.png");
				Saisi_Prenom = TTF_RenderText_Blended(arial_14, patient.prenom, noir);
				Saisi_Nom = TTF_RenderText_Blended(arial_14, patient.nom, noir);
				Saisi_Age = TTF_RenderText_Blended(arial_14, chaine_Age, noir);
				Saisi_Traitement = TTF_RenderText_Blended(arial_14, patient.traitement, noir);
				Saisi_Rv = TTF_RenderText_Blended(arial_14, Date_Rv, noir);
			}
			break;
		case TRAITEMENT:
			Saisi_Nom_Med = TTF_RenderText_Blended(arial_14, Medecin, noir);
			if(fichier != NULL){
				SDL_SetAlpha(Surf_Transparente, SDL_SRCALPHA, 0);
			}else
				SDL_SetAlpha(Surf_Transparente, SDL_SRCALPHA, 100);
			if(fichier != NULL){
				strcpy(chaine_Traitement, patient.traitement);
				strcat(chaine_Traitement, "|");
				Saisi_Sexe = IMG_Load("images/tick.png");
				Saisi_Prenom = TTF_RenderText_Blended(arial_14, patient.prenom, noir);
				Saisi_Nom = TTF_RenderText_Blended(arial_14, patient.nom, noir);
				Saisi_Age = TTF_RenderText_Blended(arial_14, patient.age, noir);
				Saisi_Traitement = TTF_RenderText_Blended(arial_14, chaine_Traitement, noir);
				Saisi_Rv = TTF_RenderText_Blended(arial_14, Date_Rv, noir);
			}
			break;
		case FEMME:
			Saisi_Nom_Med = TTF_RenderText_Blended(arial_14, Medecin, noir);
			if(fichier != NULL){
				SDL_SetAlpha(Surf_Transparente, SDL_SRCALPHA, 0);
			}else
				SDL_SetAlpha(Surf_Transparente, SDL_SRCALPHA, 100);
			if(fichier != NULL){
				Saisi_Sexe = IMG_Load("images/tick.png");
				Saisi_Prenom = TTF_RenderText_Blended(arial_14, patient.prenom, noir);
				Saisi_Nom = TTF_RenderText_Blended(arial_14, patient.nom, noir);
				Saisi_Age = TTF_RenderText_Blended(arial_14, patient.age, noir);
				Saisi_Traitement = TTF_RenderText_Blended(arial_14, patient.traitement, noir);
				Saisi_Rv = TTF_RenderText_Blended(arial_14, Date_Rv, noir);
			}
			break;
		case HOMME:
			Saisi_Nom_Med = TTF_RenderText_Blended(arial_14, Medecin, noir);
			if(fichier != NULL){
				SDL_SetAlpha(Surf_Transparente, SDL_SRCALPHA, 0);
			}else
				SDL_SetAlpha(Surf_Transparente, SDL_SRCALPHA, 100);
			if(fichier != NULL){
				Saisi_Sexe = IMG_Load("images/tick.png");
				Saisi_Prenom = TTF_RenderText_Blended(arial_14, patient.prenom, noir);
				Saisi_Nom = TTF_RenderText_Blended(arial_14, patient.nom, noir);
				Saisi_Age = TTF_RenderText_Blended(arial_14, patient.age, noir);
				Saisi_Traitement = TTF_RenderText_Blended(arial_14, patient.traitement, noir);
				Saisi_Rv = TTF_RenderText_Blended(arial_14, Date_Rv, noir);
			}
			break;
		case RV_PRECEDENT:
			Saisi_Nom_Med = TTF_RenderText_Blended(arial_14, Medecin, noir);
			if(fichier != NULL){
				SDL_SetAlpha(Surf_Transparente, SDL_SRCALPHA, 0);
			}else
				SDL_SetAlpha(Surf_Transparente, SDL_SRCALPHA, 100);
			if(fichier != NULL){
				Saisi_Sexe = IMG_Load("images/tick.png");
				Saisi_Prenom = TTF_RenderText_Blended(arial_14, patient.prenom, noir);
				Saisi_Nom = TTF_RenderText_Blended(arial_14, patient.nom, noir);
				Saisi_Age = TTF_RenderText_Blended(arial_14, patient.age, noir);
				Saisi_Traitement = TTF_RenderText_Blended(arial_14, patient.traitement, noir);
				Saisi_Rv = TTF_RenderText_Blended(arial_14, Date_Rv, noir);
			}
			break;
		case RV_SUIVANT:
			Saisi_Nom_Med = TTF_RenderText_Blended(arial_14, Medecin, noir);
			if(fichier != NULL){
				SDL_SetAlpha(Surf_Transparente, SDL_SRCALPHA, 0);
			}else
				SDL_SetAlpha(Surf_Transparente, SDL_SRCALPHA, 100);
			if(fichier != NULL){
				Saisi_Sexe = IMG_Load("images/tick.png");
				Saisi_Prenom = TTF_RenderText_Blended(arial_14, patient.prenom, noir);
				Saisi_Nom = TTF_RenderText_Blended(arial_14, patient.nom, noir);
				Saisi_Age = TTF_RenderText_Blended(arial_14, patient.age, noir);
				Saisi_Traitement = TTF_RenderText_Blended(arial_14, patient.traitement, noir);
				Saisi_Rv = TTF_RenderText_Blended(arial_14, Date_Rv, noir);
			}
			break;
		case AUCUN_BOUT_CP:
			if(strcmp(Medecin, "") == 0){
				Saisi_Nom_Med = TTF_RenderText_Blended(arial_20, "---------", gris);
			}else
				Saisi_Nom_Med = TTF_RenderText_Blended(arial_14, Medecin, noir);
	
			if(fichier != NULL){
				SDL_SetAlpha(Surf_Transparente, SDL_SRCALPHA, 0);
				Saisi_Sexe = IMG_Load("images/tick.png");
				Saisi_Prenom = TTF_RenderText_Blended(arial_14, patient.prenom, noir);
				Saisi_Nom = TTF_RenderText_Blended(arial_14, patient.nom, noir);
				Saisi_Age = TTF_RenderText_Blended(arial_14, patient.age, noir);
				Saisi_Traitement = TTF_RenderText_Blended(arial_14, patient.traitement, noir);
				Saisi_Rv = TTF_RenderText_Blended(arial_14, Date_Rv, noir);
			}else
				SDL_SetAlpha(Surf_Transparente, SDL_SRCALPHA, 100);
			break;
		case CP_BOUT_VALIDE:
			if(strcmp(Medecin, "") == 0){
				Saisi_Nom_Med = TTF_RenderText_Blended(arial_20, "---------", gris);
			}else
				Saisi_Nom_Med = TTF_RenderText_Blended(arial_14, Medecin, noir);
	
			if(fichier != NULL){
				SDL_SetAlpha(Surf_Transparente, SDL_SRCALPHA, 0);
				Saisi_Sexe = IMG_Load("images/tick.png");
				Saisi_Prenom = TTF_RenderText_Blended(arial_14, patient.prenom, noir);
				Saisi_Nom = TTF_RenderText_Blended(arial_14, patient.nom, noir);
				Saisi_Age = TTF_RenderText_Blended(arial_14, patient.age, noir);
				Saisi_Traitement = TTF_RenderText_Blended(arial_14, patient.traitement, noir);
				Saisi_Rv = TTF_RenderText_Blended(arial_14, Date_Rv, noir);

				repeat = If_Rv_Repeat(Medecin, *Nbr_Rv, patient);
				if(repeat == 0){
					if(strcmp(patient.nom, "") != 0 && strcmp(patient.prenom, "") != 0 && strcmp(patient.age, "") != 0 &&
						strcmp(patient.traitement, "") != 0 && patient.sexe != 'R'){
						*Nbr_Rv += 1;
						strcat(dossier_rv, Medecin);
						strcat(dossier_rv, "/RendezVous/rv");
						sprintf(nombre_rv, "%d", *Nbr_Rv);
						strcat(dossier_rv, nombre_rv);
						strcat(dossier_rv, ".bin");
						fichier_rv = fopen(dossier_rv, "wb");
						strcat(Note_Rv, Medecin);
						strcat(Note_Rv, "/nbr_rv.bin");
						NoteRv = fopen(Note_Rv, "wb");
						fwrite(Nbr_Rv, sizeof(int), 1, NoteRv);
						fclose(NoteRv);
						fwrite(&patient, sizeof(Patient), 1, fichier_rv);
						fclose(fichier_rv);
						alert = TTF_RenderText_Blended(arial_12, "Created successfuly", verte);
					}else{
						alert = TTF_RenderText_Blended(arial_12, "Empty fields", rouge);
					}
				}else if(repeat == 1){
					alert = TTF_RenderText_Blended(arial_12, "Created", verte);
				}else if(repeat == 2){
					alert = TTF_RenderText_Blended(arial_12, "Date used", rouge);
				}else if(repeat == 3){
					alert = TTF_RenderText_Blended(arial_12, "Has already an appointement", rouge);
				}
				SDL_BlitSurface(alert, NULL, fenetre, &Pos_alert);
				SDL_Delay(200);
			}else
				SDL_SetAlpha(Surf_Transparente, SDL_SRCALPHA, 100);
			break;
	}
	fclose(fichier);
	if(patient.sexe == 'M'){
		Pos_Sexe.x = 720;Pos_Sexe.y = 290;
	}else if(patient.sexe == 'F'){
		Pos_Sexe.x = 620;Pos_Sexe.y = 290;
	}
	SDL_BlitSurface(Saisi_Nom, NULL, fenetre, &Pos_Nom);
	SDL_BlitSurface(Saisi_Rv, NULL, fenetre, &Pos_RV);
	SDL_BlitSurface(Saisi_Traitement, NULL, fenetre, &Pos_Traitement);
	SDL_BlitSurface(Saisi_Sexe, NULL, fenetre, &Pos_Sexe);
	SDL_BlitSurface(Saisi_Prenom, NULL, fenetre, &Pos_Prenom);
	SDL_BlitSurface(Saisi_Age, NULL, fenetre, &Pos_Age);
	SDL_BlitSurface(Saisi_Nom_Med, NULL, fenetre, &Pos_Nom_Med);
	SDL_FreeSurface(Saisi_Nom_Med);
	SDL_FreeSurface(Saisi_Rv);
	SDL_FreeSurface(Saisi_Traitement);
	SDL_FreeSurface(Saisi_Age);
	SDL_FreeSurface(Saisi_Prenom);
	SDL_FreeSurface(Saisi_Sexe);
	SDL_FreeSurface(Saisi_Nom);
	SDL_FreeSurface(alert);

	SDL_BlitSurface(Surf_Transparente, NULL, fenetre, &Pos_Trans);
	SDL_FreeSurface(Surf_Transparente);
	TTF_CloseFont(arial_12);
	TTF_CloseFont(arial_20);
	TTF_CloseFont(arial_14);
}
void Create_RV(SDL_Surface *fenetre, Bout_CreerPatient_Sec Bout_App, char Med_Pour_Rv[50], Patient patient, int *compteur,
	int *Nbr_Rv, int *Nbr_Dispo){
	Creer_Patient(fenetre, Bout_App, Med_Pour_Rv, patient, compteur, Nbr_Rv, Nbr_Dispo);
}

void Affiche_Rv_Sec(SDL_Surface* fenetre, int Nbr_Rv, char med[50]){
	SDL_Surface **Surface = {NULL}, *date = NULL, *heure = NULL, *Verticale = NULL, *Horizontale = NULL;
	char dossier[50] = "", chaine_Date[50] = "", chaine_heure[50] = "";
	SDL_Rect *Position;
	Surface = malloc(sizeof(SDL_Surface)*Nbr_Rv);
	Position = malloc(sizeof(SDL_Rect)*Nbr_Rv);
	int i;
	Verticale = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 50, 32, 0, 0, 0, 0);
	Horizontale = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 1, 32, 0, 0, 0, 0);
	SDL_Color Noir = {0, 0, 0};
	TTF_Font *arial = TTF_OpenFont("polices/arial.ttf", 12);
	char chiffre[5] = "";
	FILE *fichier = NULL;
	Patient p;
	for(i=0; i < Nbr_Rv; i++){
		strcpy(dossier, "");
		strcpy(dossier, "Medecins/");
		strcat(dossier, med);
		strcat(dossier, "/RendezVous/rv");
		sprintf(chiffre, "%d", i+1);
		strcat(dossier, chiffre);
		strcat(dossier, ".bin");
		if(i==0){
			Position[i].x = 500;
			Position[i].y = 30;
		}else if(i==5 || i==10 || i==15 || i==20){
			Position[i].x = Position[0].x;
			if(i==5){
				Position[i].y = Position[0].y + 51;
			}else if(i==10)
				Position[i].y = Position[0].y + 2*51;
			else if(i==15)
				Position[i].y = Position[0].y + 51*3;
			else
				Position[i].y = Position[0].y + 51*4;
		}else{
			Position[i].x = Position[i-1].x + 100 + 1;
			Position[i].y = Position[i-1].y;
		}
		Surface[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 60, 32, 0, 0, 0, 0);
		SDL_FillRect(Surface[i], NULL, SDL_MapRGB(fenetre->format, 255, 255, 0));
		fichier = fopen(dossier, "rb");
		if(fichier != NULL){
			fread(&p, sizeof(Patient), 1, fichier);
			fclose(fichier);
			sprintf(chaine_Date, "Le %d/%d/%d", p.rv.jours, p.rv.mois, p.rv.annee);
			sprintf(chaine_heure, "a %d h %d min", p.rv.heure, p.rv.minutes);
			date = TTF_RenderText_Blended(arial, chaine_Date, Noir);
			heure = TTF_RenderText_Blended(arial, chaine_heure, Noir);
			SDL_BlitSurface(Surface[i], NULL, fenetre, &Position[i]);
			Position[i].x += 10;
			Position[i].y += 10;
			SDL_BlitSurface(date, NULL, fenetre, &Position[i]);
			Position[i].x +=5;
			Position[i].y += 15;
			SDL_BlitSurface(heure, NULL, fenetre, &Position[i]);
			Position[i].x -= 15;
			Position[i].y -= 25;
			SDL_BlitSurface(Verticale, NULL, fenetre, &Position[i]);
			Position[i].y += 50;
			SDL_BlitSurface(Horizontale, NULL, fenetre, &Position[i]);
		}else{
			fclose(fichier);
		}
		Position[i].y -= 50;
		SDL_FreeSurface(date);
		SDL_FreeSurface(heure);
	}
	for(i=0 ; i < Nbr_Rv; i++){
		SDL_FreeSurface(Surface[i]);
	}
	SDL_FreeSurface(Verticale);
	SDL_FreeSurface(Horizontale);
	TTF_CloseFont(arial);
	free(Surface);
	free(Position);
}

void Voir_Rv_Sec(SDL_Surface* fenetre, int *Nbr_Rv, Bout_VoirRv_Sec Bout_App, char med[50]){
	SDL_Surface *Surface = NULL, *quit = NULL, *En_tete = NULL, *Text_entete = NULL;
	SDL_Rect Pos_Surface, Pos_Quit;
	TTF_Font *police = TTF_OpenFont("polices/police.ttf", 12);
	SDL_Color Blanc = {255, 255, 255};
	Pos_Surface.x = 250;
	Pos_Surface.y = 10;
	Pos_Quit.x = 1130;
	Pos_Quit.y = 10;
	En_tete = SDL_CreateRGBSurface(SDL_HWSURFACE, 900, 20, 32, 0, 0, 0, 0);
	Surface = SDL_CreateRGBSurface(SDL_HWSURFACE, 900, 600, 32, 0, 0, 0, 0);
	SDL_FillRect(Surface, NULL, SDL_MapRGB(fenetre->format, 74, 177, 76));
	SDL_BlitSurface(Surface, NULL, fenetre, &Pos_Surface);
	SDL_BlitSurface(En_tete, NULL, fenetre, &Pos_Surface);
	quit = IMG_Load("images/ferme.jpg");
	SDL_BlitSurface(quit, NULL, fenetre, &Pos_Quit);
	Text_entete = TTF_RenderText_Blended(police, "Les rendez-vous crees", Blanc);
	Pos_Surface.x += 400;
	Pos_Surface.y += 5;
	SDL_BlitSurface(Text_entete, NULL, fenetre, &Pos_Surface);
	SDL_FreeSurface(Surface);
	SDL_FreeSurface(quit);
	SDL_FreeSurface(En_tete);
	SDL_FreeSurface(Text_entete);

	SDL_Surface *medecin = NULL, *texte = NULL;
	SDL_Rect Pos_med;
	Pos_med.x = 260;
	Pos_med.y = 250;
	SDL_Color Noir = {0, 0, 0};
	Text_entete = TTF_RenderText_Blended(police, "Du medecin : ", Noir);
	medecin = SDL_CreateRGBSurface(SDL_HWSURFACE, 150, 1, 32, 0, 0, 0, 0);
	SDL_FillRect(medecin, NULL, SDL_MapRGB(fenetre->format, 0, 255, 0));
	SDL_BlitSurface(Text_entete, NULL, fenetre, &Pos_med);
	Pos_med.y += 50;
	SDL_BlitSurface(medecin, NULL, fenetre, &Pos_med);
	SDL_FreeSurface(medecin);
	SDL_FreeSurface(texte);

	SDL_Surface *Surf_Nom_med = NULL;
	TTF_Font *arial_14 = TTF_OpenFont("polices/arial.ttf", 14);
	SDL_Rect Pos_Saisi_Med;
	Pos_Saisi_Med.x = 260;
	Pos_Saisi_Med.y = 285;
	char saisi_med[50] = "";

	switch(Bout_App){
		case MED_NOM:
			strcat(saisi_med, med);
			strcat(saisi_med, "|");
			Surf_Nom_med = TTF_RenderText_Blended(arial_14, saisi_med, Noir);
			break;
		default:
			Surf_Nom_med = TTF_RenderText_Blended(arial_14, med, Noir);
			break;
	}

	SDL_BlitSurface(Surf_Nom_med, NULL, fenetre, &Pos_Saisi_Med);
	if(strcmp(med, "") != 0){
		Affiche_Rv_Sec(fenetre, *Nbr_Rv, med);
	}
	SDL_FreeSurface(Surf_Nom_med);
	TTF_CloseFont(arial_14);
	TTF_CloseFont(police);
}

void Les_Bouttons(SDL_Surface* fenetre, Bout_Esp_Sec BoutSurv_Sec, Bout_Esp_Sec Bout_Appuye, Bout_Connect_Sec Bout_App_Connect, 
	Bout_Compte_Sec Bout_App_Compte, identifiant id, char masqueur1[50], char masqueur2[50], char verifie[50], int *connected,
	Bout_CreerPatient_Sec Bout_App_CP, char Med_Pour_Rv[50], Patient patient, int *Nbr_Rv, int *compteur, int *Nbr_Dispo,
	Bout_VoirRv_Sec BoutApp_VoirRV){
	SDL_Surface *Bout_Connecte = NULL, *Bout_Creer_Compte = NULL, *Bout_Creer_Patient = NULL, *Bout_Deconnecte = NULL,
	*Bout_Voir_Rv = NULL;
	SDL_Rect Pos_BC, Pos_BCC, Pos_BCP, Pos_BD, Pos_VRV;
	TTF_Font *police1, *police2;
	police1 = TTF_OpenFont("polices/arial.ttf", 12);
	police2 = TTF_OpenFont("polices/arial.ttf", 20);
	TTF_SetFontStyle(police2, TTF_STYLE_UNDERLINE | TTF_STYLE_ITALIC);
	SDL_Color aqua = {0, 255, 255}, verdatre = {74, 255, 165}, rouge = {255, 0, 0};
	switch(BoutSurv_Sec){
		case ESP_SEC_BOUT_CONNECTE:
			Bout_Voir_Rv = TTF_RenderText_Blended(police1, "Voir les rv", verdatre);
			Bout_Connecte = TTF_RenderText_Blended(police2, " Se connecter", aqua);
			Bout_Deconnecte = TTF_RenderText_Blended(police1, " Se deconnecter", rouge);
			Bout_Creer_Compte = TTF_RenderText_Blended(police1, "Creer votre Compte", verdatre);
			Bout_Creer_Patient = IMG_Load("images/crv.png");
			break;
		case ESP_SEC_BOUT_DECONNECTE:
			Bout_Connecte = TTF_RenderText_Blended(police1, " Se connecter", aqua);
			Bout_Deconnecte = TTF_RenderText_Blended(police2, " Se deconnecter", rouge);
			Bout_Creer_Compte = TTF_RenderText_Blended(police1, "Creer votre Compte", verdatre);
			Bout_Voir_Rv = TTF_RenderText_Blended(police1, "Voir les rv", verdatre);
			Bout_Creer_Patient = IMG_Load("images/crv.png");
			break;
		case ESP_SEC_BOUT_CREERCOMPTE:
			Bout_Connecte = TTF_RenderText_Blended(police1, " Se connecter", aqua);
			Bout_Deconnecte = TTF_RenderText_Blended(police1, " Se deconnecter", rouge);
			Bout_Creer_Compte = TTF_RenderText_Blended(police2, "Creer votre Compte", verdatre);
			Bout_Voir_Rv = TTF_RenderText_Blended(police1, "Voir les rv", verdatre);
			Bout_Creer_Patient = IMG_Load("images/crv.png");
			break;
		case ESP_SEC_BOUT_CREERRV:
			Bout_Creer_Patient = IMG_Load("images/creeRV.png");
			Bout_Connecte = TTF_RenderText_Blended(police1, " Se connecter", aqua);
			Bout_Deconnecte = TTF_RenderText_Blended(police1, " Se deconnecter", rouge);
			Bout_Voir_Rv = TTF_RenderText_Blended(police1, "Voir les rv", verdatre);
			Bout_Creer_Compte = TTF_RenderText_Blended(police1, "Creer votre Compte", verdatre);
			break;
		case ESP_SEC_BOUT_VOIRRV:
			Bout_Voir_Rv = TTF_RenderText_Blended(police2, "Voir les rv", verdatre);
			Bout_Creer_Patient = IMG_Load("images/crv.png");
			Bout_Connecte = TTF_RenderText_Blended(police1, " Se connecter", aqua);
			Bout_Deconnecte = TTF_RenderText_Blended(police1, " Se deconnecter", rouge);
			Bout_Creer_Compte = TTF_RenderText_Blended(police1, "Creer votre Compte", verdatre);
			break;
		default:
			Bout_Creer_Patient = IMG_Load("images/crv.png");
			Bout_Connecte = TTF_RenderText_Blended(police1, " Se connecter", aqua);
			Bout_Deconnecte = TTF_RenderText_Blended(police1, " Se deconnecter", rouge);
			Bout_Voir_Rv = TTF_RenderText_Blended(police1, "Voir les rv", verdatre);
			Bout_Creer_Compte = TTF_RenderText_Blended(police1, "Creer votre Compte", verdatre);
			break;
	}
	Pos_BC.x = 310;
	Pos_BC.y = 130;
	Pos_BD.x = 310;
	Pos_BD.y = 160;
	Pos_BCC.x = 310;
	Pos_BCC.y = 320;
	SDL_BlitSurface(Bout_Connecte, NULL, fenetre, &Pos_BC);
	SDL_BlitSurface(Bout_Deconnecte, NULL, fenetre, &Pos_BD);
	SDL_BlitSurface(Bout_Creer_Compte, NULL, fenetre, &Pos_BCC);
	Pos_BCP.x = 500;
	Pos_BCP.y = 380;
	Pos_VRV.x = 300;
	Pos_VRV.y = 400;
	SDL_BlitSurface(Bout_Creer_Patient, NULL, fenetre, &Pos_BCP);
	SDL_BlitSurface(Bout_Voir_Rv, NULL, fenetre, &Pos_VRV);

	SDL_FreeSurface(Bout_Creer_Compte);
	SDL_FreeSurface(Bout_Connecte);
	SDL_FreeSurface(Bout_Deconnecte);
	SDL_FreeSurface(Bout_Creer_Patient);
	SDL_FreeSurface(Bout_Voir_Rv);
	TTF_CloseFont(police1);
	TTF_CloseFont(police2); 

	//gestion des clics
	switch(Bout_Appuye){
		case ESP_SEC_BOUT_CONNECTE:
			if(Bout_App_Connect != BOUT_CONNECT_QUIT){
				Connexion_Sec(fenetre, Bout_App_Connect, id, masqueur1, connected);
			}
			break;
		case ESP_SEC_BOUT_DECONNECTE:
			if(*connected){
				*connected = 0;
			}
			break;
		case ESP_SEC_BOUT_CREERCOMPTE:
			if(Bout_App_Compte != BOUT_COMPTE_QUIT){
				Creation_Compte_Sec(fenetre, Bout_App_Compte, id, masqueur1, masqueur2, verifie);
			}
			break;
		case ESP_SEC_BOUT_CREERRV:
			if(*connected == 1 && Bout_App_CP != BOUT_CP_QUITTER){
				Create_RV(fenetre, Bout_App_CP, Med_Pour_Rv, patient, compteur, Nbr_Rv, Nbr_Dispo);
			}
			break;
		case ESP_SEC_BOUT_VOIRRV:
			if(*connected == 1 && BoutApp_VoirRV != BOUT_VRV_QUIT){
				Voir_Rv_Sec(fenetre, Nbr_Rv, BoutApp_VoirRV, Med_Pour_Rv);
			}
		case ESP_SEC_AUCUN:
			break;
	}
}

void Espace_Secretaire(SDL_Surface* fenetre, Bout_Esp_Sec BoutSurv_Sec, Bout_Esp_Sec BoutApp_Sec, Bout_Connect_Sec BoutApp_Connexion_Sec,
	Bout_Compte_Sec BoutApp_Compte_Sec, identifiant mes_id, char masqueur1[50], char masqueur2[50], char verifie[50], int *connected,
	Bout_CreerPatient_Sec BoutApp_CP, char Med_Pour_Rv[50], Patient Le_Patient, int *Nbr_Rv, int *compteur, int *Nbr_Dispo,
	Bout_VoirRv_Sec BoutApp_VoirRV){
	Zone_Alerte(fenetre);
	Texte_Accueille(fenetre);

	char le_dossier1[50] = "Medecins/", le_dossier2[50] = "Medecins/", dossier1[50] = "Medecins/";
	strcat(le_dossier1, Med_Pour_Rv);
	strcat(le_dossier1, "/RendezVous/rv1.bin");
	strcat(le_dossier2, Med_Pour_Rv);
	strcat(le_dossier2, "/nbr_rv.bin");
	strcat(dossier1, Med_Pour_Rv);
	strcat(dossier1, "/nbrDispo.bin");
	FILE *fichier = NULL, *Nbr_Rv_File = NULL, *file = NULL;

	if(*connected && strcmp(Med_Pour_Rv, "") != 0){
		fichier = fopen(le_dossier1, "rb");
		if(fichier == NULL){
			remove(le_dossier2);
			*Nbr_Rv = 0;
			fclose(fichier);
		}else
			fclose(fichier);

		Nbr_Rv_File = fopen(le_dossier2, "rb");
		if(Nbr_Rv_File == NULL){
			fclose(Nbr_Rv_File);
			Nbr_Rv_File = fopen(le_dossier2, "wb");
			fwrite(Nbr_Rv, sizeof(int), 1, Nbr_Rv_File);
			fclose(Nbr_Rv_File);
		}else{
			fread(Nbr_Rv, sizeof(int), 1, Nbr_Rv_File);
			fclose(Nbr_Rv_File);
		}

		file = fopen(dossier1, "rb");
		if(file != NULL){
			fread(Nbr_Dispo, sizeof(int), 1, file);
			fclose(file);
		}else
			fclose(file);
	}

	Les_Bouttons(fenetre, BoutSurv_Sec, BoutApp_Sec, BoutApp_Connexion_Sec, BoutApp_Compte_Sec, mes_id, masqueur1, masqueur2,
		verifie, connected, BoutApp_CP, Med_Pour_Rv, Le_Patient, Nbr_Rv, compteur, Nbr_Dispo, BoutApp_VoirRV);
}

//Les survoles dans laa zone secretaire gere ici gerer
Bout_Esp_Sec Bout_Survole_Sec(int abscisse, int ordonnee, int longueur, int largeur){
	if(abscisse > 310 && abscisse < 400 && ordonnee > 130 && ordonnee < 160){
		return ESP_SEC_BOUT_CONNECTE;
	}else if(abscisse > 310 && abscisse < 400 && ordonnee > 160 && ordonnee < 190){
		return ESP_SEC_BOUT_DECONNECTE;
	}else if(abscisse > 310 && abscisse < 410 && ordonnee > 320 && ordonnee < 350){
		return ESP_SEC_BOUT_CREERCOMPTE;
	}else if(abscisse > 500 && abscisse < 646 && ordonnee > 380 && ordonnee < 496){
		return ESP_SEC_BOUT_CREERRV;
	}else if(abscisse > 300 && abscisse < 400 && ordonnee > 400 && ordonnee < 430){
		return ESP_SEC_BOUT_VOIRRV;
	}else
		return ESP_SEC_AUCUN;
}

Bout_Esp_Sec Bout_Appuye_Sec(int abscisse, int ordonnee, Bout_Esp_Sec Boutton){
	if(abscisse > 310 && abscisse < 400 && ordonnee > 130 && ordonnee < 160){
		return ESP_SEC_BOUT_CONNECTE;
	}else if(abscisse > 310 && abscisse < 400 && ordonnee > 160 && ordonnee < 190){
		return ESP_SEC_BOUT_DECONNECTE;
	}else if(abscisse > 310 && abscisse < 410 && ordonnee > 320 && ordonnee < 350){
		return ESP_SEC_BOUT_CREERCOMPTE;
	}else if(abscisse > 500 && abscisse < 646 && ordonnee > 380 && ordonnee < 496){
		return ESP_SEC_BOUT_CREERRV;
	}else if(abscisse > 300 && abscisse < 400 && ordonnee > 400 && ordonnee < 430){
		return ESP_SEC_BOUT_VOIRRV;
	}else
		return Boutton;
}

Bout_VoirRv_Sec App_VoirRv_Sec(int abscisse, int ordonnee, Bout_VoirRv_Sec Boutton){
	if(abscisse > 1130 && abscisse < 1150 && ordonnee > 10 && ordonnee < 30){
		return BOUT_VRV_QUIT;
	}else if(abscisse > 260 && abscisse < 410 && ordonnee > 270 && ordonnee < 300){
		return MED_NOM;
	}else if(Boutton == BOUT_VRV_QUIT){
		return BOUT_VRV_RIEN;
	}else
		return Boutton;
}

Bout_Connect_Sec App_Connexion_Sec(int abscisse, int ordonnee, Bout_Connect_Sec Boutton){
	if(abscisse > 579 && abscisse < 749 && ordonnee > 165 && ordonnee < 195){
		return BOUT_CONNECT_NOM;
	}else if(abscisse > 629 && abscisse < 799 && ordonnee > 235 && ordonnee < 265){
		return BOUT_CONNECT_MDP;
	}else if(abscisse > 650 && abscisse < 721 && ordonnee > 300 && ordonnee < 340){
		return BOUT_CONNECT_OK;
	}else if(abscisse > 899 && abscisse < 919 && ordonnee > 130 && ordonnee < 150){
		return BOUT_CONNECT_QUIT;
	}else if(Boutton == BOUT_CONNECT_QUIT){
		return BOUT_CONNECT_RIEN;
	}else
		return Boutton;
}

Bout_Compte_Sec App_Compte_Sec(int abscisse, int ordonnee, Bout_Compte_Sec Boutton){
	if(abscisse > 579 && abscisse < 749 && ordonnee > 170 && ordonnee < 200){
		return BOUT_COMPTE_NOM;
	}else if(abscisse > 629 && abscisse < 799 && ordonnee > 210 && ordonnee < 240){
		return BOUT_COMPTE_MDP;
	}else if(abscisse > 679 && abscisse < 849 && ordonnee > 250 && ordonnee < 280){
		return BOUT_COMPTE_CMDP;
	}else if(abscisse > 689 && abscisse < 792 && ordonnee > 290 && ordonnee < 340){
		return BOUT_COMPTE_VALIDE;
	}else if(abscisse > 899 && abscisse < 919 && ordonnee > 130 && ordonnee < 150){
		return BOUT_COMPTE_QUIT;
	}else if(Boutton == BOUT_COMPTE_QUIT){
		return BOUT_COMPTE_RIEN;
	}else
		return Boutton;
}

Bout_CreerPatient_Sec Bout_AppCP_Sec(int abscisse, int ordonnee, Bout_CreerPatient_Sec Boutton){
	if(abscisse > 450 && abscisse < 600 && ordonnee > 130 && ordonnee < 160){
		return NOM_MED;
	}else if(abscisse > 610 && abscisse < 700 && ordonnee > 130 && ordonnee < 179){
		return CP_SUITE;
	}else if(abscisse > 880 && abscisse < 900 && ordonnee > 70 && ordonnee < 90){
		return BOUT_CP_QUITTER;
	}else if(abscisse > 400 && abscisse < 550 && ordonnee > 250 && ordonnee < 280){
		return NOM_PATIENT;
	}else if(abscisse > 620 && abscisse < 770 && ordonnee > 250 && ordonnee < 280){
		return PRENOM_PATIENT;
	}else if(abscisse > 400 && abscisse < 450 && ordonnee > 290 && ordonnee < 320){
		return AGE_PATIENT;
	}else if(abscisse > 620 && abscisse < 640 && ordonnee > 290 && ordonnee < 310){
		return FEMME;
	}else if(abscisse > 720 && abscisse < 740 && ordonnee > 290 && ordonnee < 310){
		return HOMME;
	}else if(abscisse > 400 && abscisse < 600 && ordonnee > 330 && ordonnee < 360){
		return TRAITEMENT;
	}else if(abscisse > 350 && abscisse < 377 && ordonnee > 460 && ordonnee < 487){
		return RV_PRECEDENT;
	}else if(abscisse > 650 && abscisse < 677 &&ordonnee > 460 && ordonnee < 487){
		return RV_SUIVANT;
	}else if(abscisse > 800 && abscisse < 900 && ordonnee > 530 && ordonnee < 570){
		return CP_BOUT_VALIDE;
	}else if(Boutton == BOUT_CP_QUITTER || Boutton == RV_SUIVANT || Boutton == RV_PRECEDENT){
		return AUCUN_BOUT_CP;
	}else{
		return Boutton;
	}
}

void Repousse_Supprime_Dispo(int nombre, int nombre_Dispo, char medecin[50]){
	int i;
	char dossier1[50] = "", dossier2[50] = "", chiff1[5] = "", chiff2[5] = "";
	Rendez_Vous rv1, rv2;
	FILE *fichier1 = NULL, *fichier2 = NULL;

	if(nombre_Dispo == 1){
		strcpy(dossier1, "Medecins/");
		strcat(dossier1, medecin);
		strcat(dossier1, "/disponibilites/dispo1.bin");
		remove(dossier1);
		break;
	}else if(nombre_Dispo == 0){
		break;
	}
	for(i=nombre; i< nombre_Dispo; i++){
		strcpy(dossier1, "");
		strcpy(dossier2, "");
		strcpy(dossier1, "Medecins/");
		strcpy(dossier2, "Medecins/");
		strcat(dossier1, medecin);
		strcat(dossier2, medecin);
		strcat(dossier1, "/disponibilites/dispo");
		strcat(dossier2, "/disponibilites/dispo");
		sprintf(chiff1, "%d", i);
		sprintf(chiff2, "%d", i + 1);
		strcat(dossier1, chiff1);
		strcat(dossier2, chiff2);
		strcat(dossier1, ".bin");
		strcat(dossier2, ".bin");
		fichier1 = fopen(dossier1, "rb");
		fichier2 = fopen(dossier2, "rb");
		if(fichier1 != NULL){
			fread(&rv1, sizeof(Rendez_Vous), 1, fichier1);
		}
		fclose(fichier1);
		fichier2 = fopen(dossier2, "rb");
		if(fichier2 != NULL){
			fread(&rv2, sizeof(Rendez_Vous), 1, fichier2);
		}
		fclose(fichier2);
		fichier1 = fopen(dossier1, "wb");
		fwrite(&rv2, sizeof(Rendez_Vous), 1, fichier1);
		fclose(fichier1);
		fichier2 = fopen(dossier2, "wb");
		fwrite(&rv1, sizeof(Rendez_Vous), 1, fichier2);
		fclose(fichier2);

		if(i == nombre_Dispo - 1)
			remove(dossier2);
	}
	nombre_Dispo--;
	char dossier_dispo[50] = "";
	FILE* file = NULL;
	strcpy(dossier_dispo, "Medecins/");
	strcat(dossier_dispo, medecin);
	strcat(dossier_dispo, "/nbrDispo.bin");
	file = fopen(dossier_dispo, "wb+");
	fwrite(&nombre_Dispo, sizeof(int), 1, file);
	fclose(file);
}

void Repousse_Supprime_Rv(int nombre, int nombre_Rv, char medecin[50]){
	int i;
	char dossier1[50] = "", dossier2[50] = "", chiff1[5] = "", chiff2[5] = "";
	Patient p1, p2;
	FILE *fichier1 = NULL, *fichier2 = NULL;
	for(i=nombre; i< nombre_Rv; i++){
		strcpy(dossier1, "Medecins/");
		strcpy(dossier2, "Medecins/");
		strcat(dossier1, medecin);
		strcat(dossier2, medecin);
		strcat(dossier1, "/RendezVous/rv");
		strcat(dossier2, "/RendezVous/rv");
		sprintf(chiff1, "%d", i);
		sprintf(chiff2, "%d", i + 1);
		strcat(dossier1, chiff1);
		strcat(dossier2, chiff2);
		strcat(dossier1, ".bin");
		strcat(dossier2, ".bin");
		fichier1 = fopen(dossier1, "rb");
		fichier2 = fopen(dossier2, "rb");
		if(fichier1 != NULL){
			fread(&p1, sizeof(Patient), 1, fichier1);
		}
		fclose(fichier1);
		fichier2 = fopen(dossier2, "rb");
		if(fichier2 != NULL){
			fread(&p2, sizeof(Patient), 1, fichier2);
		}
		fclose(fichier2);
		fichier1 = fopen(dossier1, "wb");
		fwrite(&p2, sizeof(Patient), 1, fichier1);
		fclose(fichier1);
		fichier2 = fopen(dossier2, "wb");
		fwrite(&p1, sizeof(Patient), 1, fichier2);
		fclose(fichier2);

		if(i == nombre_Rv - 1)
			remove(dossier2);
	}
	
	nombre_Rv--;
	char dossier_rv[50] = "";
	FILE* file = NULL;
	strcpy(dossier_rv, "Medecins/");
	strcat(dossier_rv, medecin);
	strcat(dossier_rv, "/nbr_rv.bin");
	file = fopen(dossier_rv, "wb");
	fwrite(&nombre_Rv, sizeof(int), 1, file);
	fclose(file);
}

void Suppression_Auto(char medecin[50]){
	char dossier1[50] = "", chiffre[5] = "";
	int Nbr_Dispo, i, day, month, year;
	strcpy(dossier1, "Medecins/");
	strcat(dossier1, medecin);
	strcat(dossier1, "/nbrDispo.bin");
	FILE *fichier1 = fopen(dossier1, "rb");
	if(fichier1 != NULL){
		fread(&Nbr_Dispo, sizeof(int), 1, fichier1);
	}else{
		Nbr_Dispo = 0;
	}
	fclose(fichier1);
	if(Nbr_Dispo == 0){
		return;
	}
	Rendez_Vous rv;
	time_t currenttime;
	time(&currenttime);
	struct tm *mytime = localtime(&currenttime);
	day = mytime->tm_mday;
	month = mytime->tm_mon + 1;
	year = mytime->tm_year + 1900;
	for(i=0; i<Nbr_Dispo; i++){
		strcpy(dossier1, "Medecins/");
		strcat(dossier1, medecin);
		strcat(dossier1, "/disponibilites/dispo");
		sprintf(chiffre, "%d", i+1);
		strcat(dossier1, chiffre);
		strcat(dossier1, ".bin");
		fichier1 = fopen(dossier1, "rb");
		if(fichier1 != NULL){
			fread(&rv, sizeof(Rendez_Vous), 1, fichier1);
			fclose(fichier1);
			if(rv.annee < year || (rv.annee == year && rv.mois < month) || (rv.annee == year && rv.mois == month && rv.jours < day)){
				Repousse_Supprime_Dispo(i+1, Nbr_Dispo, medecin);
			}
		}else
			fclose(fichier1);
	}

	char dossier2[50] = "";
	int Nbr_Rv;
	strcpy(dossier2, "Medecins/");
	strcat(dossier2, medecin);
	strcat(dossier2,"/nbr_rv.bin");
	FILE* fichier2 = fopen(dossier2, "rb");
	if(fichier2 != NULL){
		fread(&Nbr_Rv, sizeof(int), 1, fichier2);
	}else
		Nbr_Rv = 0;
	fclose(fichier2);

	if(Nbr_Rv == 0){
		return;
	}
	Patient p;
	for(i=0; i<Nbr_Rv; i++){
		strcpy(dossier2, "Medecins/");
		strcat(dossier2, medecin);
		strcat(dossier2, "/RendezVous/rv");
		sprintf(chiffre, "%d", i+1);
		strcat(dossier2, chiffre);
		strcat(dossier2, ".bin");
		fichier2 = fopen(dossier2, "rb");
		if(fichier2 != NULL){
			fread(&p, sizeof(Patient), 1, fichier2);
			if(p.rv.annee < year || (p.rv.annee == year && p.rv.mois < month) || (p.rv.annee == year && p.rv.mois == month && p.rv.jours < day)){
				Repousse_Supprime_Rv(i+1, Nbr_Rv, medecin);
			}
			fclose(fichier2);
		}else
			fclose(fichier2);
	}
}

//Fonctions permettant de saisir
char* Saisi_Chaine(SDL_KeyboardEvent boutton){
	char* aretourner;
	switch(boutton.keysym.sym){
		case SDLK_a:
			strcpy(aretourner, "q");
			break;
		case SDLK_b:
			strcpy(aretourner, "b");
			break;
		case SDLK_c:
			strcpy(aretourner, "c");
			break;
		case SDLK_d:
			strcpy(aretourner, "d");
			break;
		case SDLK_e:
			strcpy(aretourner, "e");
			break;
		case SDLK_f:
			strcpy(aretourner, "f");
			break;
		case SDLK_g:
			strcpy(aretourner, "g");
			break;
		case SDLK_h:
			strcpy(aretourner, "h");
			break;
		case SDLK_i:
			strcpy(aretourner, "i");
			break;
		case SDLK_j:
			strcpy(aretourner, "j");
			break;
		case SDLK_k:
			strcpy(aretourner, "k");
			break;
		case SDLK_l:
			strcpy(aretourner, "l");
			break;
		case SDLK_SEMICOLON:
			strcpy(aretourner, "m");
			break;
		case SDLK_n:
			strcpy(aretourner, "n");
			break;
		case SDLK_o:
			strcpy(aretourner, "o");
			break;
		case SDLK_p:
			strcpy(aretourner, "p");
			break;
		case SDLK_q:
			strcpy(aretourner, "a");
			break;
		case SDLK_r:
			strcpy(aretourner, "r");
			break;
		case SDLK_s:
			strcpy(aretourner, "s");
			break;
		case SDLK_t:
			strcpy(aretourner, "t");
			break;
		case SDLK_u:
			strcpy(aretourner, "u");
			break;
		case SDLK_v:
			strcpy(aretourner, "v");
			break;
		case SDLK_w:
			strcpy(aretourner, "z");
			break;
		case SDLK_x:
			strcpy(aretourner, "x");
			break;
		case SDLK_y:
			strcpy(aretourner, "y");
			break;
		case SDLK_z:
			strcpy(aretourner, "w");
			break;
		case SDLK_SPACE:
			strcpy(aretourner, " ");
			break;
		default:
			strcpy(aretourner, "");
			break;
	}

	return aretourner;
}

char* Saisi_Chiffre(SDL_KeyboardEvent boutton){
	char* aretourner;
	switch(boutton.keysym.sym){
		case SDLK_KP0:
			strcpy(aretourner, "0");
			break;
		case SDLK_KP1:
			strcpy(aretourner, "1");
			break;
		case SDLK_KP2:
			strcpy(aretourner, "2");
			break;
		case SDLK_KP3:
			strcpy(aretourner, "3");
			break;
		case SDLK_KP4:
			strcpy(aretourner, "4");
			break;
		case SDLK_KP5:
			strcpy(aretourner, "5");
			break;
		case SDLK_KP6:
			strcpy(aretourner, "6");
			break;
		case SDLK_KP7:
			strcpy(aretourner, "7");
			break;
		case SDLK_KP8:
			strcpy(aretourner, "8");
			break;
		case SDLK_KP9:
			strcpy(aretourner, "9");
			break;
		default:
			strcpy(aretourner, "");
			break;
	}

	return aretourner;
}
