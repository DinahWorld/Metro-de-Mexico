#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/graph.h"

StrGr assignStrand(StrGr g, int node, int nstr, int indexstr,Shu time) {
    int fstr, save;
    Strand str;
    fstr = 0;
    save = 0;
    // On recupere le premier brin de notre sommet
    fstr = g.node[node];
    // Si le sommet possede un premier brin    
    if (fstr != 0) {
        save = fstr;

        // si le premier brin est par exemple -5 alors dans le tableau
        // il sera a l'index 5
        // si le premier brin est 5 par exemple alors dans le tableau 
        // il sera a l'index 5 + nb = 10;
        fstr = (fstr < 0) ? -fstr : fstr + g.edge;
        
 
        // Si à l'index du premier brin du sommet
        // on trouve un brin suivant
        if (g.nxt[fstr].next != 0) {

            // On echange le brin suivant du premier brin
            // avec le brin n
            g.nxt[indexstr] = g.nxt[fstr];
                   str.next = nstr; 
        str.node = node;
        str.time = time;
            
            g.nxt[fstr] = str;
        } else {
            // On crée à l'index du premier brin du sommet
            // un brin suivant qui correspond au brin n
                   str.next = nstr; 
        str.node = node;
        str.time = time;
            
            g.nxt[fstr] = str;

            // On crée un brin suivant qui sera la valeur
            // du premier brin du sommet à l'index du brin n
            str.next = save;
            str.node = node;
            str.time = time;
            g.nxt[indexstr] = str;
        }

    }
    // Si notre sommet n'a pas de premier brin
    else {
        g.node[node] = nstr;
        // on initialise son brin suivant par son le brin n
        str.next = nstr;
        str.node = node;
        str.time = time;
        g.nxt[indexstr] = str;

    }
    return g;
}

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
        g = assignStrand(g, matrix[i][0], -nstr, nstr,matrix[i][2]);
        g = assignStrand(g, matrix[i][1], nstr, nstr + g.edge,matrix[i][2]);
    }

    return g;
}
