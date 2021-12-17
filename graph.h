#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <assert.h>

#include <time.h>



/* Sommet ------ -brin ------- sommet -------- brin --------- deuxieme sommet
/* objectif mettre en place la structure de brins*/
typedef short unsigned Shu;
struct strand {
    Shu node;
    short next;
    float price; /* inutilise ici */
};
typedef struct strand strand;
typedef struct strand *stra;

struct strandgraph {
    Shu nbs;
    Shu nbstr;
	// le primier brin
    short * node; /* first strand*/
    // puis le neoud puis le brin suivant
	stra * nxt; /* node and next strand*/
};
typedef struct strandgraph strgr;

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
graphe creegraphe(int nbs) {
    Shu i, j, flag, num;
    float v, taux;
    graphe g;
    ligne l, ptl;
    g.nbs = nbs;
    taux = 25.0;
    num = nbs / 10;
    while (num > 1) {
        num /= 5;
        taux /= 3.0;
    }
    taux /= 100.0;
    printf("taux %g\n", taux);

    g.tab = (ligne * ) malloc(nbs * sizeof(ligne));
    memset(g.tab, 0, (size_t) nbs * 8);
    
	/*
    srand(time(NULL));
    */
    for (i = 0; i < nbs; i++) {
        for (j = 0; j < nbs; j++) {
            v = (float) rand() / RAND_MAX;
            flag = v < taux ? (int)(v * 1000) : 0;
            if (flag) {
				// Je crée mon noeud
                ptl = (ligne) malloc(sizeof(succsom));
                // je lui met les valeurs
				ptl -> y = j;
                ptl -> val = flag;
				// je lui dit que je suis le succeseur de tab i
                ptl -> nxt = g.tab[i];
                g.tab[i] = ptl;
            }
        }
    }
    return g;
}

strgr create_brin_graph(int nbs) {
    Shu i, j, flag, num;
    float v, taux;
    strgr g;
    ligne l, ptl;
	stra brin;
    g.nbs = nbs;
    taux = 25.0;
    num = nbs / 10;
    while (num > 1) {
        num /= 5;
        taux /= 3.0;
    }
    taux /= 100.0;
    printf("taux %g\n", taux);

	// J'alloue le nombre de sommet à mon pointeur
	g.node = (short* ) malloc(nbs * sizeof(short));
	g.nxt = (short* ) malloc(nbs * sizeof(short));
	// je le remplit 
	memset(g.node, 0, (size_t) nbs << 1);
    
	/*
    srand(time(NULL));
    */
   int brin_n = 1;
   
	// la valeur du premier brin
	g.node[brin_n] = -brin_n;
	// Je crée mon deuxieme brin
	brin = (stra) malloc(sizeof(stra));
    // je lui met la valeur du sommet
	brin -> node = 5;
	// La valeur du deuxieme brin
	brin -> next = brin_n;

    g.nxt[i] = brin;
	brin_n++;

    return g;
}


void bienvoirgraf(graphe g) {
    Shu i, nb;
    ligne l;
    nb = g.nbs;
    printf("Graphe\n");
    for (i = 0; i < nb; i++) {
        l = g.tab[i];
        printf(" ligne %3d\t", i);
        while (l) {
            printf("%3u %5u  ", l -> y, l -> val);
            l = l -> nxt;
        }
        printf("\n");
    }
}
void voirgraf(graphe g) {
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
void voirgrafbrin(graphe g) {
    Shu i, nb;
    ligne l;
    nb = g.nbs;
    printf("Graphe brin\n");
	
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
void insert(strgr g, int num, Shu nod) {

}
strgr transforme(graphe g) {
    Shu i;
    int nbstr, size_str, nbz;
    ligne l;
    strgr newg;

    return newg;
}

void seegr(strgr g) {
    int i, size, adv;
    size = (g.nbstr) + 1;
    adv = size >> 1;
    for (i = 0; i < g.nbs; i++)
        printf("%2d %3d| ", i, g.node[i]);
    printf("\n\n");
    for (i = 0; i < size; i++)
        printf("%3d %2d %3d| ", i - adv, g.nxt[i].node, g.nxt[i].next);
    printf("\n");
}
int chemin(Shu dep, Shu arr, graphe g, Shu flag[]) {
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
            if (chemin(new, arr, g, flag))
                return 1;
        l = l -> nxt;
    }
    return 0;
}
void affichechemin(Shu * flag, int nbn) {
    int i;
    printf("voici un chemin \n");
    for (i = 0; i < nbn; i++) {
        if (flag[i])
            printf("%3d : %3d\t", i, flag[i]);
    }
    printf("\n");
}
int existe_chemin(Shu dep, Shu arr, graphe g) {
    Shu * flag;
    int alors;
    flag = (Shu * ) malloc(g.nbs * sizeof(Shu));
    memset(flag, 0, (size_t)(g.nbs << 1));
    alors = chemin(dep, arr, g, flag);
    return alors;
}

int cheminbr(Shu dep, Shu arr, strgr g, Shu flag[], int nba) {
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
                if (cheminbr(newn, arr, g, flag, nba))
                    return 1;
        }
        //si newbr = est positif
        //alors sa veut dire qu'on est à l'autre brin
        //donc le nouveau brin se le brin du sommet suivant
        newbr = g.nxt[newbr + nba].next;
    } while (newbr != frstbr);
    return 0;
}


int exist_che_br(strgr g, Shu dep, Shu arr) {
    Shu * flag;
    int alors, nbaretes;
    // nombre d'arrete = nombre de brin * 2
    nbaretes = g.nbstr >> 1;
    // On alloue le nombre de sommet * 2 du graphe au tableau
    flag = (Shu * ) malloc(g.nbs * sizeof(Shu));
    // On remplit le tableau par 0 sur tout le tableau
    memset(flag, 0, (size_t)(g.nbs << 1));

    alors = cheminbr(dep, arr, g, flag, nbaretes);
    return alors;
}
int main(int argc, char ** argv) {
    graphe g;
    int nb, nbstr, size_str;
    Shu to, fro;
    strgr gg;
    if (argc == 2)
        nb = atoi(argv[1]);
    else
        nb = 10;
    g = creegraphe(nb);
    voirgraf(g);
    to = nonzeros(g);
    printf("Pour %d il y a %d cases non vides\n soit %f %% \n", nb, to, (to * 100.0) / (nb * nb));
    to = 6;
    if (to >= nb)
        to = nb - 1;
    fro = 2;
    if (existe_chemin(fro, to, g))
        printf("Liste : il existe un chemin de %d a %d\n\n", fro, to);
    else
        printf("Liste : pas de chemin de %d a %d\n\n", fro, to);
    gg = transforme(g);
    seegr(gg);
    if (exist_che_br(gg, fro, to))
        printf("Brins : il existe un chemin de %d a %d\n", fro, to);
    else
        printf("Brins : pas de chemin de %d a %d\n", fro, to);
}
// J'alloue le nombre de sommet à mon pointeur
	g.node = (short* ) malloc(nbs * sizeof(short));
	g.nxt = (short* ) malloc(nbs * sizeof(short));
	// je le remplit 
	memset(g.node, 0, (size_t) nbs << 1);
    
	/*
    srand(time(NULL));
    */
   int brin_n = 1;
   
	// la valeur du premier brin
	g.node[brin_n] = -brin_n;
	// Je crée mon deuxieme brin
	brin = (str) malloc(sizeof(str));
    // je lui met la valeur du sommet
	brin -> node = 5;
	// La valeur du deuxieme brin
	brin -> next = brin_n;

    g.nxt[i] = brin;
	brin_n++;
