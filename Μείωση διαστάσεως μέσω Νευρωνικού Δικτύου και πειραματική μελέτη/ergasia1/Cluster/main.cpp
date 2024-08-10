//sdi2000014 , sdi2000048
#include "Cluster.h"
#define MAXITERATIONS 20

int main(int argc, char* argv[]) 
{
    int k_1 = Input(argc,argv);
    if(k_1 == -1)
        return 0;
    OutFile(K, k_LSH, MAXITERATIONS, L, probes, M, k_Cube);

    string filename_initial;
    cout << "Give the path for the input file for the initial dataset: ";
    cin >> filename_initial;

    const char* program = "./Cluster_initial/cluster";
    const char* outputfile = "output_initial.txt";
    ostringstream commandStream;
    if (argc == 9)
        commandStream << program << " -i " << filename_initial << " -c " << Configuration_file_name << " -o " << outputfile << " -m " << Method;
    if (argc == 10)
        commandStream << program << " -i " << filename_initial << " -c " << Configuration_file_name << " -o " << outputfile << " -complete " << " -m " << Method;
    string command = commandStream.str();
    const char* cstr_command = command.c_str();
    int result = system(cstr_command);
    if (result == 0) 
    {
        return 0;
    } 
    else 
    {
        cout << "Error! The algorithm on the initial dataset was not executed!" << endl;
        return -1;
    }
    return 0;
}