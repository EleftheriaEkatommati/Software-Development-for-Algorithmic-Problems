//sdi2000014 , sdi2000048
#include "Cube.h"
int Dim_initial = 0;
string filename_initial = " ";
string query_initial = " ";
vector<MNIST_Image> Images_initial;
vector<MNIST_Image> Q_Image_initial;

int main(int argc, char* argv[]) 
{
    srand(static_cast<unsigned int>(time(0)));
    int In = Input(argc,argv);
    if(In == -1)
        return 0; 

    int Q_number = rand() % Q_Image.size();
    cout << "Give the path for the input file for the initial dataset: ";
    cin >> filename_initial;
    cout << "Give the path for the query file for the initial queryset: ";
    cin >> query_initial;
    
    Images_initial = create_image_initial(filename_initial);
    Q_Image_initial = create_image_initial(query_initial);
    Dim_initial = sizeof(Images_initial[0].pixels) / sizeof(Images_initial[0].pixels[0]);

    Probe = GenerateRandomBinaryProbe(k);
    Images_To_Binary(Q_number, k, Probe);
    Cube_OutFile(probes, k, Q_number, N, R);

    while(1)
    {
        string str;
        cout << "If you want to stop write END else for redoing the algorithm (for the reduced dimension) type continue: ";
        cin >> str;
        if(str == "END")
            break;

        else if(str == "continue")
        {
            OutputF.close();
            int k_1 = Input(1,argv);
            if(k_1 == -1)
                return 0;
                
            cout << "Give the path for the input file for the initial dataset: ";
            cin >> filename_initial;
            cout << "Give the path for the query file for the initial queryset: ";
            cin >> query_initial;

            Probe = GenerateRandomBinaryProbe(k);
            Images_To_Binary(Q_number, k, Probe);
            Cube_OutFile(probes, k, Q_number, N, R);
        }
    }

    const char* program = "./Cube_initial/cube";
    const char* outputfile = "output_initial.txt";
    ostringstream commandStream;
    commandStream << program << " -d " << filename_initial << " -q " << query_initial << " -k " << k << " -M " << M << " -probes " << probes << " -o " << outputfile << " -N " << N << " -R " << R;
    string command = commandStream.str();
    const char* cstr_command = command.c_str();
    int result = system(cstr_command); 
    if(result != 0) 
    {
        cout << "Error! The algorithm on the initial dataset was not executed!" << endl;
        return -1;
    }

    ifstream file(outputfile);

    if (!file.is_open()) 
    {
        cerr << "Error opening the file!" << endl;
        return 1;
    }

    for (int i = 0; i < 2; ++i) 
    {
        file.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    string line;
    getline(file, line);

    istringstream iss(line);
    string distanceLabel;
    int dist_approx_neighbor = 0;

    iss >> distanceLabel >> dist_approx_neighbor;

    if (!iss) 
    {
        cerr << "Error reading the integer from the file!" << endl;
        return 1;
    }

    OutputF << endl << "AF: " << (double) Euclidian_dist_initial(Cube_Neighbor, Q_number) / dist_approx_neighbor << endl;
    file.close();
    OutputF.close();
}