#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/graph.h"

StrGr createGraphe(Shu matrix[NBA][VERT], int nbs,int nbstr) {
    StrGr g = {0,nbs,nbstr,NBA,NULL,NULL};

    //on commence a partir de brin 1
    int nstr = 1;

    // Allocations de la mémoire
    g.node = (short * ) calloc(1,g.nbs * sizeof(short));
    // + 1 car on compte aussi le brin 0
    g.nxt = (Strand * ) calloc(1,(g.nbrStr + 1) * sizeof(Strand));

    for (int i = 0; i < g.edge; i++, nstr++) {
        // La premiere valeur du tableau de la matrice aura 
        // un brin -n
        g = assignStrand(g, matrix[i][0], -nstr,matrix[i][2]);
        g = assignStrand(g, matrix[i][1], nstr,matrix[i][2]);
    }

    return g;
}

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
        // Si à l'index du premier brin du sommet
        // on trouve un brin suivant
        if (g.nxt[fstr+NBA].next != 0) {

            // On echange le brin suivant du premier brin
            // avec le brin n
            g.nxt[nstr+NBA] = g.nxt[fstr+NBA];
            g.nxt[fstr+NBA] = str;

        } 
        else {
            // On crée à l'index du premier brin du sommet
            // un brin suivant qui correspond au brin n
            g.nxt[fstr+NBA] = str;

            // On crée un brin suivant qui sera la valeur
            // du premier brin du sommet à l'index du brin n
            str.next = fstr;
            str.node = node;
            str.time = time;
            g.nxt[nstr+NBA] = str;
        }

    }
    return g;
}

