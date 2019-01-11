//
//  vector.c
//  TD4bis
//
//  Created by henri de Montalembert on 24/11/2017.
//  Copyright © 2017 henri de Montalembert. All rights reserved.
//

#include "vector.h"
#include <stdlib.h>
#include <stdbool.h>

vector* create_vector()
{
    vector * Vect = (vector*)malloc(sizeof(vector));
    Vect->taille_logique = 0 ;
    Vect->taille_physique = 0 ;
    Vect->contenu = NULL ;
    return Vect ;
    
}

bool is_null_or_empty(vector const * p_vec)
{
    
    bool result = false ;
    if(p_vec == NULL) return true ;
    return result;
    
}

bool add(double element, vector * p_vec)
{
    bool result = false;
    if (p_vec->taille_logique == (*p_vec).taille_physique)
    {
        p_vec->taille_physique = p_vec->taille_physique+ 1 ;
        p_vec->taille_logique = p_vec->taille_logique+ 1 ;
        double * Cont = (double*)malloc(sizeof(double)*(p_vec->taille_logique ));
        for(int i = 0 ; i < p_vec->taille_logique-1 ; i++)
        {
            Cont[i] = p_vec->contenu[i];
            
            
        }
        Cont[p_vec->taille_logique-1] = element;
        p_vec->contenu = Cont ;
        //printf("%lf", p_vec->contenu[0]);
        
        result = true;
    }
    else
    {
        p_vec->taille_logique +=1;
        p_vec->contenu[p_vec->taille_logique-1] = element;
        
    }
    
    return true;
}

unsigned int size(vector const * p_vec)
{
    
    return p_vec->taille_logique;
}

bool est_dans_le_vecteur(vector * vec , int n)
{
    bool test = false ;
    for(int i = 0 ; i < vec->taille_logique ; i++)
    {
        if(vec->contenu[i] == n) test = true ;
    }
    return test ;
}

double * element_at(unsigned int index, vector const * p_vec)
{
    if(index <= p_vec->taille_logique)
    {
        return p_vec->contenu+index;
    }
    return NULL;
}

bool remove_at(unsigned int index, vector * p_vec)
{
    bool result = false;
    if(index < p_vec->taille_logique)
    {
        p_vec->taille_logique -= 1 ;
        for(int i = index; i < p_vec->taille_logique; i++)
        {
            p_vec->contenu[i] = p_vec->contenu[i+1];
        }
        result = true;
    }
    return result ;
}

void delete_vector(vector * p_vec)
{
    
    free(p_vec->contenu);
    p_vec->contenu = NULL;
    free(p_vec);
    p_vec=NULL;
}
