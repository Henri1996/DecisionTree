
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "donnees.h" 
#include "vector.h"

//permet d'afficher la matrice pour vérifier que les valeurs on bien été chargé
void afficherMat(matrice_donnees * mat)
{
    for(int i = 0 ; i < mat->nb_lignes ; i++)
    {
        for(int j = 0 ; j < mat->nb_colonnes ; j++)
        {
            printf("%lg ", mat->matrice[i][j]);
        }
        printf("\n");
    }
}

//permet d'afficher le bon espace pour l'arbre
void afficher_offset(int offset)
{
    for(int i = 0 ; i < offset ; i++)
    {
        printf("          "); // 10 espaces
    }
}

//permet d'afficher le noeud
void affichage(noeud * arbre, int offset , int * compt)
{
    
    if(arbre->diviseur != NULL)
    {
        
        if(arbre->diviseur->caractere == '>')
        {
            //si c'est une feuille on le précise en disant en lui donnant un numéro
            if(est_feuille(arbre))
            {
                printf("FEUILLE %d\n",*compt);(*compt)++;
                afficher_offset(offset);
            }
            printf("|-Precision: %lg %%\n",arbre->precision);
            afficher_offset(offset);
            printf("|-Nb d'individu: %d\n",arbre->index->taille_logique);
            afficher_offset(offset);
            printf("|-Comment: X%d %c %lg\n",arbre->diviseur->x,'>',arbre->diviseur->mediane);
            
            
            
        }
        else
        {
            
            if(est_feuille(arbre))
            {
                printf("FEUILLE %d\n",*compt);(*compt)++;
                afficher_offset(offset);
            }
            printf("|-Precision: %lg %%\n",arbre->precision);
            afficher_offset(offset);
            printf("|-Nb d'individu: %d\n",arbre->index->taille_logique);
            afficher_offset(offset);
            printf("|-Comment: X%d %s %lg\n",arbre->diviseur->x,"<=",arbre->diviseur->mediane);
            
        }
    }
    else
    {
        printf("RACINE\n");
        printf("|-Precision: %lg %%\n",arbre->precision);
        printf("|-Nb d'individu: %d\n",arbre->index->taille_logique);
    }
}

void affichage_arborescence(noeud * arbre, int offset , int * compt)
{
    if(arbre != NULL)
    {
        printf("\n");
        afficher_offset(offset);
        affichage(arbre,offset, compt);
        affichage_arborescence(arbre->fils_gauche, offset+1 ,compt);
        affichage_arborescence(arbre->fils_droit, offset+1 ,  compt);
    }
    
}

//fonctino qui affiche le chemin d'une feuille
void affichage_chemin(noeud * feuille)
{
    if(feuille->parent!=NULL)
    {
        affichage_chemin(feuille->parent);
     
        
        if(feuille->diviseur->caractere == '<')
        {
            if(feuille->fils_gauche !=NULL && feuille->fils_droit != NULL)
            printf("X%d %s %lg puis ", feuille->diviseur->x ,"<=" , feuille->diviseur->mediane );
            else printf("X%d %s %lg", feuille->diviseur->x ,"<=" , feuille->diviseur->mediane );
        }
        else
        {
            if(feuille->fils_gauche !=NULL && feuille->fils_droit != NULL)
            printf("X%d %c %lg puis ", feuille->diviseur->x ,'>' , feuille->diviseur->mediane );
            else printf("X%d %c %lg", feuille->diviseur->x ,'>' , feuille->diviseur->mediane );
        }
    }
}

// affiche les informations des feuilles
void affichage_feuille(noeud* arbre, int * compt)
{
    
    if(!est_feuille(arbre))
    {
        affichage_feuille(arbre->fils_gauche, compt);
        affichage_feuille(arbre->fils_droit, compt);
    }
    else
    {
        printf("FEUILLE %d\n",*compt); (*compt)++;
        printf("Precision: %lg %%\n",arbre->precision);
        printf("Nb d'individu: %d\n",arbre->index->taille_logique);
        printf("Chemin: ");
        affichage_chemin(arbre);
        printf("\n\n");
    }
        
    
}


// fonction quie de demande a l'utilisateur tous les Xi
//puis qui appelle la fonction predire
//puis affiche les precisions
void predire_menu(noeud * arbre1 , noeud *arbre2 , noeud * arbre3)
{
    
    double x1, x2, x3 , x4 = 0;
    
    
    printf("\nSaisir la longueur des sepales (X1):");
    scanf("%lg",&x1);
    printf("\nSaisir la largeur des sepales (X2):");
    scanf("%lg",&x2);
    printf("\nSaisir la longueur des petales (X3):");
    scanf("%lg",&x3);
    printf("\nSaisir la largeur des petales (X4):");
    scanf("%lg",&x4);
    
    double p1 = predire(arbre1, x1, x2, x3, x4, 0);
    double p2 = predire(arbre2, x1, x2, x3, x4, 0);
    double p3 = predire(arbre3, x1, x2, x3, x4, 0);
    
    printf("\nC'est un iris setosa a %lg %%\n",p1);
    printf("C'est un iris versicolor a %lg %%\n",p2);
    printf("C'est un iris verginica a %lg %%\n\n",p3);
    
    double max=max_pre(p1, p2, p3);
    if(max==p1) printf("Donc d'apres mon arbre de decision c'est plutot un iris setosa!\n\n");
    if(max==p2) printf("Donc d'apres mon arbre de decision c'est plutot un iris versicolor!\n\n");
    if(max==p3) printf("Donc d'apres mon arbre de decision c'est plutot un iris verginica!\n\n");
}

void predire_main(noeud * arbre)
{
    double x1, x2, x3 , x4 = 0;
    
    printf("\nSaisir la longueur des sepales (X1):");
    scanf("%lg",&x1);
    printf("\nSaisir la largeur des sepales (X2):");
    scanf("%lg",&x2);
    printf("\nSaisir la longueur des petales (X3):");
    scanf("%lg",&x3);
    printf("\nSaisir la largeur des petales (X4):");
    scanf("%lg",&x4);
    
    double precision = predire(arbre, x1, x2, x3, x4, 0);
    if(arbre->y == 1) printf("\nC'est un iris setosa a %lg %%\n",precision);
    if(arbre->y == 2) printf("\nC'est un iris versicolor a %lg %%\n",precision);
    if(arbre->y == 3) printf("\nC'est un iris verginica a %lg %%\n",precision);
}

// fonction qui crée un menu
void menu(noeud * arbre1, noeud * arbre2 , noeud * arbre3, int y)
{
    noeud *arbre = (noeud*)malloc(sizeof(noeud));
    
    if(y==1) arbre= arbre1;
    if(y==2) arbre= arbre2;
    if(y==3) arbre = arbre3;
    int compt = 1;
    int *p_compt = &compt;
    char * choix=(char*)malloc(sizeof(char));
    printf("-----------MENU----------\n\n");
    
    printf("Saisir un nombre entre 0 et 6:\n");
    printf("1- Afficher la hauteur de l'arbre\n");
    printf("2- Afficher la largeur de l'arbre (nombre de feuilles)\n");
    printf("3- Afficher l'abre en arborescence\n");
    printf("4- Afficher les feuilles\n");
    printf("5- Predire\n");
    printf("6- Quitter\n");
    printf("\n\nQue voulez-vous faire ?");
    scanf("%s",choix);
    if((int)choix[0]>57 || (int)choix[0]<48 || (int)choix[1]!=0 )
    {
        printf("Erreur, veuillez recommencer:\n\n");
        menu(arbre1,arbre2,arbre3,y);
    }
    else
    {
        switch (((int)choix[0]-48))
        {
            case 1:
                printf("\n\nHauteur de l'arbre :%d\n\n",height(arbre));
                menu(arbre1,arbre2,arbre3, y);
                break;
            case 2:
                printf("\nLe nombre de feuille est :%d\n\n",nombre_feuilles(arbre));
                menu(arbre1,arbre2,arbre3,y);
                break;
            case 3:
                printf("\n--------------------");
                printf("| ARBRE DE DECISION |");
                printf("--------------------\n\n");
                affichage_arborescence(arbre, 0,p_compt); printf("\n");
                menu(arbre1,arbre2,arbre3,y);
                break;
            case 4:
                printf("\nVOICI LES %d FEUILLES:\n\n",nombre_feuilles(arbre));
                affichage_feuille(arbre,p_compt);
                menu(arbre1,arbre2,arbre3,y);
                break;
            case 5:
                //predire_main(arbre);
                predire_menu(arbre1, arbre2, arbre3);
                menu(arbre1,arbre2,arbre3,y);
                break;
            case 6:
                printf("\nAu revoir!\n\n");
                break;
            default:
                printf("Veuillez saisir une bonne valeure:\n\n");
                menu(arbre1,arbre2,arbre3,y);
                break;
        }
        
    }
}
int main(int argc, const char * argv[])
{
    printf("--------------Projet Henri de Montalembert---------------\n\n");
    matrice_donnees * Mat = (matrice_donnees*)malloc(sizeof(matrice_donnees));
    Mat = charger_donnnees("iris.txt");
    int y =0 ;
    double seuil_max = 0;
    double seuil_min = 0;
    double nb_indiv_minim = 0;
    double hauteur_max=0;
    printf("Saisir la valeur de Y a predire:\n1- iris setosa\n2- iris versicolor\n3- iris verginica\n");
    scanf("%d",&y);
    printf("\n\nSaisir un seuil minimal (en %%) :");
    scanf("%lg",&seuil_min);
    printf("\nSaisir un seuil maxinal (en %%) :");
    scanf("%lg",&seuil_max);
    printf("\nSaisir le nombre minimal d'individu que vous souhaitez :");
    scanf("%lg",&nb_indiv_minim);
    printf("\nSaisir la hauteur maximal de l'arbre que vous voulez :");
    scanf("%lg",&hauteur_max);
    printf("\n\n");
    noeud * arbre1 = initialisation_racine(Mat, 1);
    noeud * arbre2 = initialisation_racine(Mat, 2);
    noeud * arbre3 = initialisation_racine(Mat, 3);
    creat_arbre(arbre1, seuil_min,seuil_max, nb_indiv_minim,hauteur_max);
    creat_arbre(arbre2, seuil_min, seuil_max,nb_indiv_minim, hauteur_max);
    creat_arbre(arbre3, seuil_min, seuil_max,nb_indiv_minim, hauteur_max);
    menu(arbre1,arbre2,arbre3,y);
    liberer_donnees(Mat);
  
    return 0;
}

