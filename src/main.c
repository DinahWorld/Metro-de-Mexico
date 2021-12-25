/**
 * @name Metro de Mexico
 * @author Dinath
 * @brief Gérer un réseau de transports en commun,
 *  via un graphe (Système à brins et Matrice Compacte)
 *  et résoudre le cas du plus court chemin
 *  avec l'algorithme de Dijkstra
 * @version 1.0
 * @date 2021-12-23
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "include/graph.h"


int main(void){

    return 0;
}

/*
int main(void) {
    //Shu to, fro;

    // En faire une fonction pour l'utiliser pour PrintSolution et ici
    FILE* stream = fopen("mexico.txt","r");
    Shu matrix[NBA][3] = {0};
    const char* tok = NULL;
    char line[1024] = {0};

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
    
    fclose(stream);
    
    //Shu matrix[5][3] = {{0,1,2},{0,2,1},{1,4,1},{2,4,6},{2,3,4}};
    // nombres de brins
    int strand = NBA << 1;

    //Nombre de sommet    
    int nbs = NODE;
    // Complexité en Log(N);
    StrGr g = createGraphe(matrix, nbs,strand);
    dijkstra(g,0);

    //printStrGraph(g);
    //seegr(g);
    ////fro = 0;
    //to = 4;
    //printf("\n");
    //
    //if (strandPathExist(g, fro, to))
    //    printf("Liste : il existe un chemin de %d a %d\n\n", fro, to);
    //else
    //    printf("Liste : pas de chemin de %d a %d\n\n", fro, to);
    //
    ////printStrGraph(g);

    free(g.node);
    free(g.nxt);
    return 0;
}
*/

/**
 * @brief 
 * L'avantage de Brins pour l'instant, c'est que on peut acceder directement au 
 * successeur d'un noeud grâce aux systeme de brin, ça nous évite de faire une boucle
 * afin de vérifier si telle noeud est successeur de du noeud qu'on visite
 * 
 * Conclusion : 
 * Le parcours est tres rapide (je pense c'est une complexité en N Log(n) mais pas sur)
 * Mais Cela prend enormement de mémoire (une arrete = 2 brin du coup il faut dra reserver 2 fois
 * le nombre d'arete en mémoire)
 * 
 */