#include "LSH.h"

class DirectedGraph                                            //Domh gia kateuthinomeno grafo
{
    private:
        int numVertices;                                       //Arithmos twn komvwn 
        vector<vector<int>> adjacencyList;                     //Lista geitniashs

    public:
        DirectedGraph(int vertices);                           //Constructor ths klashs
        void Edge_init(void);                                  //Arxikopoihsh ths listas geitniashs
        void addEdge(int from, int to);                        //Prosthetoume akmh
        void print_number_vertex();                            //Ektupwsh arithmou komvwn
        void printGraph();                                     //Ektupwsh grafou
        vector<int> edges_for_a_vertex(int number);            //Epistrefei tous komvous me tous opoious sundeetai mia sugkekrimenh akmh 
};

extern DirectedGraph graph;
void k_NN_graph(int , DirectedGraph & , int , int );           //Gemizoume ton grafo 

bool compareSecondColumn(const vector<int>& a, const vector<int>& b); 

vector<int> sort_R(vector<int> R, int number_image);           //Kanoume sort me bash tis apostaseis ta tous arithmous twn eikonwn pou einai ston pinaka R[p]
double distance(int number_image1, int number_image2);         //Ypologizoume thn eukleidia apostash metksi duo eikonwn

bool isLongestEdge(int p, int r, int t);                       //Epistrefei true an h pr einai h megalyteru akmh tou trigwnou prt
void MRNG(int , DirectedGraph & , int , int );                 //Ftiaxnei ton grafo MRNG