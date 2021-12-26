#ifndef STR_GRAPH
#define STR_GRAPH
typedef short unsigned Shu;
#define NODE 122 /* Nombres de sommets */
#define NBA 135 /* Nombres d'aretes */
#define VERT 3 /* Nombres d'éléments dans la matrice */

struct Strand {
    Shu node;
    short next;
    Shu time;
};
typedef struct Strand Strand;

struct StrandGraph {
    Shu timeCount;
    Shu nbs;
    Shu nbrStr;
    Shu edge;   /* aretes */
    short * node; /* first strand*/
    Strand * nxt; /* node and next strand*/
};
typedef struct StrandGraph StrGr;
struct Triplet{
    int i;
    int j;
    Shu val;
};
typedef struct Triplet Triplet;
struct CompactMatrix{
    int nbs;
    int nba;
    struct Triplet * ares;
};
typedef struct CompactMatrix MatCpt;


StrGr createGraphe(Shu matrix[NBA][VERT], int nbs,int nbstr);
StrGr assignStrand(StrGr g, int node, int nstr,Shu time);
int strandPathExist(StrGr g, Shu dep, Shu arr);
int strandPath(Shu dep, Shu arr, StrGr g, Shu flag[], int nba);
void printPath(Shu * flag, int nbn);
void printStrGraph(StrGr g);
void seegr(StrGr g);
int minDistance(int dist[], char sptSet[]);
void printSolution(int dist[],int start);
void dijkstraForStrand(StrGr g,int start);
void dijkstraForCptMat(MatCpt mat, int start);

#endif
