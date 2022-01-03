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
    int src = 0;
    printf("Vous voulez le plus court chemin depuis quel stations ?\n");

    if( scanf("%d", &src) != 1 )
        return 0;

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

/**
 * @brief Pourquoi utiliser Brins ?
 * L'avantage de Brins pour l'instant, c'est que on peut acceder directement au 
 * successeur d'un noeud grâce aux systeme de brin, ça nous évite de faire une boucle
 * afin de vérifier si telle noeud est successeur de du noeud qu'on visite
 * Elle prend beaucoup moins qu'une simple matrice
 * 
 * Conclusion : 
 * Le parcours est tres rapide (je pense c'est une complexité en N Log(n) mais pas sur)
 * Mais Cela prend enormement de mémoire (une arrete = 2 brin du coup il faut dra reserver 2 fois
 * le nombre d'arete en mémoire)
 */

/**
 * @brief Pourquoi utiliser Matrice Compacte
 * La raison principale est pour le stockage, et pour le temps d'execution,
 * on ignorera les 0 
 */