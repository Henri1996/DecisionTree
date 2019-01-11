
#include "donnees.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vector.h"

//permet de creer le tableau d'index pour la racine de l'arbre
vector * Tab_index_racine(matrice_donnees * mat) 
{
    int compt=0;
    vector * vect = create_vector();
    for(int i = 0 ; i < mat->nb_lignes ; i++)
    {
        compt++;
        add(compt, vect);
    }
    return vect;
}

//permet de renvoyer le maximum de trois double
double max_pre(double p1 , double p2 , double p3)
{
    double max = 0;
    if(p1 > p2) max = p1;
    else max=p2;
    
    if(max < p3) max = p3;
    return max;
}
//permet de renvoyer le nombre de feuille
int nombre_feuilles(noeud const * parent)
{
    if(parent == NULL)
    {
        return 0;
    }
    if(est_feuille(parent))
    {
        return 1;
    }
    return nombre_feuilles(parent->fils_gauche) + nombre_feuilles(parent->fils_droit);
}

// renvoie true si c'est une feuille
bool est_feuille(noeud const * element)
{
    bool test = false;
    if (element != NULL)
    {
        if(element->fils_gauche == NULL && element->fils_droit == NULL)
        {
            test = true;
        }
    }
    return test ;
}

//renvoie le max de deux entiers
int max(int a , int b)
{
    if(a>b)return a;
    else return b;
}


int height_2(noeud *arbre)
{
    while(arbre->parent != NULL)
    {
        arbre=arbre->parent;
    }
    int hauteur =height(arbre);
    return hauteur;
}
//permet de renvoyer la hauteur d'un arbre
int height(noeud * arbre)
{
    
    if(arbre==NULL)
    {
        return 0 ;
    }
    else return 1 + max(height(arbre->fils_gauche), height(arbre->fils_droit));
}

// permet de trier l'arbre
//fonction que j'ai faite en td
void tri_rapide (double * tableau, int taille)
{
    int mur, courant;
    double tmp;
    double pivot;
    if (taille < 2) return;
    // On prend comme pivot l element le plus a droite
    pivot = tableau[taille - 1];
    mur  = courant = 0;
    while (courant<taille)
    {
        if (tableau[courant] <= pivot)
        {
            if (mur != courant)
            {
                tmp=tableau[courant];
                tableau[courant]=tableau[mur];
                tableau[mur]=tmp;
            }
            mur ++;
        }
        courant ++;
    }
    tri_rapide(tableau, mur - 1);
    tri_rapide(tableau + mur - 1, taille - mur + 1);
    
    
    
}

// permet de renvoyer un vector d'index en fonction du critere de division et du noeud
vector * tab_index(noeud * arbre , critere_de_division *diviseur )
{
    
    vector * vect = create_vector();// on crée le vector
    
    for(int i = 0 ; i < arbre->mat->nb_lignes ; i++)
    {
        
        if(est_dans_le_vecteur(arbre->index, i+1)) //on regarde si l'index de la matrice est dans le vecteur d'index
        {
            
            if(diviseur->caractere == '>') //on regarde si on a le critere de division du fils droit
            {
                if(arbre->mat->matrice[i][diviseur->x] > diviseur->mediane )
                {
                    add(i+1,vect);
                }
            }
            else
            {
                if(arbre->mat->matrice[i][diviseur->x] <= diviseur->mediane)// ou le fils gauche
                {
                    add(i+1,vect);
                }
            }
        }
            
    }
    
    
    return vect;
}

// permet de calculer la mediane corrigée à partir d'un tableau
double calcul_mediane(double * tab , int taille)
{
    double mediane;
    if(taille %2 == 0 )
    {
        mediane = (tab[taille/2-1]+ tab[taille/2])/2;
        
    }
    else
    {
        mediane = tab[taille/2  ];
    }
    if(mediane == tab[taille-1]) mediane = tab[taille-2];
    
    return mediane;
}

//permet de rechercher le maximum de toutes les precision pour renvoyer la position du meilleur xi
//on utilise la structure precision qui permet de stocker la precision inf et sup dans chaque case
int recherche_max(critere_de_division * critere ,precision * pre, int taille)
{
    double max=0 ;
    int position = 0 ;

    for(int i = 0 ; i < taille ; i++)
    {
        
        if(pre[i].p_inf > max || pre[i].p_sup > max)
        {
            position = i ;
            if(pre[i].p_inf > pre[i].p_sup)
            {
                max = pre[i].p_inf;
                
            }
            else max = pre[i].p_sup;
        }
    }
    
    return position +1 ;
}

//permet de rechercher le bon critere de division
//on renvoie la structure critere de division avec le bon xi, la bonne medianne et le bon caractere
critere_de_division *  chercher_diviseur(noeud * arbre , char s)
{
    critere_de_division * critere = (critere_de_division*)malloc(sizeof(critere_de_division));
    int taille = arbre->mat->nb_colonnes-1;
    double * mediane = (double*)malloc(sizeof(double)*taille);
    precision * pre = (precision*)malloc(sizeof(precision)*taille);
    
    int compt=0;
    for(int i = 0 ; i < arbre->mat->nb_colonnes-1 ; i++)
    {
       
        double * tab  = (double*)malloc(sizeof(double)*arbre->index->taille_logique);
        for(int j = 0 ; j < arbre->index->taille_logique ;j++)
        {
            int k = arbre->index->contenu[j];
            tab[j] = arbre->mat->matrice[k-1][i+1];
        }
        tri_rapide(tab, arbre->index->taille_logique);
        
        mediane[compt] = calcul_mediane(tab, arbre->index->taille_logique);
        compt++;
        
    }
    pre = chercher_div_precision(arbre, mediane, pre, arbre->y );
    
    int pos;
    pos = recherche_max(critere , pre, arbre->mat->nb_colonnes-1 );
    critere->mediane = mediane[pos-1];
    
    critere->x = pos;
    critere->caractere = s;
    return critere;
    
}

//permet de créer le noeud racine
noeud * initialisation_racine(matrice_donnees * mat, int y)
{
    noeud * racine = (noeud*)malloc(sizeof(noeud));
    racine->mat = mat;
    racine->diviseur = NULL;
    racine->index = Tab_index_racine(mat);
    racine->fils_droit =NULL;
    racine->fils_gauche=NULL;
    racine->y =y;
    racine->parent=NULL;
    racine->precision = precisionY(racine);
    return racine ;
    
}

//permet de créer les noeud fils gauche et droit a chaque fois
noeud * intitialisation_fils(noeud * arbre , critere_de_division *diviseur)
{
    noeud * racine = (noeud*)malloc(sizeof(noeud));
    racine->mat = arbre->mat ;
    racine->index = tab_index(arbre, diviseur);
    racine->fils_gauche=NULL;
    racine->fils_droit = NULL;
    racine->y=arbre->y;
    racine->precision = precisionY(racine);
    racine->parent = arbre ;
    racine->diviseur = diviseur ;
    return racine ;
}

//permet de créer l'arbre en récursivité
void creat_arbre(noeud * arbre , double precision_inf , double precision_sup ,double nb_indiv_minim, double hauteur_max)
{
   
   int hauteur = height_2(arbre);
    
    //on vérifie toutes les conditions
   if(arbre->precision < precision_sup && arbre->precision > precision_inf && hauteur <= hauteur_max && nb_indiv_minim < arbre->index->taille_logique )
   {
       //on crée le critere de division pour le fils gauche
       critere_de_division * diviseurG = chercher_diviseur(arbre, '<');
       //on crée le fils gauche
       noeud * filsGauche = intitialisation_fils(arbre, diviseurG);
       arbre->fils_gauche = filsGauche;//on affecte le fils gauche au pere
       filsGauche->parent=arbre;// et on affecte le pere au fils gauche
       
       //on fait de meme pour le fils droit
       critere_de_division * diviseurD = changer_caractere(diviseurG);
       noeud * filsDroit = intitialisation_fils(arbre, diviseurD);
       arbre->fils_droit = filsDroit;
       filsDroit->parent = arbre;
       
       //et on rappelle 'creer_arbre' avec le fils gauche puis avec le fils droit
       creat_arbre(filsGauche , precision_inf, precision_sup,nb_indiv_minim, hauteur_max);
       creat_arbre(filsDroit, precision_inf, precision_sup,nb_indiv_minim, hauteur_max);
   }
}

//permet de creer le critere de diviseur pour le fils droit (meme que celui de gauche mais avec avec le signe superieur)
critere_de_division * changer_caractere(critere_de_division * div)
{
    critere_de_division * stock = (critere_de_division*)malloc(sizeof(critere_de_division));
    stock->mediane = div->mediane;
    stock->x=div->x;
    stock->caractere = '>';
    return stock;
}

// permet de renvoyer la precision par rapport au y rentré par l'utilisateur
double  precisionY(noeud * a_noeud)
{
    int compt = 0 ;
    
    for(int z=0 ; z < a_noeud->index->taille_logique ; z++)
    {
        double i = a_noeud->index->contenu[z];
        if(a_noeud->mat->matrice[(int)i-1][0] == a_noeud->y)
        {
            compt++;
        }
    }
    if(a_noeud->index->taille_logique == 0) return 0;
    else return (double)compt/a_noeud->index->taille_logique*100;
}
// permet de trouver toutes les précisions inf et sup pour les quatres variables
//on renvoie un tableau de precision
precision * chercher_div_precision(noeud * arbre, double * med, precision * pre ,  int y )
{
    int compt2=0;
    for(int j = 1; j < arbre->mat->nb_colonnes ; j++)
    {
        // on crée des compteurs pour compter les valeur en dessous et au dessus de la mediane et dont le y est egale à celui rentré en parametre
        int compt_inf = 0;
        int compt_sup = 0;
        int compt = 0 ;// et un compteur pour compter le nombre de valeur en dessous et au dessus de la mediane
        for(int i = 0 ; i < arbre->mat->nb_lignes ; i++)
        {
            if(est_dans_le_vecteur(arbre->index, i+1))
            {
                if(arbre->mat->matrice[i][j] <= med[compt2])
                {
                    if( arbre->mat->matrice[i][0] == y) compt_inf++;
                    compt++;
                }
                else
                {
                    if(arbre->mat->matrice[i][0]== y ) compt_sup++;
                }
            }
        }
        
        pre[compt2].p_inf = (double)compt_inf/compt * 100 ;
        pre[compt2].p_sup = (double)compt_sup/(arbre->index->taille_logique-compt)*100;
        compt2++;
        
    }
    return pre;
}

//permet de predire une precision par rapport à un y grace à quatres variables rentrées en paramètre
//renvoie la précision de la feuille à laquelle on arrive après avoir parcouru l'arbre à partir des Xi
double predire(noeud * arbre, double x1 ,double x2, double x3,double x4,double precision)
{
    if(arbre->fils_gauche == NULL || arbre->fils_droit == NULL)
    {
        return precision;
    }
    else
    {
        
        double diviseur =0;
        if(arbre->fils_gauche->diviseur->x == 1 || arbre->fils_droit->diviseur->x==1)diviseur = x1;
        if(arbre->fils_gauche->diviseur->x == 2 || arbre->fils_droit->diviseur->x==2)diviseur = x2;
        if(arbre->fils_gauche->diviseur->x == 3 || arbre->fils_droit->diviseur->x==3)diviseur = x3;
        if(arbre->fils_gauche->diviseur->x == 4 || arbre->fils_droit->diviseur->x==4)diviseur = x4;
        
        if(diviseur <= arbre->fils_gauche->diviseur->mediane || diviseur <= arbre->fils_droit->diviseur->mediane)
        {
            precision = arbre->fils_gauche->precision;
            return predire(arbre->fils_gauche, x1, x2, x3, x4,precision);
        }
        else
        {
            precision = arbre->fils_droit->precision;
            return predire(arbre->fils_droit, x1, x2, x3, x4, precision);
        }
    }
 
    
}

//fonction donnée qui permet de renvoyer une matrice de données à partir d'un fichier de données
matrice_donnees* charger_donnnees(const char* nom_fichier)
{
    
    FILE* fichier = fopen(nom_fichier,"r");
    if( fichier != NULL )
    {
        unsigned int nb_lignes;
        unsigned int nb_colonnes;
        fscanf(fichier, "%u %u", &nb_lignes, &nb_colonnes);
        fgetc(fichier);
        double** matrice = (double**) malloc( nb_lignes * sizeof(double*) );
        for(int ligne = 0 ; ligne < nb_lignes ; ligne++)
        {
            matrice[ligne] = (double*) malloc( nb_colonnes * sizeof(double) );
            
            for(int colonne = 0 ; colonne < nb_colonnes ; colonne++)
            {
                if(colonne != nb_colonnes-1)
                {
                    fscanf(fichier, "%lg ", &matrice[ligne][colonne]);
                }
                else
                {
                    fscanf(fichier, "%lg" , &matrice[ligne][colonne]);
                }
            }
            
            fgetc(fichier);
        }
        matrice_donnees * data = (matrice_donnees*) malloc(sizeof(matrice_donnees));
        data->nb_colonnes = nb_colonnes;
        data->nb_lignes = nb_lignes;
        data->matrice = matrice;
        
        fclose(fichier);
        return data;
    }
    
    printf("Fichier %s inconnu.\n", nom_fichier);
    return NULL;
}
matrice_donnees* liberer_donnees(matrice_donnees * data)
{
    if(data != NULL)
    {
        for(int ligne = 0 ; ligne < data->nb_lignes ; ligne++)
        {
            if(data->matrice[ligne] != NULL) 
                free(data->matrice[ligne]);
        }
        free(data->matrice);
        free(data);
    }
    return NULL;
}

