#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

struct MNIST_Image 
{
    unsigned char pixels[784];
};

extern ofstream OutputF;
extern ifstream Conf_F;
extern string FileName; 
extern int NUMBER_IMAGES;   //apothikeuoume ton arithmo twn eikonwn
extern int K; 
extern int k_LSH; 
extern int k_Cube; 
extern int L; 
extern int M; 
extern int probes; 
extern string Method;
extern int CompFlag;

extern vector<MNIST_Image> Images;
vector <MNIST_Image> create_image(string& );
void readFromFile(string );
int Input(int argc, char* argv[]);