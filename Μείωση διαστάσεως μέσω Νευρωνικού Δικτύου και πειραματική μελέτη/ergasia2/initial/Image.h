#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct MNIST_Image 
{
    unsigned char pixels[784];
};

extern ofstream OutputF;
extern string FileName; 
extern int NUMBER_IMAGES;    //apothikeuoume ton arithmo twn eikonwn
extern int k;                //GNNS
extern int w;                //LSH
extern int N;                //N-nearest neighbors
extern int R;                //GNNS
extern int L;                //MRNG
extern int E;                //GNNS
extern int method;           //1 an h methodos einai GNNS 2 an einai to Search on graph

extern vector<MNIST_Image> Images;
extern vector<MNIST_Image> Q_Image;

vector <MNIST_Image> create_image(string& );
int Input(int argc, char* argv[]);