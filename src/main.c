#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "include/graph.h"


int main(void) {
    Shu to, fro;

    //FILE* stream = fopen("mexico.txt","r");
    //char line[1024] = {0};
    /*Shu matrix[NBA][3] = {0};;
    const char* tok = NULL;
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
    */
    Shu matrix[5][3] = {{0,3,5},{1,2,3},{4,1,5},{0,4,3},{0,1,2}};
    // nombres de brins
    int strand = NBA << 1;

    //Nombre de sommet    
    int nbs = NODE;
    // Complexité en Log(N);
    StrGr g = createGraphe(matrix, nbs,strand);

    //printStrGraph(g);
    seegr(g);
    fro = 0;
    to = 4;
    printf("\n");

    if (strandPathExist(g, fro, to))
        printf("Liste : il existe un chemin de %d a %d\n\n", fro, to);
    else
        printf("Liste : pas de chemin de %d a %d\n\n", fro, to);
    
    //printStrGraph(g);

    free(g.node);
    free(g.nxt);
    return 0;
}