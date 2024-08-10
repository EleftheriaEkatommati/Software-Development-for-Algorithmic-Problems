#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <random>
#include <time.h>
#include <chrono>
#include <algorithm>
#include <bitset>
#include <string>
#include <ctime>
#include "Euclidian.h"
using namespace std;

extern vector<vector<bool>> searchSpace;
static vector<int> Points_Range;                                          //Apothikekoume tous arithmous twn eikonwn sto range search
static vector<int> N_Points;                                              //Apothikekoume tous arithmous twn eikonwn twn N kontinoterwn geitonwn
extern vector<vector<bool>> BinaryImages;                                 //Apothikeuoume tis eikones me thn binary morfh tous
extern vector<bool> BinaryQuery;                                          //Apothikeuoume to query me thn binary morfh tou
extern vector<bool> Probe;                                                //Apothikeuoume binary arithmo megethous k
extern int Cube_Neighbor;

int HammingDistance(const vector<bool> , const vector<bool> );            //Ypologizoume thn hamming aposatsh metaksi duo binary vector
                  
void Images_To_Binary(int , int , const vector<bool> );                   //Metatrepei thn kathe eikona se ena binary dianusma megethous k

vector<bool> GenerateRandomBinaryProbe(int );                            
void FindSearchSpace(int );
void RandomlySelectMPoints(vector<vector<bool>>& , int );                 //Dialegoume M apo tis eikones enos vector

void Random_projection_to_HyperCube(int , int , int );
void Random_projection_to_HyperCube_N(int , int , int , int );            //Ekteloume ton algorithmo ths probolhs ston upoerkubo
void Random_projection_to_HyperCube_RangeSearch(int , int , int , int );  //Ekteloume ton algorithmo ths probolhs ston upoerkubo me range search
void Cube_OutFile(int , int , int , int , int );                          //Kalei tis sunarthseis gia thn ektelesh twn algorithmwn kai upologizei kai ton xrono