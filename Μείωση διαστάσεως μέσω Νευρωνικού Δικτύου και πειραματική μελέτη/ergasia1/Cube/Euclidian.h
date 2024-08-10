#include <cmath>
#include <stdlib.h>
#include <random>
#include <time.h>
#include <chrono>
#include <algorithm>
#include "Image.h"

extern int True_Neighbor;

long long int Euclidian_dist(int , int );   //Ypologizei thn apostash metaksi duo dianusmatwn
void Euclidian_Nearest_N(int );             //Briskei me ton exhaustive algorithmo ton kontinotero geitona
void Euclidian_NNN(int , int );             //Briskei me ton exhaustive algorithmo tous N kontinoterous geitones
long long int Euclidian_dist_initial(int , int );