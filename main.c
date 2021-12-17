#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <assert.h>

#include <time.h>



/* Sommet ------ -brin ------- sommet -------- brin --------- deuxieme sommet
/* objectif mettre en place la structure de brins*/
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


graphe createGraphe(int nbs) {
    Shu i, j, flag, num;
    float v, taux;
    graphe g;
    ligne l, ptl;
    g.nbs = nbs;
    /*
    srand(time(NULL));
    */
   // (0 3) (1 2) (4 1) (4 0) (0 1)
   // 0   3 1
   // 1   2
   // 2   
   // 3  
   // 4  1 0

    int  matrix[5][2] = {{0,3},{1,2},{4,1},{4,0},{0,1}};
    int inode = 0;
    g.tab = (ligne * ) malloc(nbs * sizeof(ligne));
    memset(g.tab, 0, (size_t) nbs * 8);


    for(int i = 0;i < 5;i++){
        inode = matrix[i][0];
        l = g.tab[inode];
        ptl = (ligne) malloc(sizeof(succsom));
        ptl -> y = matrix[i][1];
        ptl -> val = matrix[i][1];
        ptl -> nxt = NULL;

        // On ajoute à la fin de la liste chainé notre successeur
        //Si notre tableau n'est pas null alors cela veut dire qu'il y a un noeud suivant
        if(l != NULL){
            //on parcours la liste chainé
            //Lorsqu'une prochaine liste sera vide alors on dira qu'on a atteint la fin de la liste
            while(l->nxt != NULL){
                l = l->nxt;
            }
            //On indique à notre dernier noeud (avant null) que son successeur sera le noeud ptl 
            l->nxt = ptl;
        }
        else{
            g.tab[inode] = ptl;    
        }
    }
    
    return g;
}

void printGraph(graphe g) {
    Shu i, nb;
    ligne l;
    nb = g.nbs;
    printf("Graphe\nLignes\n");
    for (i = 0; i < nb; i++) {
        l = g.tab[i];
        printf(" %3d\t", i);
        while (l) {
            printf("%3u ", l -> y);
            l = l -> nxt;
        }
        printf("\n");
    }
}

void printStrGraph(StrGr g) {
    printf("\n");
   for (int i = 0; i < 20; i++) {
        printf("|%d ",g.node[i]);
        printf("%d |",g.nxt[i].node);
    }


}


void insert(StrGr g, int num, Shu nod) {

}

StrGr graphToStrGr(graphe g) {
    Shu i;
    int nbrStr, size_str, nbz;
    ligne l;
    StrGr newg;
	int nb = g.nbs;
	nbrStr = nb * 2;
    Strand node;

	newg.node = (int* ) malloc(nbrStr *sizeof(int));
    newg.nxt = (Strand* ) malloc(nbrStr * sizeof(Strand));
	
    memset(newg.node, 0, (size_t) nbrStr * sizeof(int));
	memset(newg.nxt, 0, (size_t) nbrStr * sizeof(Strand));
    
    newg.nbs = 10;
    newg.nbrStr = 10 * 2;
    
    newg.node[0] = -0;
	node.node = 0;
    node.next = 0;
    newg.nxt[0] = node;
	printf("%d s\n",newg.nxt[0].node);

	int int_brin = 1;
	printf("Transformation\n");
    for (i = 0; i < nb; i++) {
        l = g.tab[i];
		newg.node[int_brin] = -int_brin;
		node.node = i+ 1;
        node.next = i+1;
        newg.nxt[int_brin] = node;
        while (l) {
            newg.node[int_brin + nb] = int_brin;
            node.node = l->y;
            node.next = i;
		    newg.nxt[int_brin + nb] = node;            
            int_brin++;
            l = l -> nxt;
        }
    }
    return newg;
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

int path(Shu dep, Shu arr, graphe g, Shu flag[]) {
    Shu new;
    ligne l;
    if (dep == arr) {
        flag[dep] = 1;
        return 1;
    }
    if (flag[dep])
        return 0;
    l = g.tab[dep];
    flag[dep] = 1;
    while (l) {
        new = l -> y;
        if (!flag[new])
            if (path(new, arr, g, flag))
                return 1;
        l = l -> nxt;
    }
    return 0;
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

int pathExist(Shu dep, Shu arr, graphe g) {
    Shu * flag;
    int alors;
    flag = (Shu * ) malloc(g.nbs * sizeof(Shu));
    memset(flag, 0, (size_t)(g.nbs << 1));
    alors = path(dep, arr, g, flag);
    return alors;
}

int strandPath(Shu dep, Shu arr, StrGr g, Shu flag[], int nba) {
    // nba = nombre d'arrete
    short newbr, frstbr, neubr;
    Shu newn;
    ligne l;
    //si la valeur actuel est égale a l'arrivé 
    // cela veut dire qu'on a parcourut tout le tableau
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
                if (strandPath(newn, arr, g, flag, nba))
                    return 1;
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
    // nombre d'arrete = nombre de brin * 2
    nbaretes = g.nbrStr >> 1;
    // On alloue le nombre de sommet * 2 du graphe au tableau
    flag = (Shu * ) malloc(g.nbs * sizeof(Shu));
    // On remplit le tableau par 0 sur tout le tableau
    memset(flag, 0, (size_t)(g.nbs << 1));

    alors = strandPath(dep, arr, g, flag, nbaretes);
    return alors;
}

int nonzeros(graphe g) {
    Shu i, nbz;
    ligne l;
    nbz = 0;
    for (i = 0; i < g.nbs; i++) {
        l = g.tab[i];
        while (l) {
            nbz++;
            l = l -> nxt;
        }
    }
    return nbz;
}

int main(int argc, char ** argv) {
    graphe g;
    int nb, nbrStr, size_str;
    Shu to, fro;
    StrGr gg;
    if (argc == 2)
        nb = atoi(argv[1]);
    else
        nb = 5;
    g = createGraphe(nb);
    printGraph(g);
    printf("Pour %d il y a %d cases non vides\n soit %f %% \n", nb, to, (to * 100.0) / (nb * nb));
    to = 3;
    if (to >= nb)
        to = nb - 1;
    fro = 0;
    if (pathExist(fro, to, g))
        printf("Liste : il existe un path de %d a %d\n\n", fro, to);
    else
        printf("Liste : pas de path de %d a %d\n\n", fro, to);
    gg = graphToStrGr(g);
    printStrGraph(gg);
}