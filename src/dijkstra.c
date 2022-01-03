#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>

#include "include/graph.h"

void dijkstraForStrand(StrGr g,int start){

    // Va contenir les informations comme le tps et le plus court successeur d'un noeud   
    Info data[NODE];            
    int fstr,nxtstr,str,node; /* variables pour brins */
    node = 999;
    str = 999;
    // Va compter nos boucles
    int countLoop = 0;
    int countInsideLoop = 0;

    // Tableau qui nous renvoi 1 si à l'indice du noeud
    // le noeud a été visité 
    char sptSet[NODE]; 
    

    // Initialisation 
    for(int i = 0; i < NODE;i++){
        data[i].time = 999;
        sptSet[i] = 0;
    }

    // data[].node nous donne le successeur le plus court d'un noeud
    // on initialise le noeud de départ à -1
    data[start].node = -1;
    data[start].time = 0;

    for(int count = 0; count < NODE;count++){
        //On recupere la plus petite distance des noeud visité
        int u =  minTime(data, sptSet);
        // indique que le noeud u a été visité
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
        while(fstr != str){
            countInsideLoop++;
            str = nxtstr;
            // On explore tout les successeur du sommet uniqument
            nxtstr = g.nxt[str + NBA].next;
            node = g.nxt[(-nxtstr)+NBA].node;
            
            // Condition de l'algorithme de Dijstra
            if(!sptSet[node] && data[u].time != 999
            && data[u].time + g.nxt[str + NBA].time < data[node].time){
                data[node].node = u;
                data[node].time = data[u].time + g.nxt[str + NBA].time;
            }

        }
        
    
    }
    printSolution(data,start);
    printf("\n\nNombre de boucle extérieur : %d\n",countLoop);
    printf("Nombre de boucle intérieur : %d\n",countInsideLoop);
    printf("Nombre de boucles totale en comptant la boucle de la fonction minTime :\n");
    printf("%d",countInsideLoop*countLoop);

}


void dijkstraForCptMat(MatCpt mat, int start){
    // Va contenir les informations comme le tps et le plus court successeur d'un noeud   
    Info data[NODE];

    // Tableau qui nous renvoi 1 si à l'indice du noeud
    // le noeud a été visité 
    char sptSet[NODE];
    int countLoop = 0;
    int countInsideLoop = 0;

    // Initialisation 
    for (int i = 0; i < NODE; i++){
        data[i].time = 999;
        sptSet[i] = 0;
    }
    // data[].node nous donnera le successeur le plus court d'un noeud
    // data[].time nous donnera le temps le plus court pour arriver à un noeud
    // Initialisation
    data[start].node = -1;
    data[start].time = 0;
 
    for (int count = 0; count < NODE; count++) {
        //On recupere la plus petite distance des noeud visité
        int u = minTime(data, sptSet);
         // indique que le noeud u a été visité
        sptSet[u] = 1;
        countLoop++;

        for (int v = 0; v < NBA; v++){
            // On recupere le noeud et le successeur
            int iares = mat.ares[v].i; 
            int jares = mat.ares[v].j; 
            countInsideLoop++;

            // Etant donné que notre fichier metro n'inclut pas le prédécesseur 
            // comme son successeur aussi, on vérifie donc i et j

            if(iares == u){
                // Condition de l'algorithme de Dijstra
                if (!sptSet[jares] && data[u].time != 999
                    && data[u].time + mat.ares[v].val < data[jares].time){
                        data[jares].time = data[u].time + mat.ares[v].val;
                        data[jares].node = u;
                    }
            }
            if(jares == u){
                // Condition de l'algorithme de Dijstra
                if (!sptSet[iares] && data[u].time != 999
                    && data[u].time + mat.ares[v].val < data[iares].time){
                        data[iares].time = data[u].time + mat.ares[v].val;
                        data[iares].node = u;
                    }
            }
        }
    }
    printSolution(data,start);
    printf("\n\nNombre de boucle extérieur : %d\n",countLoop);
    printf("Nombre de boucle intérieur : %d\n",countInsideLoop);
    printf("Nombre de boucles totale en comptant la boucle de la fonction minTime : ");
    printf("%d\n",countInsideLoop*countLoop);    

}


int minTime(Info data[], char sptSet[]){
    int min = 999, min_index = 0;

    for (int v = 0; v < NODE; v++){
        if (sptSet[v] == 0 && data[v].time <= min){
            min = data[v].time, min_index = v;
        }
    }
    return min_index;
}

// On explore chaque successeur de chaque noeud
// que l'on explore
void printPathDijsktra(int path[NODE], int j){

    
     
}

void printSolution(Info data[],int start){
    FILE* stream = fopen("mexico_station.txt","r");
    char line[1024] = {0};
    char station[163][50] = {0};
    char* tok = NULL;
    int selectedDest = 0;

    /* Je recupere le nom des stations */

    int i = 0;
    int y = 0;
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
    
    /* J'affiche la plus courte durée qu'il faudrait pour acceder 
                    a chaque station
    */
    

    printf("Temps depuis :\t Stations\n");
    printf("%s \n",station[start]);
    for (i = 0; i <NODE; i++){
        printf("%d \t\t %s (%d)\n",data[i].time,station[i],i);
    }

    /* Demande a l'utilisateur quel chemin veut il voir */

    printf("Vous voulez voir le plus court chemin depuis %d vers quel stations ?\n",start);
    printf("Entrez un numero correspondant à une station (regardez le fichier metro_station.txt)\n");
    if( scanf("%d",&selectedDest) != 1) return;

    int j = selectedDest;
    printf("\nArrivé  = ");
    while(data[j].node != - 1){
        printf("%s <-- %d min -- ", station[j],data[j].time);
        j = data[j].node; 
    }
    printf("%s = Depart",station[start]);


}
 

