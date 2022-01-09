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
#include "include/graph.h"


int main(void) {
    int src = -1;
    printf("Vous voulez le plus court chemin depuis quel stations ?\n");

    while (src < 0 || src > NODE){
        printf("Entrez un numéro de station valide !\n");
        if( scanf("%d", &src) != 1 )
            return 0;
    }

    printf("\n\n\t\tDijkstra pour un graphe avec une structure 'Brins'\n\n");
    StrGr g = getDataForStrandGraph();
    dijkstraForStrand(g,src);

    printf("\n\n\t\tDijkstra pour un graphe avec une structure 'Matrice Compacte'\n\n");
    MatCpt cpt_matrix = getDataForCompactMatrix();
    dijkstraForCptMat(cpt_matrix,src);


    free(cpt_matrix.ares);
    free(g.node);
    free(g.nxt);
    return 0;
}
