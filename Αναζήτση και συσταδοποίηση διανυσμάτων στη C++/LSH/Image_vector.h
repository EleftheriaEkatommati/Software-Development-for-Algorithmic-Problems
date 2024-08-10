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
extern int NUMBER_IMAGES;   //apothikeuoume ton arithmo twn eikonwn
extern int k; 
extern int L; 
extern int w; 
extern int N; 
extern int R; 

extern vector<MNIST_Image> Images;
extern vector<MNIST_Image> Q_Image;

vector <MNIST_Image> create_image(string& );
int Input(int argc, char* argv[]);