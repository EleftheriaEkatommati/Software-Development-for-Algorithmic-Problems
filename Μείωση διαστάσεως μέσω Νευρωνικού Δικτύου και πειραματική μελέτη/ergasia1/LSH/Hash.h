#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <random>
#include <time.h>
#include <chrono>
#include <algorithm>
#include "Random.h"
using namespace std;

static vector<vector<vector<long long unsigned int>>> Euclidian_Hash_Tables;
static vector<double> t;
static vector<vector<double>> v;
static vector<vector<int>> HashFunctions_Amplified;
static vector<int> Points_Range;                        //Apothikekoume tous arithmous twn eikonwn sto range search
static vector<int> N_Points;                            //Apothikekoume tous arithmous twn eikonwn twn N kontinoterwn geitonwn
extern int LSH_NN;

void Hash_initialize(int);                              //Arxikopoioume tous hash tables
void HashFunctions_initialize(int, int);                //Arxikopoioume tis g sunarthseis
void Euclidian_Hash(int , int , int );                  //Gemizoume tous hash tables
void Hash_clear(int );  
long long int Euclidian_dist(int , int );               //Ypologizei thn apostash metaksi duo dianusmatwn
long long unsigned int Query_Hash(int , int , int ); 
long long int Euclidian_dist_initial(int , int ); 

void Euclidian_Nearest_N(int );                         //Briskei me ton exhaustive algorithmo ton kontinotero geitona
void LSH_Nearest_N(int , int , int );                   //Ektelei LSH gia ton kontinotero geitona

void Euclidian_NN(int , int );                         //Briskei me ton exhaustive algorithmo tous N kontinoterous geitones
void N_NearestNeighbors_LSH(int , int , int , int );   //Ektelei LSH gia tous N kontinoterous geitones

void LSH_RangeSearch(int , int , int , double );       //Ektelei LSH me range search
void LSH_OutFile(int , int , int , int , int );        //Kalei tis sunarthseis gia thn ektelesh twn algorithmwn kai upologizei kai ton xrono