#ifndef STR_GRAPH
#define STR_GRAPH

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


StrGr assignStrand(StrGr g, int node, int nstr, int indexstr);
StrGr createGraphe(int matrix[6][2], int nbs,int nbstr);
void printPath(Shu * flag, int nbn);
int strandPath(Shu dep, Shu arr, StrGr g, Shu flag[], int nba);
int strandPathExist(StrGr g, Shu dep, Shu arr);
void printStrGraph(StrGr g);

#endif
