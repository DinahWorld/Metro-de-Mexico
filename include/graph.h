#ifndef STR_GRAPH
#define STR_GRAPH
#define NODE 122 /* Nombres de sommets */
#define NBA 136 /* Nombres d'aretes */
#define VERT 3 /* Nombres d'éléments dans la matrice */ 
typedef short unsigned Shu;
struct Strand {
    Shu node;
    short next;
    Shu time;
};
typedef struct Strand Strand;

struct StrandGraph {
    Shu nbs;
    Shu nbrStr;
    Shu edge;   /* aretes */
    short * node; /* first strand*/
    Strand * nxt; /* node and next strand*/
};
typedef struct StrandGraph StrGr;


StrGr createGraphe(Shu matrix[NBA][VERT], int nbs,int nbstr);
StrGr assignStrand(StrGr g, int node, int nstr, int indexstr,Shu time);
int strandPathExist(StrGr g, Shu dep, Shu arr);
int strandPath(Shu dep, Shu arr, StrGr g, Shu flag[], int nba);
void printPath(Shu * flag, int nbn);
void printStrGraph(StrGr g);
void seegr(StrGr g);

#endif
