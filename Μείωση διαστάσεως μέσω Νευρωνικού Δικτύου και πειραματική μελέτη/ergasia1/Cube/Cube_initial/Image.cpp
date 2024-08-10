#include "Image.h"

vector<MNIST_Image> Images;
vector<MNIST_Image> Q_Image;
int NUMBER_IMAGES = 0;
int k = 14;
int M = 10;
int probes = 2;
int N = 1;
int R = 10000;
int Dim = 784;
ofstream OutputF;
string FileName = "output.txt";

vector<MNIST_Image> create_image(string& filename)
{
    vector<MNIST_Image> Images;

    ifstream file(filename, ios::binary);                            //anoigoume binary arxeio me onoma filename 
    if(!file)                                                        //elegxoume an to arxeio exei anoiksei 
    {
        cout << "Error!" << endl;
        return Images;
    }
    int magic_number, number_images, rows, cols;
    file.read((char*)&magic_number, sizeof(magic_number));
    magic_number = __builtin_bswap32(magic_number); 
    file.read((char*)&number_images, sizeof(number_images));
    number_images = __builtin_bswap32(number_images);
    file.read((char*)&rows, sizeof(rows));
    rows = __builtin_bswap32(rows);
    file.read((char*)&cols, sizeof(cols));
    cols = __builtin_bswap32(cols);

    MNIST_Image image;
    for(int i = 0; i < number_images; i++)
    {
        file.read(reinterpret_cast <char*>(&image.pixels), sizeof(image.pixels));  //diabazoume mia mia thn eikona
        Images.push_back(image);
    }

    file.close();   //kleinoume to arxeio
    return Images;
}

int Input(int argc, char* argv[])
{
    string Input_FName;
    string Q_FName;
    string Output_FName;
    if(argc == 1)
    {
        cout << "Give the path for the input file: ";
        cin >> Input_FName;

        cout << "Give the path for the query file: ";
        cin >> Q_FName;

        cout << "Give the path for the output file: ";
        cin >> Output_FName;
		OutputF.open(Output_FName);

        string str;
        cout << "Give k: ";
        cin >> str;
        if(str != "-")
            k = stoi(str);

        cout << "Give M: ";
        cin >> str;
        if(str != "-")
            M = stoi(str);

        cout << "Give probes: ";
        cin >> str;
        if(str != "-")
            probes = stoi(str);

        cout << "Give N: ";
        cin >> str;
        if(str != "-")
            N = stoi(str);

        cout << "Give R: ";
        cin >> str;
        if(str != "-")
            R = stoi(str);
        Images = create_image(Input_FName);  
        NUMBER_IMAGES = Images.size();
        Q_Image = create_image(Q_FName);  
    }
    else if (argc == 17)
    {
        string input_flag = argv[1];
        string input_filename = argv[2];

        if (input_flag != "-d") 
        {
            cerr << "Invalid flag. Please use -d flag." << endl;
            return -1;
        }
        Images = create_image(input_filename);  
        NUMBER_IMAGES = Images.size();

        string query_flag = argv[3];
        string query_filename = argv[4];

        if (query_flag != "-q") 
        {
            cerr << "Invalid flag. Please use -q flag." << endl;
            return -1;
        }
        Q_Image = create_image(query_filename);  

        string k_flag = argv[5];
        k = stoi(argv[6]);
        if (k_flag != "-k") 
        {
            cerr << "Invalid flag. Please use -k flag." << endl;
            return -1;
        }

        string M_flag = argv[7];
        M = stoi(argv[8]);
        if (M_flag != "-M") 
        {
            cerr << "Invalid flag. Please use -M flag." << endl;
            return -1;
        }

        string Probes_flag = argv[9];
        probes = stoi(argv[10]);
        if (Probes_flag != "-probes") 
        {
            cerr << "Invalid flag. Please use -probes flag." << endl;
            return -1;
        }

        string output_flag = argv[11];
        string output_filename = argv[12];
        if (output_flag != "-o") 
        {
            cerr << "Invalid flag. Please use -o flag." << endl;
            return -1;
        }    
        OutputF.open(output_filename);
        
        string N_flag = argv[13];
        N = stoi(argv[14]);
        if (N_flag != "-N") 
        {
            cerr << "Invalid flag. Please use -N flag." << endl;
            return -1;
        }

        string R_flag = argv[15];
        R = stoi(argv[16]);
        if (R_flag != "-R") 
        {
            cerr << "Invalid flag. Please use -R flag." << endl;
            return -1;
        }
    }
    else
    {
        cerr << "Wrong arguments!" << endl;
        cerr << "./cube –d <input file> –q <query file> –k <int> -M <int> -probes <int> -ο <output file> -Ν <number of nearest> -R <radius>" << endl;
        return -1;
    }

    return 0;
}