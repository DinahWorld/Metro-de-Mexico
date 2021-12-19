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
    Shu edge;
    // le primier brin
    short * node; /* first strand*/
    // puis le neoud puis le brin suivant
    Strand * nxt; /* node and next strand*/
};
typedef struct StrandGraph StrGr;

// |0 0 |0 -5 |1 5 |4 -4 |4 -3 |0 4 |3 1 |2 2 |1 -2 |0 -1 |1 3  
// |0 0 |0 -5 |1 5 |4 -4 |4 -3 |0 4 |3 1 |2 2 |1 -2 |0 -1 |1 3 

// |0 0 |0 -5 |1 5 |4 4 |0 -1 |0 -4 |3 1 |2 2 |1 -2 |4 -3 |1 3 
// |0 0 |0 -5 |1 5 |4 4 |0 -1 |0 -4 |3 1 |2 2 |1 -2 |4 -3 |1 3 
StrGr assignStrand(StrGr g, int node, int nstr, int indexstr) {
    int fstr, save;
    Strand str;
    fstr = 0;
    save = 0;
    // On recupere le premier brin de notre sommet
    fstr = g.node[node];
    // Si le sommet possede un premier brin    
    if (fstr != 0) {
        save = fstr;

        // si le premier brin est par exemple -5 alors dans le tableau
        // il sera a l'index 5
        // si le premier brin est 5 par exemple alors dans le tableau 
        // il sera a l'index 5 + nb = 10;
        fstr = (fstr < 0) ? -fstr : fstr + g.edge;

        // Si à l'index du premier brin du sommet
        // on trouve un brin suivant
        if (g.nxt[fstr].next != 0) {

            // On echange le brin suivant du premier brin
            // avec le brin n
            g.nxt[indexstr] = g.nxt[fstr];
            str.next = nstr; //provisoire
            str.node = node;
            g.nxt[fstr] = str;
        } else {
            // On crée à l'index du premier brin du sommet
            // un brin suivant qui correspond au brin n
            str.next = nstr; //provisoire
            str.node = node;
            g.nxt[fstr] = str;

            // On crée un brin suivant qui sera la valeur
            // du premier brin du sommet à l'index du brin n
            str.next = save;
            str.node = node;
            g.nxt[indexstr] = str;
        }

    }
    // Si notre sommet n'a pas de premier brin
    else {
        g.node[node] = nstr;
        // on initialise son brin suivant par son le brin n
        str.next = nstr;
        str.node = node;
        g.nxt[indexstr] = str;

    }
    return g;
}

StrGr createGraphe(int matrix[6][2], int nbs,int nbstr) {
    StrGr g;
    int nstr;

    //on commence a partir de brin 1
    nstr = 1;

    //Nombres de sommets
    g.nbs = 5;
    //Nombres de brins
    g.nbrStr = nbstr;
    // Nombre d'arete
    g.edge = nbstr >> 1;

    // Allocations de la mémoire
    g.node = (short * ) malloc(g.nbs * sizeof(short));
    memset(g.node, 0, (size_t) g.nbs);
    // + 1 car on compte aussi le brin 0
    g.nxt = (Strand * ) malloc((g.nbrStr + 1) * sizeof(Strand));
    memset(g.nxt, 0, (size_t)(g.nbrStr + 1));



    for (int i = 0; i < g.edge; i++, nstr++) {
        // La premiere valeur du tableau de la matrice aura 
        // un brin -n
        g = assignStrand(g, matrix[i][0], -nstr, nstr);
        g = assignStrand(g, matrix[i][1], nstr, nstr + g.edge);
    }

    return g;
}

void printStrGraph(StrGr g) {
    printf("Tableau des premiers brin\nBrins  ");
    for (int i = 0; i < g.nbs; i++) {
        if (g.node[i] >= 0) printf(" ");
        printf("%d ", g.node[i]);
    }

    printf("\nSommet ");
    for (int i = 0; i < g.nbs; i++) {
        printf(" %d ", i);
    }
    printf("\n---\nBrins\t\t ");
    for (int i = 1; i < g.nbrStr + 1; i++) {
        (i > g.edge) ? 
        printf("+%d ", i - g.edge):
        printf("-%d ", i);
    }
    printf("\nBrins suivant\t ");
    for (int i = 1; i < g.nbrStr + 1; i++) {
        if (g.nxt[i].next >= 0) printf(" ");
        printf("%d ", g.nxt[i].next);
    }

}

void seegr(StrGr g) {
    int i, size, adv;
    size = (g.nbrStr) + 1;
    adv = size >> 1;
    printf("\n");
    for (i = 0; i < g.nbs; i++)
        printf("%2d %3d| ", i, g.node[i]);
    printf("\n\n");
    for (i = 0; i < size; i++){
        if(i == g.nbs + 1) printf("\n");
        printf("%3d %2d %3d| ", i - adv, g.nxt[i].node, g.nxt[i].next);
    }
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
                if (strandPath(newn, arr, g, flag, nba)) {
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
    int alors;
    // On alloue le nombre de sommet * 2 du graphe au tableau
    flag = (Shu * ) malloc(g.nbs * sizeof(Shu));
    // On remplit le tableau par 0 sur tout le tableau
    memset(flag, 0, (size_t)(g.nbs << 1));
    // nb arrete en nb sommet
    alors = strandPath(dep, arr, g, flag, g.edge);
    return alors;
}

int main(void) {
    int nb;
    Shu to, fro;
    StrGr g;

    // ON OBTIENT LE NMBRE D ARETE EN MM TMPS
    int matrix[6][2] = {{0,3},{1,2},{4,1},{4,0},{0,1},{2,4}};

    int num_rows = sizeof(matrix) / sizeof(matrix[0]);
    //Nombre de sommet    
    nb = 5;
    g = createGraphe(matrix, nb,num_rows*2);
    printStrGraph(g);
    //seegr(g);
    fro = 4;
    to = 3;
    printf("\n");

    if (strandPathExist(g, fro, to))
        printf("Liste : il existe un chemin de %d a %d\n\n", fro, to);
    else
        printf("Liste : pas de chemin de %d a %d\n\n", fro, to);


}