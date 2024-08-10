//sdi2000014 , sdi2000048
#include "Cluster.h"
#define MAXITERATIONS 20

int main(int argc, char* argv[]) 
{
    int k_1 = Input(argc,argv);
    if(k_1 == -1)
        return 0;
    OutFile(K, k_LSH, MAXITERATIONS, L, probes, M, k_Cube);
    return 0;
}