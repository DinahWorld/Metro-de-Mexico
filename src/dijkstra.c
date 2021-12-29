#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>

#include "include/graph.h"


int minDistance(int dist[], char sptSet[]){
    int min = 999, min_index = 0;

    for (int v = 0; v < NODE; v++){
        if (sptSet[v] == 0 && dist[v] <= min){
            min = dist[v], min_index = v;
        }
    }
    return min_index;
}

// A utility function to print the constructed distance array
void printSolution(int dist[],int start){
    FILE* stream = fopen("mexico_station.txt","r");
    char line[1024] = {0};
    char station[163][50] = {0};
    char* tok = NULL;

    Shu i = 0;
    Shu y = 0;
    while (fgets(line, 1024, stream)){
        char* tmp = strdup(line);
         for (tok = strtok(tmp, "|");tok && *tok;tok = strtok(NULL, "|\n")){
            if(i == 1){
                i = 0;
                strcpy(station[y],tok);
            }else{
                i = 1;
                y = strtol(tok, NULL, 10);
            }
        }
        i = 0;
        free(tmp);
    }
    fclose(stream);

    printf("Temps depuis :\t Stations\n");
    printf("%s \n",station[start]);
    for (int i = 0; i <NODE; i++)
        printf("%d \t\t %s\n",dist[i],station[i]);
}
 

void dijkstraForStrand(StrGr g,int start){
    int dist[NODE],fstr,nxtstr,str,node;
    node = 999;
    str = 999;
    int countLoop = 0;
    int countInsideLoop = 0;
    // Tableau qui nous renvoi true si à l'indice du noeud
    // Le noeud a été visité 
    char sptSet[NODE]; 

    for(int i = 0; i < NODE;i++){
        dist[i] = 999;
        sptSet[i] = 0;
    }
    dist[start] = 0;
    
    // Dans le meilleurs cas on a une constance en O(N)
    for(int count = 0; count < NODE;count++){
        int u =  minDistance(dist, sptSet);
        sptSet[u] = 1;
        countLoop++;
        /* Je recupere le premier brin */
        fstr = g.node[u]; 
        /* je recupere le brin suivant */
        nxtstr = g.nxt[fstr + NBA].next; 
        
        // On considere que lorsque le brin suivant sera égale au premier brin
        // on a regardé tout les successeur du sommet
        // Dans le pire cas, on a une complexité en O(N)
        // si le nombre de successeur était le nombre de noeud totale
        // dans le meilleur cas O(1) 
        while(fstr != str){
            countInsideLoop++;
            str = nxtstr;
            // On explore tout les successeur du sommet uniqument
            nxtstr = g.nxt[str + NBA].next;
            node = g.nxt[(-nxtstr)+NBA].node;

            if(!sptSet[node] && dist[u] != 999
            && dist[u] + g.nxt[str + NBA].time < dist[node]){
                dist[node] = dist[u] + g.nxt[str + NBA].time;
            }

        }
    
    }
    printf("Nombre de boucle extérieur : %d\n",countLoop);
    printf("Nombre de boucle intérieur : %d\n",countInsideLoop);
    printSolution(dist,start);

}

// Compléxité en O(n²) ou O(n*m) mais étant donnée m que sera toujours plus
// grand que n on préfera dire O(n²)
void dijkstraForCptMat(MatCpt mat, int start){
    int dist[NODE]; 

    char sptSet[NODE];
    int countLoop = 0;
    int countInsideLoop = 0;
    
    for (int i = 0; i < NODE; i++)
        dist[i] = 999, sptSet[i] = 0;
 
    dist[start] = 0;
 
    for (int count = 0; count < NODE; count++) {
        int u = minDistance(dist, sptSet);
        countLoop++;

        sptSet[u] = 1;
 
        for (int v = 0; v < NBA; v++){
            countInsideLoop++;
            if(mat.ares[v].i == u){
                if (!sptSet[mat.ares[v].j] && dist[u] != 999
                    && dist[u] + mat.ares[v].val < dist[mat.ares[v].j]){
                        dist[mat.ares[v].j] = dist[u] + mat.ares[v].val;
                    }
            }
            if(mat.ares[v].j == u){
                if (!sptSet[mat.ares[v].i] && dist[u] != 999
                    && dist[u] + mat.ares[v].val < dist[mat.ares[v].i]){
                        dist[mat.ares[v].i] = dist[u] + mat.ares[v].val;
                    }
            }
        }
    }
    printf("Nombre de boucle extérieur : %d\n",countLoop);
    printf("Nombre de boucle intérieur : %d\n",countInsideLoop);
    printSolution(dist,start);
}

