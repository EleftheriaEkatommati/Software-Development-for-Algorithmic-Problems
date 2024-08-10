#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
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
extern int Dim;
extern int Dim_initial;
extern string filename_initial;
extern string query_initial;

extern vector<vector<int>> Images;
extern vector<vector<int>> Q_Image;

extern vector<MNIST_Image> Images_initial;
extern vector<MNIST_Image> Q_Image_initial;

vector<vector<int>> create_image(string& );
vector<MNIST_Image> create_image_initial(string& );
int Input(int argc, char* argv[]);