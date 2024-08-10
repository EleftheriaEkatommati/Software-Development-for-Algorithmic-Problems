#include "Graph.h"

extern vector <int> set;
extern vector <long long int> U;
extern vector <int> Y;
static vector<vector<int>> sorted_neighbors;

vector<int> E_Neighbors(int , int , DirectedGraph );                 //Kratame E kontinoterous geitones
int Min_Number_Image(vector<int> , int );                            //Briskoume apo tous E geitones ton kontinotero sto query
void GNNS_algorithm(DirectedGraph , int , int , int , int );         //Ekteloume ton algorithmo GNNS
void OutfileGNNS(DirectedGraph , int , int , int , int , int );      //Kalei tis sunarthseis gia thn ektelesh twn algorithmwn 

void Search_On_Graph_algorithm(DirectedGraph , int , int );          //Ekteloume ton algorithmo search on graph
void OutfileSearch_On_Graph_algorithm(DirectedGraph , int , int , int );  //Kalei tis sunarthseis gia thn ektelesh twn algorithmwn 