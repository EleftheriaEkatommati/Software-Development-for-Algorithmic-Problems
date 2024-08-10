#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <random>
#include <time.h>
#include <chrono>
#include <algorithm>
#include <sstream>
#include "Random.h"
using namespace std;

static vector<vector<vector<long long unsigned int>>> Euclidian_Hash_Tables;
static vector<double> t;
static vector<vector<double>> v;
static vector<vector<int>> HashFunctions_Amplified;
extern vector<int> N_Points;                            //Apothikekoume tous arithmous twn eikonwn twn N kontinoterwn geitonwn

void Hash_initialize(int);                              //Arxikopoioume tous hash tables
void HashFunctions_initialize(int, int);                //Arxikopoioume tis g sunarthseis
void Euclidian_Hash(int , int , int );                  //Gemizoume tous hash tables
void Hash_clear(int );  
long long int Euclidian_dist(int , int );               //Ypologizei thn apostash metaksi duo dianusmatwn
long long unsigned int Query_Hash(int , int , int );    //Briskei thn thesi mias eikonas sta hash tables

long long int Euclidian_dist_initial(int , int );
long long unsigned int Euclidian_Nearest_N(int );       //Briskei ton kontinotero geitona me ton exhaustive algorithmo
void Euclidian_NN(int , int );                          //Briskei tous N kontinoterous geitones me ton exhaustive algorithmo
void N_NearestNeighbors_LSH(int , int , int , int );    //Ektelei LSH gia tous N kontinoterous geitones