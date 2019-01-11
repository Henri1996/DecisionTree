
#ifndef donnee_h
#define donnee_h

#include <stdio.h>
#include "vector.h"


typedef struct
{
    unsigned int nb_colonnes; // la 1ere <=> classe à prédire (Y). Autres colonnes <=> variables d'observatio
    unsigned int nb_lignes;   // <=> les individus
    double** matrice;         // tableau de tableaux de réels (i.e. tableaux 2D de réels)
} matrice_donnees;


typedef struct _precision
{
    double p_inf;
    double p_sup;
    
}precision;

typedef struct
{
    int x ;
    char caractere;
    double mediane;
  
}critere_de_division;

typedef struct _noeud
{
    int y;
    matrice_donnees * mat ;
    vector * index ;
    struct _noeud * fils_gauche ;
    struct _noeud * fils_droit ;
    struct _noeud * parent ;
    critere_de_division * diviseur;
    double precision;
    
}noeud;


matrice_donnees* charger_donnnees(const char* nom_fichier);
matrice_donnees* liberer_donnees(matrice_donnees * data);

vector * Tab_index_racine(matrice_donnees * mat);
precision * chercher_div_precision(noeud * arbre, double * med, precision * pre ,  int y );
critere_de_division *  chercher_diviseur(noeud * arbre , char s);
double calcul_mediane(double * tab , int taille);

double  precisionY(noeud * a_noeud);
int recherche_max(critere_de_division * critere ,precision * pre, int taille);

noeud * initialisation_racine(matrice_donnees * mat, int y);
noeud * intitialisation_fils(noeud * arbre , critere_de_division *diviseur);
void creat_arbre(noeud * arbre , double precision_inf , double precision_sup ,double nb_indiv_minim, double hauteur_max);
critere_de_division * changer_caractere(critere_de_division * div);

double predire(noeud * arbre, double x1 ,double x2, double x3,double x4,double precision);


bool est_feuille(noeud const * element);
int nombre_feuilles(noeud const * parent);
int height(noeud * arbre);
int height_2(noeud *arbre);
int max(int a , int b);
double max_pre(double p1 , double p2 , double p3);


#endif /* donnee_h */

