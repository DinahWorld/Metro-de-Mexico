#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/graph.h"

/// Fonction pour créer un Graphe avec Brins
StrGr createGraphe(Shu matrix[NBA][VERT], int nbs,int nbstr) {
    StrGr g = {0,nbs,nbstr,NBA,NULL,NULL};

    //on commence a partir de brin 1
    int nstr = 1;
    // Allocations de la mémoire
    g.node = (short * ) calloc(1,g.nbs * sizeof(short));
    // + 1 car on compte aussi le brin 0
    g.nxt = (Strand * ) calloc(1,(g.nbrStr + 1) * sizeof(Strand));

    // Compléxité en Temps O(n) n qui correspond aux nombre d'aretes
    for (int i = 0; i < g.edge; i++, nstr++) {
        // La premiere valeur du tableau de la matrice aura 
        // un brin -n
        g = assignStrand(g, matrix[i][0], -nstr,matrix[i][2]);
        g = assignStrand(g, matrix[i][1], nstr,matrix[i][2]);
    }

    return g;
}

/// Fonction qui assigne un brin pour chaque sommet
StrGr assignStrand(StrGr g, int node, int nstr,Shu time) {
    Strand str;
    // On recupere le premier brin de notre sommet
    int fstr = g.node[node];

    str.next = nstr; 
    str.node = node;
    str.time = time;

    // Si le sommet ne possede pas de premier brin    
    if (!fstr) {
        g.node[node] = nstr;
        // on initialise son brin suivant par le brin n
        g.nxt[nstr+NBA] = str;
    }
    // Si notre sommet possede un premier brin
    else {
        // On echange le brin suivant du premier brin
        // avec le brin n
        g.nxt[nstr+NBA] = g.nxt[fstr+NBA];
        g.nxt[fstr+NBA] = str; 
    }
    return g;
}

