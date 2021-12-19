#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <assert.h>

#include <time.h>




typedef short unsigned Shu;
struct Strand {
    Shu node;
    short next;
    //float price; /* inutilise ici */
};
typedef struct Strand Strand;

struct StrandGraph {
    Shu nbs;
    Shu nbrStr;
	// le primier brin
    short * node; /* first strand*/
    // puis le neoud puis le brin suivant
	Strand * nxt; /* node and next strand*/
};
typedef struct StrandGraph StrGr;

/* Maintenant le graphe par liste de successeurs */
struct succsom {
    Shu y;
    Shu val;
    struct succsom * nxt;
};
typedef struct succsom succsom;
typedef struct succsom * ligne;

struct graphe {
    int nbs;
    ligne * tab; /* une ligne represente tous les successeurs d'un noeud*/
};
typedef struct graphe graphe;

StrGr assignStrand(StrGr g,int matrix[5][2],int i,int j,int iStr){
    int n,a;
    n = 0;
    a = 0;
    Strand node;

    if(g.node[matrix[i][j]] == 0){
        g.node[matrix[i][j]] = -iStr;
    }
    else{
        // On recupere le premier brin de notre sommet
        n = g.node[matrix[i][j]];
        a = n;
        // si le premier brin est par exemple -5 alors dans le tableau
        // il sera a l'index 5
        // si le premier brin est 5 par exemple alors dans le tableau 
        // il sera a l'index 5 + 5 = 10;
        if(n < 0) n = -n;
        else n = n + 5;
        // Si à l'index du premier brin du sommet
        // on trouve un brin suivant
        if(g.nxt[n].next != 0){
            // On echange le brin suivant du premier brin
            // avec le brin n
            g.nxt[iStr] = g.nxt[n];
            node.next =  -iStr;  //provisoire
            node.node = matrix[i][j];
            g.nxt[n] = node;
        }else{
            // On crée à l'index du premier brin du sommet
            // un brin suivant qui correspond au brin n
            node.next =  -iStr;  //provisoire
            node.node = matrix[i][j];
            g.nxt[n] = node;
    
            // On crée un brin suivant à l'index brin n
            node.next = a;
            node.node = matrix[i][j];
            g.nxt[iStr] = node;
        }
    }

    return g;   
}


StrGr createGraphe(int matrix[5][2],int nbs) {
    StrGr g;
    Strand node;

    g.nbs = nbs;
    g.nbrStr = nbs * 2;

    g.node = (short* ) malloc(((nbs *2) + 1) * sizeof(short));
    memset(g.node, 0, (size_t) ((nbs *2) + 1));

    g.nxt = (Strand* ) malloc(((nbs *2) + 1) * sizeof(Strand));	
	memset(g.nxt, 0, (size_t) ((nbs *2) + 1));
    
    g.node[0] = -0;
	node.node = 0;
    node.next = 0;
    g.nxt[0] = node;

    int iStr = 1;
    int n = 0;
    int a = 0;
    for(int i = 0;i < 5;i++){
        //Si notre sommet n'a pas de premier brin
        if(g.node[matrix[i][0]] == 0){
            g.node[matrix[i][0]] = -iStr;
        }
        else{
            // On recupere le premier brin de notre sommet
            n = g.node[matrix[i][0]];
            a = n;
            // si le premier brin est par exemple -5 alors dans le tableau
            // il sera a l'index 5
            // si le premier brin est 5 par exemple alors dans le tableau 
            // il sera a l'index 5 + 5 = 10;
            if(n < 0) n = -n;
            else n = n + 5;
            // Si à l'index du premier brin du sommet
            // on trouve un brin suivant
            if(g.nxt[n].next != 0){
                // On echange le brin suivant du premier brin
                // avec le brin n
                g.nxt[iStr] = g.nxt[n];
                node.next =  -iStr;  //provisoire
                node.node = matrix[i][0];
                g.nxt[n] = node;
            }else{
                // On crée à l'index du premier brin du sommet
                // un brin suivant qui correspond au brin n
                node.next =  -iStr;  //provisoire
                node.node = matrix[i][0];
                g.nxt[n] = node;
        
                // On crée un brin suivant à l'index brin n
                node.next = a;
                node.node = matrix[i][0];
                g.nxt[iStr] = node;
            }
        }
        
        /* Faut faire une loupe */
        //Pour quelle aille jusque en bas là en bas
        if(g.node[matrix[i][1]] == 0){
            g.node[matrix[i][1]] = iStr;
            node.next = iStr;
            node.node = matrix[i][1];
            g.nxt[iStr+5] = node;
        
        }else{
            n = g.node[matrix[i][1]];
            a = n;
            if(n < 0) n = -n;
            else n = n + 5;

            /* Faut faire une loupe */
            //Pour quelle aille jusque en bas là en bas
            if(g.nxt[n].next != 0){
                g.nxt[iStr+5] = g.nxt[n];
                node.next = iStr;  //provisoire
                node.node = matrix[i][1];
                g.nxt[n] = node;
            }else{

                node.next =  iStr;  //provisoire
                node.node = matrix[i][1];
                g.nxt[n] = node;


                node.next = a;
                node.node = matrix[i][1];
                g.nxt[iStr+5] = node;
            }
        
        }        
        iStr++;
    }

    return g;
}


void printStrGraph(StrGr g) {
    printf("\n");
    for(int i = 0;i < 11;i++){
        printf("%d ",i);
    } 
    printf("\n"); 
   for (int i = 0; i < 11;i++) {
        
        printf("|%d ",g.nxt[i].node);
        printf("%d ",g.nxt[i].next);
        //printf("%d |",g.nxt[brin].next);
    }

}


void insert(StrGr g, int num, Shu nod) {

}


void seegr(StrGr g) {
    int i, size, adv;
    size = (g.nbrStr) + 1;
    adv = size >> 1;
    for (i = 0; i < g.nbs; i++)
        printf("%2d %3d| ", i, g.node[i]);
    printf("\n\n");
    for (i = 0; i < size; i++)
        printf("%3d %2d %3d| ", i - adv, g.nxt[i].node, g.nxt[i].next);
    printf("\n");
}

void printPath(Shu * flag, int nbn) {
    int i;
    printf("voici un path \n");
    for (i = 0; i < nbn; i++) {
        if (flag[i])
            printf("%3d : %3d\t", i, flag[i]);
    }
    printf("\n");
}

int strandPath(Shu dep, Shu arr, StrGr g, Shu flag[], int nba) {
    // nba = nombre d'arrete
    short newbr, frstbr, neubr;
    Shu newn;
    //si la valeur actuel est égale a l'arrivé 
    // cela veut dire qu'on est arrivé au sommet voulu
    if (dep == arr) {
        //flag est de base initialisé a 0 sur tout le tableau
        flag[dep] = 1;
        return 1;
    }
    // flag = tableau vide de taille sommet * 2
    // si la valeur du tableau flag est égale a 1 on return 0
	// Sa veut dire qu'on a déjà exploré le sommet
    if (flag[dep])
        return 0;

    // On a l'indice du départ du tableau la valeur a 1
    flag[dep] = 1;
    // premie brin = brin du sommet
    frstbr = g.node[dep];
    // nouveau brin = premier brin
    newbr = frstbr;
    // fait 
    do {
        // si le nouveau brin est inférieur donc qu'il soit négatif
        if (newbr < 0) {
            /* brin de depart */
            // le brin suivant est égale à la valeur absolue du brin actuel
            // exemple : A <--(5)------(-5)--B
            // Comme on sait que la valeur positif c'est une arete sortante
            neubr = -newbr;
            //la valeur du sommet suivant = au brin + le nombre d'arrete positon
            newn = g.nxt[neubr + nba].node;
            //si la valeur de l'indice du prochain sommet est égale = 0
            if (!flag[newn])
                //Si le programme retourne 1 on return 1
                if (strandPath(newn, arr, g, flag, nba)){
                    return 1;
                }
        }
        //si newbr = est positif
        //alors sa veut dire qu'on est à l'autre brin
        //donc le nouveau brin se le brin du sommet suivant
        newbr = g.nxt[newbr + nba].next;
    } while (newbr != frstbr);
    return 0;
}


int strandPathExist(StrGr g, Shu dep, Shu arr) {
    Shu * flag;
    int alors, nbaretes;
    // nombre d'arrete = nombre de brin / 2
    nbaretes = g.nbrStr >> 1;
    // On alloue le nombre de sommet * 2 du graphe au tableau
    flag = (Shu * ) malloc(g.nbs * sizeof(Shu));
    // On remplit le tableau par 0 sur tout le tableau
    memset(flag, 0, (size_t)(g.nbs << 1));
    // nb arrete en nb sommet
    alors = strandPath(dep, arr, g, flag, nbaretes);
    return alors;
}

int main(void) {
    int nb;
    Shu to, fro;
    StrGr g;
  
        nb = 5;
    
    // ON OBTIENT LE NMBRE D ARETE EN MM TMPS
    int  matrix[5][2] = {{0,3},{1,2},{4,1},{0,4},{0,1}};
    size_t nba= sizeof(matrix); 
    
    g = createGraphe(matrix,nb);
    printStrGraph(g);
    
    fro = 4;
    to = 3;
    printf("\n");
    
    if (strandPathExist(g, fro,to))
        printf("Liste : il existe un chemin de %d a %d\n\n", fro, to);
    else
        printf("Liste : pas de chemin de %d a %d\n\n", fro, to);
    
}