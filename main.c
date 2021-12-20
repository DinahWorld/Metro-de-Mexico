#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "graph.h"


int main(void) {
    int nbs;
    Shu to, fro;
    StrGr g;

    int matrix[7][2] = {{0,3},{1,2},{4,1},{4,0},{0,1},{2,6},{2,5}};

    // nombres de brins
    int strand = (sizeof(matrix) / sizeof(matrix[0])) << 1;
    //Nombre de sommet    
    nbs = 7;
    
    // Complexité en Log(N);
    g = createGraphe(matrix, nbs,strand);
    printStrGraph(g);
    //seegr(g);
    fro = 4;
    to = 3;
    printf("\n");

    if (strandPathExist(g, fro, to))
        printf("Liste : il existe un chemin de %d a %d\n\n", fro, to);
    else
        printf("Liste : pas de chemin de %d a %d\n\n", fro, to);


}