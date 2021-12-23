/**
 *@name Metro de Mexico
 *@author Dinath
 *@brief Gérer un réseau de transports en commun,
 *via un graphe (Système à brins et Matrice Compacte)
 *et résoudre le cas du plus court chemin
 *avec l'algorithme de Dijkstra
 *@version 1.0
 *@date 2021-12-23
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>
#include "include/graph.h"

int minDistance(int dist[], bool sptSet[]) {
    // Initialize min value
    int min = 999, min_index = 0;
    for (int v = 0; v < NODE; v++) {
        if (sptSet[v] == false && dist[v] <= min) {
            min = dist[v], min_index = v;
        }
    }
    return min_index;
}
// A utility function to print the constructed distance array
void printSolution(int dist[], int start) {
    FILE * stream = fopen("mexico_station.txt", "r");
    char line[1024] = {0};
    char station[163][50] = {0};
    char * tok = NULL;
    Shu i = 0;
    Shu y = 0;

    while (fgets(line, 1024, stream)) {
        char * tmp = strdup(line);
        for (tok = strtok(tmp, "|"); tok && * tok; tok = strtok(NULL, "|\n")) {
            if (i == 1) {
                i = 0;
                strcpy(station[y], tok);
            } else {
                i = 1;
                y = strtol(tok, NULL, 10);
            }
        }
        i = 0;
        free(tmp);
    }
    fclose(stream);

    printf("Temps depuis :\t Stations\n");
    printf("%s \n", station[start]);
    
    for (int i = 0; i < NODE; i++)
        printf("%d \t\t %s\n", dist[i], station[i]);
}
void dijkstra(StrGr g, int start) {
    int dist[NODE], fstr, nxtstr, str, node;
    node = 999;
    str = 999;

    // Tableau qui nous renvoi true si à l'indice du noeud
    // Le noeud a été visité 
    bool sptSet[NODE];

    for (int i = 0; i < NODE; i++) {
        dist[i] = 999;
        sptSet[i] = false;
    }

    dist[start] = 0;
    for (int count = 0; count < NODE; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;
        // Je recupere le premier brin
        fstr = g.node[u];
        
        // je recupere le brin suivant 
        nxtstr = g.nxt[fstr + NBA].next; 
        
        // On considere que lorsque le brin suivant sera égale au premier brin
        // on a regardé tout les successeur du sommet
        while (fstr != str) {
            str = nxtstr;
            // On explore tout les successeur du sommet uniqument
            nxtstr = g.nxt[str + NBA].next;
            node = g.nxt[(-nxtstr) + NBA].node;
        
            if (!sptSet[node] && dist[u] != 999 &&
                dist[u] + g.nxt[str + NBA].time < dist[node]) {
                if(node == 10)
                dist[node] = dist[u] + g.nxt[str + NBA].time;
            }
        }
    }
    printSolution(dist, start);
}
int main(void) {
    //Shu to, fro;
    FILE * stream = fopen("mexico.txt", "r");
    Shu matrix[NBA][3] = {
        0
    };
    const char * tok = NULL;
    char line[1024] = {
        0
    };
    int i, y;
    i = 0;
    y = 0;
    while (fgets(line, 1024, stream)) {
        char * tmp = strdup(line);
        for (tok = strtok(tmp, "|"); tok && * tok; tok = strtok(NULL, "|\n")) {
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
    StrGr g = createGraphe(matrix, nbs, strand);
    dijkstra(g, 12);
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
/**
 *@brief 
 *L'avantage de Brins pour l'instant, c'est que on peut acceder directement au 
 *successeur d'un noeud grâce aux systeme de brin, ça nous évite de faire une boucle
 *afin de vérifier si telle noeud est successeur de du noeud qu'on visite
 * 
 *Conclusion : 
 *Le parcours est tres rapide (je pense c'est une complexité en N Log(n) mais pas sur)
 *Mais Cela prend enormement de mémoire (une arrete = 2 brin du coup il faut dra reserver 2 fois
 *le nombre d'arete en mémoire)
 *
 */