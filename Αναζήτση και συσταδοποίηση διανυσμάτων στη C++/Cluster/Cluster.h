#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <random>
#include <time.h>
#include <limits>
#include <chrono>
#include <algorithm>
#include "Hash.h"

using namespace std;

extern vector<vector<double>> centroids;
extern vector<int> clusters;

long long int Euclidian_dist(int , int );                                       //Ypologizei thn apostash metaksi duo dianusmatwn

void k_MeansPlusPlus_Init(int );                                                //Kanei thn arxikopoihsh twn centroids
void AssignToClusters(int );                                                    //Bazei kathe eikona se ena cluster

void AssignToClusters_LSH(int , int , int , int );        
void AssignToClusters_Cube(int , int , int , int , int );   

void updateCentroids(int );                                                     //Briskei tis nees suntetagmenes twn centroids

void macQueen(int , int , int , int , int , int , int );                        //Kanei thn ektelesh tou algorithmou sumfwna me thn methodo pou exei zhthsei o xrhsths

double CalculateA(int );
double CalculateB(int , int );

void OutFile(int , int , int , int , int , int , int );                         //Kalei tis sunarthseis gia thn ektelesh twn algorithmwn kai upologizei kai ton xrono