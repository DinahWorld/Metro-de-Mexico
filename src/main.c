#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "include/graph.h"


int main(void) {
    int nbs;
    Shu to, fro;
    StrGr g;

    FILE* stream = fopen("mexico.txt","r");
    char line[1024];
    Shu matrix[NBA][VERT];
    const char* tok;
    int i,y;
    i = 0;
    y = 0;
    while (fgets(line, 1024, stream))
    {
        char* tmp = strdup(line);
        for (tok = strtok(tmp, "|");tok && *tok;tok = strtok(NULL, "|\n")){
            matrix[i][y] = strtol(tok, NULL, 10);
            y++;
        }
        y = 0;
        i++;
        free(tmp);
    }
    // nombres de brins
    int strand = NBA << 1;

    //Nombre de sommet    
    nbs = NODE;
    
    // Complexité en Log(N);
    g = createGraphe(matrix, nbs,strand);
    //printStrGraph(g);
    //seegr(g);
    fro = 86;
    to = 18;
    printf("\n");

    if (strandPathExist(g, fro, to))
        printf("Liste : il existe un chemin de %d a %d\n\n", fro, to);
    else
        printf("Liste : pas de chemin de %d a %d\n\n", fro, to);

    free(g.node);
    free(g.nxt);
    return 0;
}