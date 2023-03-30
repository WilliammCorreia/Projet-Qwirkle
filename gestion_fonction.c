#include "Headers.h"

// Affiche les règles
void afficheregles()
{
    FILE *file;
    char lignes[MAX_LIGNE_TAILLE];
    char lignescores[200];
    char nom_file[100];

    system("cls");
    file = fopen("regles_qwirk.txt","r");
    if (file == NULL)
    {
        printf("erreur de l'ouverture du fichier\n");
    }
    while (fgets(lignes,MAX_LIGNE_TAILLE, file)!= NULL)
    {
        printf("%s",lignes);
    }

    fclose(file);
    printf("\n Revenir au menu:");


}

// Nombre de joueurs dans la partie
int nb_joueurs(int nb_joueur)
{

    printf("Saisir le nombres de joueurs : \n");
    scanf("%d", &nb_joueur);

    return nb_joueur;
}

// Retourne un chiffre qui permet de savoir quelle joueur du tableau de joueurs doit jouer
int joueur_qui_joue(int indic, int nb_joueur, int joueur_qui_joue)
{

    if( nb_joueur == 2 )
    {
        if( indic % 2 == 1 )
        {
            joueur_qui_joue = 1;
        }
        else if( indic % 2 == 0 )
        {
            joueur_qui_joue = 0;
        }
    }

    if( nb_joueur == 3 )
    {
        if( indic % 3 == 0 )
        {
            joueur_qui_joue = 0;
        }
        else if( indic % 3 == 1 )
        {
            joueur_qui_joue = 1;
        }
        else if( indic % 3 == 2 )
        {
            joueur_qui_joue = 2;
        }
    }

    if( nb_joueur == 4 )
    {
        if( indic % 4 == 0 )
        {
            joueur_qui_joue = 0;
        }
        else if( indic % 4 == 1 )
        {
            joueur_qui_joue = 1;
        }
        else if( indic % 4 == 2 )
        {
            joueur_qui_joue = 2;
        }
        else if( indic % 4 == 3 )
        {
            joueur_qui_joue = 3;
        }
    }

    return joueur_qui_joue;
}

// Demande le nombre de joueurs et leurs pseudos
JOU* creation_joueur(JOU* tab_joueur, TUI tuile[NB_TUILE_MAX],int nb_joueur)
{
    int i; // Boucle 1
    int j; // Boucle 2
    int incrementation = 0;

    for( i = 0; i < nb_joueur; i++)
    {
        printf("Saisir le pseudo du joueur : \n");
        scanf("%s", tab_joueur[i].nom);
    }

    // Initialisation de la main des joueurs
    for( i = 0; i < nb_joueur; i++)
    {
        for( j = 0; j < NB_TUILE_MAI; j++)
        {
            tab_joueur[i].main[j].affichage = tuile[incrementation].affichage;
            tab_joueur[i].main[j].symbole = tuile[incrementation].symbole;
            tab_joueur[i].main[j].couleur = tuile[incrementation].couleur;
            incrementation++;
        }
    }
    return tab_joueur;
}

// Plateau de jeu
PLA* initialisation_tab(PLA plateau[NB_LIGNE_TAB][NB_COLON_TAB])
{
    int i; // Boucle 1
    int j; // Boucle 2
    int alphabet = 65; // Permet d'incrémenter la bonne lettre à la bonne place du tableau sur la première ligne

    // Intialise le tableau
    for( i = 0; i < NB_LIGNE_TAB; i++)
    {
        for( j = 0; j < NB_COLON_TAB; j++)
        {
            if( j % 2 == 1)
            {
                plateau[i][j].affichage = ' ';
            }
            else
            {
                if( j == 0)
                {
                    plateau[i][j].affichage = (char) (i + 64);
                }
                else if( i == 0 && j >= 1)
                {
                    plateau[i][j].affichage = (char) alphabet;
                    alphabet++;
                }
                else
                {
                    plateau[i][j].affichage = '.';
                }
            }
        }
    }
    return (PLA *) plateau;
}

// Affiche le tableau
void affichage_tab(PLA plateau[NB_LIGNE_TAB][NB_COLON_TAB])
{
    int i; // Boucle 1
    int j; // Boucle 2

    for(i = 0; i < NB_LIGNE_TAB; i++ )
    {
        for(j = 0; j < NB_COLON_TAB; j++)
        {
            // Rouge
            if( plateau[i][j].couleur == 1)
            {
                text_color(4) ;
            }
                // Bleu
            else if( plateau[i][j].couleur == 2)
            {
                text_color(9) ;
            }
                // Vert
            else if( plateau[i][j].couleur == 3)
            {
                text_color(10) ;
            }
                // Violet
            else if( plateau[i][j].couleur == 4)
            {
                text_color(5) ;
            }
                // Jaune
            else if( plateau[i][j].couleur == 5)
            {
                text_color(14) ;
            }
                // Turquoise
            else if( plateau[i][j].couleur == 6)
            {
                text_color(11) ;
            }
                // Couleur de base
            else
            {
                text_color(15) ;
            }
            printf("%c", plateau[i][j].affichage);
        }
        printf("\n");
    }
}

// Tuiles
TUI* creation_tuiles(int nb_tuiles, TUI* tuile)
{
    int i; // Boucle 1
    int j; // Boucle 2
    int k; // Boucle 3
    int incrementation = 0;

    // Exemplaire
    for( i = 0; i < nb_tuiles; i++)
    {
        // Symbole
        for( j = 0; j < NB_TUILE_DIF; j++)
        {
            // Couleur
            for( k = 0; k < NB_TUILE_DIF; k++)
            {
                tuile[incrementation].symbole = j;
                tuile[incrementation].couleur = (k+1);
                incrementation++;
            }
        }
    }

    // Aléatoire
    srand(time(0));
    int random_index;
    for (i = 0; i < (36*nb_tuiles); i++)
    {
        tuile[i].symbole = rand() % NB_TUILE_DIF;
        tuile[i].couleur = rand() % NB_TUILE_DIF + 1;
        random_index = rand() % nb_tuiles;
        TUI temp = tuile[i];
        tuile[i] = tuile[random_index];
        tuile[random_index] = temp;
    }

    return tuile;
}

// Nombre de tuile à placer
int nb_tuile(int nb_tuile_a_placer)
{
    printf("Saisir le nombre de tuile a placer durant ce tour : \n");
    scanf("%d", &nb_tuile_a_placer);

    return nb_tuile_a_placer;
}

// Demande où placer la tuile et quel tuile placer
char* saisie_tuile()
{
    char* reponse = malloc(sizeof(char) * 4); // Pour sauvegarder les données en mémoires

    // Saisie de la Tuile à placer durant le tour et de sa position
    printf("Saisir ou placer la tuile ( ecrire : LigneColonneFORMECouleur ( ex : flL1 )\n");
    scanf("%s", reponse);
    return reponse;
}

// Récupère la valeur de i de tableau[i][j] saisie par l'utilisateur
int valeur_ligne(char* reponse)
{
    int x; // Ligne
    x = ((int)reponse[0] - 96); // Récupère la lettre est la convertie en sa valeur de la ligne
    return x;
}

// Récupère la valeur de j de tableau[i][j] saisie par l'utilisateur
int valeur_colonne(char* reponse)
{
    int y; // Colonne
    y = (((int)reponse[1] - 96)*2); // Récupère la lettre est la convertie en sa valeur de la colonne
    return y;
}

// Vérifie que la tuile à jouer est dans la main
int verification_main(char* reponse, JOU tab_joueur[MAX_SIZE_JOU], int joueur_qui_joue)
{
    int forme; // Valeur de la forme
    int couleur; // Valeur de la couleur
    int verif_main; // 1 = tuile dans la main, 0 = tuile pas dans la main
    int i; // Boucle 1

    //Forme
    if( reponse[2] == 'L' )
    {
        forme = 0;
    }
    else if( reponse[2] == 'C' )
    {
        forme = 1;
    }
    else if( reponse[2] == 'P' )
    {
        forme = 2;
    }
    else if( reponse[2] == 'N' )
    {
        forme = 3;
    }
    else if( reponse[2] == 'T' )
    {
        forme = 4;
    }
    else if( reponse[2] == 'X' )
    {
        forme = 5;
    }

    // Couleur
    if( reponse[3] == '1' )
    {
        couleur = 0;
    }
    else if( reponse[3] == '2' )
    {
        couleur = 1;
    }
    else if( reponse[3] == '3' )
    {
        couleur = 2;
    }
    else if( reponse[3] == '4' )
    {
        couleur = 3;
    }
    else if( reponse[3] == '5' )
    {
        couleur = 4;
    }
    else if( reponse[3] == '6' )
    {
        couleur = 5;
    }

    couleur++;
    verif_main = 0;

    for( i = 0; i < 6; i++ )
    {
        if( tab_joueur[joueur_qui_joue].main[i].symbole == forme && tab_joueur[joueur_qui_joue].main[i].couleur == couleur )///couleur+1 car k = k+1 (affichage)
        {
            verif_main = 1;
        }
    }
    return verif_main;
}

// Retire la tuile joué de la main
JOU retire_tuile(char* reponse,JOU tab_joueur[MAX_SIZE_JOU], int joueur_qui_joue)
{
    int forme; // Valeur de la forme
    int couleur; // Valeur de la couleur
    int index; // Emplacement dans la main ou se trouve la tuile joué
    int i; // Boucle 1

    // Forme
    if( reponse[2] == 'L' )
    {
        forme = 0;
    }
    else if( reponse[2] == 'C' )
    {
        forme = 1;
    }
    else if( reponse[2] == 'P' )
    {
        forme = 2;
    }
    else if( reponse[2] == 'N' )
    {
        forme = 3;
    }
    else if( reponse[2] == 'T' )
    {
        forme = 4;
    }
    else if( reponse[2] == 'X' )
    {
        forme = 5;
    }

    // Couleur
    if( reponse[3] == '1' )
    {
        couleur = 0;
    }
    else if( reponse[3] == '2' )
    {
        couleur = 1;
    }
    else if( reponse[3] == '3' )
    {
        couleur = 2;
    }
    else if( reponse[3] == '4' )
    {
        couleur = 3;
    }
    else if( reponse[3] == '5' )
    {
        couleur = 4;
    }
    else if( reponse[3] == '6' )
    {
        couleur = 5;
    }

    couleur++;
    index = 0;

    for( i = 0; i < 6; i++ )
    {
        if( tab_joueur[joueur_qui_joue].main[i].symbole == forme && tab_joueur[joueur_qui_joue].main[i].couleur == couleur )///couleur+1 car k = k+1 (affichage)
        {
            index = i;
        }
    }

    tab_joueur[joueur_qui_joue].main[index].symbole = 7;
    tab_joueur[joueur_qui_joue].main[index].couleur = 7;
    tab_joueur[joueur_qui_joue].main[index].affichage = ' ';

    return* tab_joueur;
}

// Attribue une lettre et une couleur à chaque tuiles
TUI* attribut_tuiles(TUI tuile[NB_TUILE_MAX])
{
    int i; // Boucle

    for( i = 0; i < NB_TUILE_MAX; i++)
    {
        if( tuile[i].symbole == 0 )
        {
            tuile[i].affichage = 'L';
            //tuile[i].affichage = 0x04;
        }
        else if( tuile[i].symbole == 1 )
        {
            tuile[i].affichage = 'C';
            //tuile[i].affichage = 0x03;
        }
        else if( tuile[i].symbole == 2 )
        {
            tuile[i].affichage = 'P';
            //tuile[i].affichage = 0x06;
        }
        else if( tuile[i].symbole == 3 )
        {
            tuile[i].affichage = 'N';
            //tuile[i].affichage = 0x0E;
        }
        else if( tuile[i].symbole == 4 )
        {
            tuile[i].affichage = 'T';
            //tuile[i].affichage = 0x05;
        }
        else if( tuile[i].symbole == 5 )
        {
            tuile[i].affichage = 'X';
        }
    }
    return tuile;
}

// Demande où le joueur veut placer sa tuile et la tuile qu'il veut placer
char* reponse_joueur()
{
    char* reponse = saisie_tuile(); // Demande où saisir la tuile et quel tuile placé

    return reponse;
}

// Ajoute une tuile dans le plateau
PLA* ajout_tuile_tab(PLA plateau[NB_LIGNE_TAB][NB_COLON_TAB], JOU tab_joueur[MAX_SIZE_JOU], int joueurs_qui_joue, char* reponse)
{

    // Variables
    int couleur;
    int symbole;
    char affichage;
    int x;
    int y;
    int verif_main;

    // Fonctions appelées
    do
    {
        x = valeur_ligne(reponse); // Coordonnée de la ligne
        y = valeur_colonne(reponse); // Coordonnée de la colonne
        verif_main = verification_main(reponse, tab_joueur, joueurs_qui_joue); // Vérifie que la tuile à jouer est dans la main

        if( verif_main == 0 )
        {
            printf("Vous ne possedez pas cette tuile dans votre main, ressayer !\n");
            reponse = reponse_joueur();
        }
    }
    while( verif_main == 0 );

    // Récupération du symbole

    // Symboles
    char Losange = 'L';
    char Coeur = 'C';
    char Pic = 'P';
    char Note = 'N';
    char Trefle = 'T';
    char Forme_X = 'X';

    if( reponse[2] == Losange )
    {
        affichage = 'L';
        //affichage = 0x04;
        symbole = 1;
    }
    else if( reponse[2] == Coeur )
    {
        affichage = 'C';
        //affichage = 0x03;
        symbole = 2;

    }
    else if( reponse[2] == Pic )
    {
        affichage = 'P';
        //affichage = 0x06;
        symbole = 3;

    }
    else if( reponse[2] == Note )
    {
        affichage = 'N';
        //affichage = 0x0E;
        symbole = 4;

    }
    else if( reponse[2] == Trefle )
    {
        affichage = 'T';
        //affichage = 0x05;
        symbole = 5;

    }
    else if( reponse[2] == Forme_X )
    {
        affichage = 'X';
        symbole = 6;

    }

    // Récupération de la couleur
    couleur = atoi(&reponse[3]); // Récupère la valeur de la couleur

    plateau[x][y].couleur = couleur;
    plateau[x][y].symbole = symbole;
    plateau[x][y].affichage = affichage;

    return* plateau;
}

// Fonction d'affichage des couleurs
void text_color(int text_color) //change la couleur du texte de la console
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE) ;
    SetConsoleTextAttribute(H,text_color) ;
}

// Affichage main du joueur
void affichage_main(JOU tab_joueur[MAX_SIZE_JOU], int joueurs_qui_joue)
{

    int i; // Boucle 1

    text_color(15);
    printf("Vos tuiles :");

    for(i = 0; i < NB_TUILE_MAI; i++ )
    {

        // Rouge
        if( tab_joueur[joueurs_qui_joue].main[i].couleur == 1)
        {
            text_color(4) ;
        }
            // Bleu
        else if( tab_joueur[joueurs_qui_joue].main[i].couleur == 2)
        {
            text_color(9) ;
        }
            // Vert
        else if( tab_joueur[joueurs_qui_joue].main[i].couleur == 3)
        {
            text_color(10) ;
        }
            // Violet
        else if( tab_joueur[joueurs_qui_joue].main[i].couleur == 4)
        {
            text_color(5) ;
        }
            // Jaune
        else if( tab_joueur[joueurs_qui_joue].main[i].couleur == 5)
        {
            text_color(14) ;
        }
            // Turquoise
        else if( tab_joueur[joueurs_qui_joue].main[i].couleur == 6)
        {
            text_color(11) ;
        }
        printf("%c", tab_joueur[joueurs_qui_joue].main[i].affichage);
    }
    text_color(15);

    printf("                  Votre score = %d", tab_joueur[joueurs_qui_joue].score);
    printf("\n\n");
}

// Place de la tuile qui n'a pas encore été pioché dans le tableau de tuile ( haut de la pioche )
int incrementation(int nb_joueur,int compteur_pioche)
{
    int i; // Boucle 1

    // Permet de rajouter la prochaine tuile de la pioche
    for( i = 0; i < nb_joueur; i ++)
    {
        compteur_pioche += 6;
    }

    return compteur_pioche;
}

// Repioche une tuile dans la main
JOU repiochage(JOU tab_joueur[MAX_SIZE_JOU], int joueur_qui_joue, int compteur_pioche, TUI tuile[NB_TUILE_MAX])
{
    int i; // Boucle 1

    // Incrémente la tuile dans la main
    for( i = 0; i < 6; i ++)
    {
        if( tab_joueur[joueur_qui_joue].main[i].couleur == 7 )
        {
            tab_joueur[joueur_qui_joue].main[i].couleur = tuile[compteur_pioche].couleur;
            tab_joueur[joueur_qui_joue].main[i].symbole = tuile[compteur_pioche].symbole;
            tab_joueur[joueur_qui_joue].main[i].affichage = tuile[compteur_pioche].affichage;
            compteur_pioche++;
        }
    }

    return* tab_joueur;
}

// Score des joueurs
JOU score(JOU tab_joueur[MAX_SIZE_JOU], int joueur_qui_joue)
{

    printf("Saisir votre score actuel :\n");
    scanf("%d", &tab_joueur[joueur_qui_joue].score);

    return* tab_joueur;
}