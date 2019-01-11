//
//  vector.h
//  TD4bis
//
//  Created by henri de Montalembert on 24/11/2017.
//  Copyright © 2017 henri de Montalembert. All rights reserved.
//

#ifndef vector_h
#define vector_h

#include <stdio.h>
#include <stdbool.h>




typedef struct
{
    int taille_logique;
    int taille_physique;
    double * contenu ;
    
}vector;


/*
 * Fonction qui crée dynamiquement vecteur, dont le contenu est vide (i.e. sans élément).
 * Retour : un pointeur sur le vecteur créé
 */

vector* create_vector(void); 



/*
 * Fonction qui teste si le vecteur est vide ou non
 * Paramètre p_vec : le (pointeur en accès en lecture seule sur le) vecteur à tester
 * Retour : true si le vecteur ne contient pas d'élément ou si p_vec est NULL; false sinon
 */
bool is_null_or_empty(vector const * p_vec);


/*
 * Fonction qui ajoute un élément à un vecteur
 * Paramètre element : l'élément à ajouter
 * Paramètre p_vec : le (pointeur sur le) vecteur dans lequel ajouter
 * Retour : true si l'ajout a pu se faire ; false sinon
 */
bool add(double element, vector * p_vec);


/*
 * Fonction qui donne (d'un point de vu logique) le nombre d'éléments contenu dans un vecteur
 * Paramètre p_vec : le (pointeur en accès en lecture seule sur le) vecteur
 * Retour : le nombre d'éléments
 */
unsigned int size(vector const * p_vec);


/*
 * Fonction qui accède à un élément dans un vecteur selon sa position
 * Paramètre index : la position de l'élément à accéder (1ère position : index 0)
 * Paramètre p_vec : le (pointeur en accès en lecture seule sur le) vecteur dans lequel accéder à l'élément
 * Retour : un accès à l'élément concerné ; NULL si accès non possible
 */
double* element_at(unsigned int index, vector const * p_vec);


/*
 * Fonction qui supprime un élément à un vecteur
 * Paramètre index : la position de l'élément à supprimer (1ère position : index 0)
 * Paramètre p_vec : le (pointeur sur le) vecteur dans lequel supprimer
 * Retour : true si la suppression a pu se faire ; false sinon
 */
bool remove_at(unsigned int index, vector * p_vec);


/*
 * Fonction qui détruit le vecteur et libère toute la mémoire associée.
 * Paramètre p_vec : le (pointeur sur le) vecteur à détruire
 * Note : penser à mettre à NULL la variable passée en paramètre après utilisation de cette fonction dans le code appelant.
 */
void delete_vector(vector * p_vec);

bool est_dans_le_vecteur(vector * vec , int n);


#endif /* vector_h */
