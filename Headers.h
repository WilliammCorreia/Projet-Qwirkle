#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>

#define NB_LIGNE_TAB 13 // On commence par un arobase donc 13 et non 12
#define NB_COLON_TAB 53 // Car il y a un espace après chaque lettre et on commence par un arobase donc 53 et non 52
#define MAX_SIZE_JOU 4 // Nombres de jouers maximum dans une partie
#define NB_TUILE_DIF 6 // Nombre de forme et de couleur différente par tuile
#define NB_TUILE_MAX 108 // Nombre de tuile maximum ( 108 - Normal , 36 - Dégradé )
#define NB_TUILE_MAI 6 // Nombre de tuile dans la main du joueur
#define NB_TUILE_UNI 36 // Nombre de tuile unique
#define TAILLE_PSEUD 20 // Taille du pseudo
#define MAX_LIGNE_TAILLE 1000 //taille des lignes a récupérer du fichier règle
// Structures

struct tuile{
    int couleur; // 0 - Rouge, 1 - Bleu, 2 - Vert, 3 - Violet, 4 - Jaune, 5 - Turquoise
    int symbole; // 0 - Losange, 1 - Coeur, 2 - Pic, 3 - Note, 4 - Trèfle, 5 - X
    char affichage; // Apparence de la tuile dans le plateau
}; typedef struct tuile TUI;

struct joueur{
    char nom[TAILLE_PSEUD];
    TUI main[NB_TUILE_UNI];
    int score;
}; typedef struct joueur JOU;

struct plateau{
    char affichage;
    int couleur;
    int symbole;
}; typedef struct plateau PLA;

// Déclarations de fonctions

int nb_joueurs(int nb_joueur); // Nombre de joueurs
int joueur_qui_joue(int indic, int nb_joueur, int joueur_qui_joue); // Valeur dans le tableau de joueur du joueur qui joue le tour actuel
JOU* creation_joueur(JOU* tab_joueur, TUI tuile[NB_TUILE_MAX],int nb_joueur); // Initialisation des joueurs
PLA* initialisation_tab(PLA plateau[NB_LIGNE_TAB][NB_COLON_TAB]); // Initialisation du tableau
TUI* creation_tuiles(int nb_tuiles, TUI * tuile); // Initialisation des tuiles
TUI* attribut_tuiles(TUI tuile[NB_TUILE_MAX]); // Attribut une lettre à chaque tuile du tableau de tuile
int nb_tuile(int nb_tuile_a_placer); // Demande le nombre de tuile à poser
char* saisie_tuile(); // Demande où placer la tuile et quel tuile placer
int valeur_ligne(char* reponse); // Récupère la valeur de la ligne saisie par l'utilisateur
int valeur_colonne(char* reponse); // Récupère la valeur de la colonne saisie par l'utilisateur
int verification_main(char* reponse, JOU tab_joueur[MAX_SIZE_JOU], int joueur_qui_joue); // Vérifie que la tuile à jouer est dans la main
void affichage_tab(PLA plateau_tab[NB_LIGNE_TAB][NB_COLON_TAB]); // Affiche le plateau
PLA* ajout_tuile_tab(PLA plateau[NB_LIGNE_TAB][NB_COLON_TAB], JOU tab_joueur[MAX_SIZE_JOU], int joueurs_qui_joue, char* reponse); // Ajoute une tuile dans le plateau
void text_color(int text_color); // fonction d'affichage de couleurs
void affichage_main(JOU tab_joueur[MAX_SIZE_JOU], int joueurs_qui_joue); // Affichage de la main du joueur
JOU retire_tuile(char* reponse,JOU tab_joueur[MAX_SIZE_JOU], int joueur_qui_joue); // Retire la tuile joué de la main
char* reponse_joueur(); // Information sur la tuile à jouer
JOU repiochage(JOU tab_joueur[MAX_SIZE_JOU], int joueur_qui_joue, int compteur_pioche, TUI tuile[NB_TUILE_MAX]); // Repioche une tuile dans la main
int incrementation(int nb_joueur,int compteur_pioche); // Place de la tuile qui n'a pas encore été pioché dans le tableau de tuile ( haut de la pioche )
JOU score(JOU tab_joueur[MAX_SIZE_JOU], int joueur_qui_joue); // Score des joueurs
void afficheregles(); // Affichage des règles

#endif // HEADERS_H_INCLUDED