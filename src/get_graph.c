#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/graph.h"

MatCpt getDataForCompactMatrix(){
    FILE* stream = fopen("mexico.txt","r");
    Shu matrix[NBA][NBA] = {0};

    const char* tok = NULL;
    char line[1024] = {0};

    int i,y;
    i = 0;
    y = 0;
    Shu count = 0;

    // On recupere les informations de notre fichier txt
    // On stocke notre graphe dans une matrice
    while (fgets(line, 1024, stream)){
        char* tmp = strdup(line);
        for (tok = strtok(tmp, "|");tok && *tok;tok = strtok(NULL, "|\n")){
            if(count == 0)
                i = strtol(tok, NULL, 10);
            else if(count == 1)
                y = strtol(tok, NULL, 10);
            else
                matrix[i][y] = strtol(tok, NULL, 10);
            count++;
        }
        y = 0;
        i = 0;
        count = 0;
        free(tmp);
    }
    fclose(stream);

    MatCpt cpt_matrix;
    Triplet triplet;
    // On transforme notre matrice en Matrice Compacte
    cpt_matrix.ares = (Triplet *) calloc(1,NBA*sizeof(Triplet));
    int index = 0;
    for(int i = 0;i < NBA;i++){
        for(int j = 0;j < NBA;j++){
            if(matrix[i][j] != 0){
                triplet.i = i;
                triplet.j = j;
                triplet.val = matrix[i][j];
                cpt_matrix.ares[index] = triplet;
                index++;
            }
        }
    }

    return cpt_matrix;
}

StrGr getDataForStrandGraph(){
    FILE* stream = fopen("mexico.txt","r");
    Shu matrix[NBA][3] = {0};
    const char* tok = NULL;
    char line[1024] = {0};

    int i,y;
    i = 0;
    y = 0;
    // On recupere les informations de notre fichier txt
    while (fgets(line, 1024, stream)){
        char* tmp = strdup(line);
        for (tok = strtok(tmp, "|");tok && *tok;tok = strtok(NULL, "|\n")){
            matrix[i][y] = strtol(tok, NULL, 10);
            y++;
        }
        y = 0;
        i++;
        free(tmp);
    }
    
    fclose(stream);
    
    // nombres de brins
    int strand = NBA << 1;
    //Nombre de sommet    
    int nbs = NODE;

    // On retourne notre tableau de brin
    return createGraphe(matrix, nbs,strand);
}
