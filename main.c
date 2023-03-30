#include "Headers.h"

int main() {

    //Variables
    int choix; // Choix de l'utilisateur
    JOU tab_joueur[MAX_SIZE_JOU]; // Tableau liste des joueurs
    int nb_tuiles_identique; // Nombre de tuiles identiques
    TUI tuile[NB_TUILE_MAX]; // Mode Normal - 108, Mode Dégradé - 36
    PLA plateau[NB_LIGNE_TAB][NB_COLON_TAB]; // Plateau
    int nb_joueur; // Nombre de joueur
    int nb_tuile_a_placer = 1; // Nombre de tuile à placer
    int j; // Boucle 2
    int k; // Boucle 1
    int indic = 0; // Sert pour définir quel est le joueur qui joue
    char* reponse; // réponse du joueur sur les informations de la tuile à jouer
    int joueurs_qui_joue; // Valeur dans le tableau de joueur du joueur qui joue le tour actuel
    int compteur_pioche = 0; // Compte les cases de la pioche
    TUI tmp; // Variable pour la permutation des tuiles
    int case_pioche; // Compte la valeur de la case du tableau de tuile
    int nb_tuile_supp; // Valeur dans la main de la tuile à supprimer
    int choix_tuile; // Nombre de tuile à échanger

    //Menu
while (1)
    do
    {
             // Instructions
        printf("***************** QWIRKLE *****************\n");
        printf("1 - Consulter les regles\n");
        printf("2 - Commencer une nouvelle partie\n");
        printf("3 - Reprendre une partie sauvegardee\n");
        printf("4 - Consulter les scores\n");
        printf("5 - Quitter le jeu\n");
        scanf("%d", &choix);

        // Consulter les règles
        if (choix == 1)
        {
            afficheregles();
            system("pause");
            break;
        }

            // Commencer une nouvelle partie
        else if (choix == 2)
        {
            do
            {
                printf("Choisir le mode de jeu :\n");
                printf("1 - Normal\n");
                printf("2 - Degrade\n");
                printf("0 - Retourner au menu\n");
                scanf("%d", &choix);

                {
                    // Mode Normal
                    if (choix == 1)
                    {
                        // Initialisation de la partie
                        nb_tuiles_identique = 3; // Nombre de tuiles identiques pour mode Normal
                        creation_tuiles(nb_tuiles_identique, tuile); // Créer le bon nombre de tuiles
                        attribut_tuiles(tuile); // Attribut une lettre à chaque tuile du tableau de tuile
                        initialisation_tab(plateau); // Initialisation du tableau
                        nb_joueur = nb_joueurs(nb_joueur); // Demande le nombre de joueurs
                        creation_joueur(tab_joueur,tuile, nb_joueur); // Création des joueurs
                        compteur_pioche = incrementation(nb_joueur, compteur_pioche); // Place de la tuile qui n'a pas encore été pioché dans le tableau de tuile ( haut de la pioche )
                        case_pioche = compteur_pioche; // Valeur de la case de la pioche du tour actuel

                        // Début de la partie
                        do
                        {
                            joueurs_qui_joue = joueur_qui_joue(indic,nb_joueur,joueurs_qui_joue);
                            printf("Tour de %s \n", tab_joueur[joueurs_qui_joue].nom);
                            affichage_tab(plateau); // Affiche le plateau
                            affichage_main(tab_joueur, joueurs_qui_joue); // Affiche la main du joueur

                            // Choix à faire au début du tour
                            printf("Choisir que faire ce tour :\n");
                            printf("1 - Placer une ou plusieurs tuile(s)\n");
                            printf("2 - Remplacer une ou plusieurs tuile(s)\n");
                            printf("3 - Quitter la partie\n");
                            scanf("%d", &choix);

                            // Continuer la partie
                            if( choix == 1 )
                            {
                                nb_tuile_a_placer = nb_tuile(nb_tuile_a_placer); // Demande le nombre de tuile à placer

                                for( j = 0; j < nb_tuile_a_placer; j++)
                                {
                                    reponse = reponse_joueur();
                                    ajout_tuile_tab(plateau, tab_joueur, joueurs_qui_joue, reponse); // Ajoute la tuile dans le plateau
                                    retire_tuile(reponse, tab_joueur, joueurs_qui_joue); // Retire la tuile de la main
                                    affichage_tab(plateau); // Affiche le plateau
                                    affichage_main(tab_joueur, joueurs_qui_joue); // Affiche la main du joueur
                                }

                                score(tab_joueur, joueurs_qui_joue); // Saisie du score du joueur

                                for( j = 0; j < nb_tuile_a_placer; j++)
                                {
                                    repiochage(tab_joueur, joueurs_qui_joue, compteur_pioche,tuile); // Repioche une ou plusieurs tuile(s)
                                    compteur_pioche++; // Enlève la tuile pioché de la pioche et passe à la suivante
                                }
                            }
                            // Echanger une ou plusieurs tuiles
                            else if( choix == 2 )
                            {
                                printf("Saisir le nombre de tuiles a echanger\n");
                                scanf("%d", &choix_tuile);

                                for( k = 0; k < choix_tuile; k++)
                                {
                                    printf("Saisir le numero de la tuile a echanger ( 1 pour la premiere, 6 pour la derniere ) :\n");
                                    scanf("%d", &nb_tuile_supp);
                                    nb_tuile_supp--;

                                    //Permutation
                                    tmp.couleur = tab_joueur[joueurs_qui_joue].main[nb_tuile_supp].couleur;
                                    tmp.symbole = tab_joueur[joueurs_qui_joue].main[nb_tuile_supp].symbole;
                                    tmp.affichage = tab_joueur[joueurs_qui_joue].main[nb_tuile_supp].affichage;

                                    tab_joueur[joueurs_qui_joue].main[nb_tuile_supp].couleur = tuile[compteur_pioche].couleur;
                                    tab_joueur[joueurs_qui_joue].main[nb_tuile_supp].symbole = tuile[compteur_pioche].symbole;
                                    tab_joueur[joueurs_qui_joue].main[nb_tuile_supp].affichage = tuile[compteur_pioche].affichage;
                                    for( j = 0; j < (108-compteur_pioche); j++)
                                    {
                                        tuile[case_pioche] = tuile[case_pioche+1];
                                        case_pioche++;
                                    }
                                    case_pioche = compteur_pioche;

                                    tuile[107].couleur = tmp.couleur;
                                    tuile[107].symbole = tmp.symbole;
                                    tuile[107].affichage = tmp.affichage;
                                }
                            }
                            // Quitter la partie
                            else if( choix == 3 )
                            {

                            }
                            indic++;
                        }while( choix != 3 );
                    }
                        // Mode Dégradé
                    else if (choix == 2)
                    {
                        // Initialisation de la partie
                        nb_tuiles_identique = 1; // Nombre de tuiles identiques pour mode Normal
                        creation_tuiles(nb_tuiles_identique, tuile); // Créer le bon nombre de tuiles
                        attribut_tuiles(tuile); // Attribut une lettre à chaque tuile du tableau de tuile
                        initialisation_tab(plateau); // Initialisation du tableau
                        nb_joueur = nb_joueurs(nb_joueur); // Demande le nombre de joueurs
                        creation_joueur(tab_joueur, tuile, nb_joueur); // Création des joueurs
                        compteur_pioche = incrementation(nb_joueur,
                                                         compteur_pioche); //Place de la tuile qui n'a pas encore été pioché dans le tableau de tuile ( haut de la pioche )
                        case_pioche = compteur_pioche;

                        // Début de la partie
                        do
                        {
                            joueurs_qui_joue = joueur_qui_joue(indic, nb_joueur, joueurs_qui_joue);
                            printf("Tour de %s \n", tab_joueur[joueurs_qui_joue].nom);
                            affichage_tab(plateau); // Affiche le plateau
                            affichage_main(tab_joueur, joueurs_qui_joue); // Affiche la main du joueur
                            /// affichage du score de la personne qui joue

                            // Choix à faire au début du tour
                            printf("Choisir que faire ce tour :\n");
                            printf("1 - Placer une ou plusieurs tuile(s)\n");
                            printf("2 - Remplacer une ou plusieurs tuile(s)\n");
                            printf("3 - Quitter la partie\n");
                            scanf("%d", &choix);

                            // Continuer la partie
                            if (choix == 1)
                            {
                                nb_tuile_a_placer = nb_tuile(nb_tuile_a_placer); // Demande le nombre de tuile à placer

                                for (j = 0; j < nb_tuile_a_placer; j++)
                                {
                                    reponse = reponse_joueur();
                                    ajout_tuile_tab(plateau, tab_joueur, joueurs_qui_joue,
                                                    reponse); // Ajoute la tuile dans le plateau
                                    retire_tuile(reponse, tab_joueur, joueurs_qui_joue); // Retire la tuile de la main
                                    /// Vérification du nombre de point
                                    affichage_tab(plateau); // Affiche le plateau
                                    affichage_main(tab_joueur, joueurs_qui_joue); // Affiche la main du joueur
                                }

                                for (j = 0; j < nb_tuile_a_placer; j++)
                                {
                                    repiochage(tab_joueur, joueurs_qui_joue, compteur_pioche,tuile); // Repioche une ou plusieurs tuile(s)
                                    compteur_pioche++; // Enlève la tuile pioché de la pioche et passe à la suivante
                                }
                            }
                                // Echanger une ou plusieurs tuiles
                            else if (choix == 2)
                            {
                                printf("Saisir le nombre de tuiles a echanger\n");
                                scanf("%d", &choix_tuile);

                                for (k = 0; k < choix_tuile; k++) {
                                    printf("Saisir le numero de la tuile a echanger ( 1 pour la premiere, 6 pour la derniere ) :\n");
                                    scanf("%d", &nb_tuile_supp);
                                    nb_tuile_supp--;

                                    //Permutation
                                    tmp.couleur = tab_joueur[joueurs_qui_joue].main[nb_tuile_supp].couleur;
                                    tmp.symbole = tab_joueur[joueurs_qui_joue].main[nb_tuile_supp].symbole;
                                    tmp.affichage = tab_joueur[joueurs_qui_joue].main[nb_tuile_supp].affichage;

                                    tab_joueur[joueurs_qui_joue].main[nb_tuile_supp].couleur = tuile[compteur_pioche].couleur;
                                    tab_joueur[joueurs_qui_joue].main[nb_tuile_supp].symbole = tuile[compteur_pioche].symbole;
                                    tab_joueur[joueurs_qui_joue].main[nb_tuile_supp].affichage = tuile[compteur_pioche].affichage;
                                    for (j = 0; j < (36 - compteur_pioche); j++) {
                                        tuile[case_pioche] = tuile[case_pioche + 1];
                                        case_pioche++;
                                    }
                                    case_pioche = compteur_pioche;

                                    tuile[35].couleur = tmp.couleur;
                                    tuile[35].symbole = tmp.symbole;
                                    tuile[35].affichage = tmp.affichage;
                                }
                            }
                            else if( choix == 3 )
                            {
                                // Ne rien faire !
                            }
                            indic++;
                        }while( choix != 3 );
                    }
                        // Retour au Menu
                    else if (choix == 0)
                    {
                        // Ne rien faire
                    }
                    else
                    {
                        printf("Taper 1, 2 ou 3 !\n\n");
                    }
                }
            }while( choix < 0 || choix > 2 );
        }
            // Reprendre une partie sauvegardée
        else if (choix == 3)
        {

        }
            // Consulter les scores
        else if (choix == 4)
        {

        }
            // Quitter
        else if (choix == 5)
        {
            return 0;
        }
    }while( choix < 1 || choix > 5 );
}