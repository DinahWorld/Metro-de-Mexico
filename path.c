#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

/// Fonction qui permet de savoir si un chemin existe dans notre graphe 
int strandPathExist(StrGr g, Shu dep, Shu arr) {
    Shu * flag;
    int alors;
    // On alloue le nombre de sommet * 2 du graphe au tableau
    flag = (Shu * ) malloc(g.nbs * sizeof(Shu));
    // On remplit le tableau par 0 sur tout le tableau
    memset(flag, 0, (size_t)(g.nbs << 1));
    // nb arrete en nb sommet
    alors = strandPath(dep, arr, g, flag, g.edge);
    return alors;
}

/// Fonction qui affiche notre chemin
void printPath(Shu * flag, int nbn) {
    int i;
    printf("voici un path \n");
    for (i = 0; i < nbn; i++) {
        if (flag[i])
            printf("%3d : %3d\t", i, flag[i]);
    }
    printf("\n");
}

/// Fonction qui affiche notre graphe
void printStrGraph(StrGr g) {
    printf("Tableau des premiers brin\nBrins  ");
    for (int i = 0; i < g.nbs; i++) {
        if (g.node[i] >= 0) printf(" ");
        printf("%d ", g.node[i]);
    }

    printf("\nSommet ");
    for (int i = 0; i < g.nbs; i++) {
        printf(" %d ", i);
    }
    printf("\n---\nBrins\t\t ");
    for (int i = 1; i < g.nbrStr + 1; i++) {
        (i > g.edge) ? 
        printf("+%d ", i - g.edge):
        printf("-%d ", i);
    }
    printf("\nSommet\t\t ");
    for (int i = 1; i < g.nbrStr + 1; i++) {
        if (g.nxt[i].node >= 0) printf(" ");
        printf("%d ", g.nxt[i].node);
    }
    printf("\nBrins suivant\t ");
    for (int i = 1; i < g.nbrStr + 1; i++) {
        if (g.nxt[i].next >= 0) printf(" ");
        printf("%d ", g.nxt[i].next);
    }

}

/// Fonction qui va trouver le chemin entre deux sommet
int strandPath(Shu dep, Shu arr, StrGr g, Shu flag[], int nba) {
    short newbr, frstbr, neubr;
    Shu newn;
    //si la valeur actuel est égale a l'arrivé 
    // cela veut dire qu'on est arrivé au sommet voulu
    if (dep == arr) {
        //flag est de base initialisé a 0 sur tout le tableau
        flag[dep] = 1;
        return 1;
    }
    // flag = tableau vide de taille sommet * 2
    // si la valeur du tableau flag est égale a 1 on return 0
    // Sa veut dire qu'on a déjà exploré le sommet
    if (flag[dep])
        return 0;

    // On a l'indice du départ du tableau la valeur a 1
    flag[dep] = 1;
    // premie brin = brin du sommet
    frstbr = g.node[dep];
    // nouveau brin = premier brin
    newbr = frstbr;
    // fait 
    do {
        // si le nouveau brin est inférieur donc qu'il soit négatif
        if (newbr < 0) {
            /* brin de depart */
            // le brin suivant est égale à la valeur absolue du brin actuel
            // exemple : A <--(5)------(-5)--B
            // Comme on sait que la valeur positif c'est une arete sortante
            neubr = -newbr;
            //la valeur du sommet suivant = au brin + le nombre d'arrete positon
            newn = g.nxt[neubr + nba].node;
            //si la valeur de l'indice du prochain sommet est égale = 0
            if (!flag[newn])
                //Si le programme retourne 1 on return 1
                if (strandPath(newn, arr, g, flag, nba)) {
                    return 1;
                }
        }
        //si newbr = est positif
        //alors sa veut dire qu'on est à l'autre brin
        //donc le nouveau brin se le brin du sommet suivant
        newbr = g.nxt[newbr + nba].next;
    } while (newbr != frstbr);
    return 0;
}

/*
void seegr(StrGr g) {
    int i, size, adv;
    size = (g.nbrStr) + 1;
    adv = size >> 1;
    printf("\n");
    for (i = 0; i < g.nbs; i++)
        printf("%2d %3d| ", i, g.node[i]);
    printf("\n\n");
    for (i = 0; i < size; i++){
        if(i == g.nbs + 1) printf("\n");
        printf("%3d %2d %3d| ", i - adv, g.nxt[i].node, g.nxt[i].next);
    }
    printf("\n");
}
*/


