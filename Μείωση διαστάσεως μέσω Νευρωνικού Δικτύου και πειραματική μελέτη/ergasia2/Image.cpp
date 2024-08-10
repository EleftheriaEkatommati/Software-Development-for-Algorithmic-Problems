#include "Image.h"

vector<vector<int>> Images;
vector<vector<int>> Q_Image;
int NUMBER_IMAGES = 0;
int k = 50;
int N = 1;
int R = 1;
int E = 30; 
int L = 20;
int method = 0;
int Dim = 0;
ofstream OutputF;
string FileName = "output.txt";

vector<MNIST_Image> create_image_initial(string& filename)
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

    file.close();   
    return Images;
}

vector<vector<int>> create_image(string& filename) 
{
    vector<vector<int>> result;
    ifstream file(filename);
    int rows = 0;
    int cols = 0;
    string line;

    if (!file.is_open()) 
    {
        cerr << "Error opening file: " << filename << endl;
        return result;
    }
    if (getline(file, line)) 
    {
        istringstream iss(line);
        int value;
        while (iss >> value) 
        {
            ++cols;
        }
        ++rows;
    }
    file.clear(); 
    file.seekg(0, ios::beg);

    while (getline(file, line)) 
    {
        ++rows;
    }
    Dim = cols;
    file.clear();
    file.seekg(0, ios::beg);

    int value;
    for (int i = 1; i < rows; ++i) 
    {
        vector<int> rowValues;
        for (int j = 0; j < cols; ++j) 
        {
            if (file >> value) 
            {
                rowValues.push_back(value);
            } 
            else if (!file.eof()) 
            {
                cerr << "Error reading value from file at position " << file.tellg() << endl;
                return result;
            }
        }
        result.push_back(rowValues);
    }

    file.close();
    return result;
}

int Input(int argc, char* argv[])                              //gia ton elegxo twn orismatwn
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
        cout << "Give 1 for GNNS or 2 for MRNG: ";
        cin >> str;
        int i = stoi(str);
        method = i;
        if(i == 2)
        {
            string str1;
            cout << "Give L: ";
            cin >> str1;
            if(str1 != "-")
                L = stoi(str1);

            cout << "Give N: ";
            cin >> str1;
            if(str1 != "-")
                N = stoi(str1);
            
            if(N > L)
            {    
                cout << "Error! N must be <= L. Give again N: ";
                cin >> str1;
                N = stoi(str1);
            }
        }
        if(i == 1)
        {
            string str2;

            cout << "Give k: ";
            cin >> str2;
            if(str2 != "-")
                k = stoi(str2);

            cout << "Give E: ";
            cin >> str2;
            if(str2 != "-")
                E = stoi(str2);

            cout << "Give R: ";
            cin >> str2;
            if(str2 != "-")
                R = stoi(str2);

            cout << "Give N: ";
            cin >> str2;
            if(str2 != "-")
                N = stoi(str2);
        }
        else if(i != 1 && i != 2)    
            cout << "Invalid input. Give 1 or 2." << endl;

        Images = create_image(Input_FName);  
        NUMBER_IMAGES = Images.size();
        Q_Image = create_image(Q_FName);  
    }
    else if (argc == 17 && stoi(argv[14]) == 1)
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

        string E_flag = argv[7];
        E = stoi(argv[8]);
        if (E_flag != "-E") 
        {
            cerr << "Invalid flag. Please use -E flag." << endl;
            return -1;
        }

        string R_flag = argv[9];
        R = stoi(argv[10]);
        if (R_flag != "-R") 
        {
            cerr << "Invalid flag. Please use -R flag." << endl;
            return -1;
        }

        string N_flag = argv[11];
        N = stoi(argv[12]);
        if (N_flag != "-N") 
        {
            cerr << "Invalid flag. Please use -N flag." << endl;
            return -1;
        }

        string m_flag = argv[13];
        method = stoi(argv[14]);
        if (m_flag != "-m") 
        {
            cerr << "Invalid flag. Please use -m flag." << endl;
            return -1;
        }

        string output_flag = argv[15];
        string output_filename = argv[16];
        if (output_flag != "-o") 
        {
            cerr << "Invalid flag. Please use -o flag." << endl;
            return -1;
        }
        OutputF.open(output_filename);
    }
    else if (argc == 19 && stoi(argv[16]) == 2)
    {
        method = stoi(argv[16]);
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

        string E_flag = argv[7];
        E = stoi(argv[8]);
        if (E_flag != "-E") 
        {
            cerr << "Invalid flag. Please use -E flag." << endl;
            return -1;
        }

        string R_flag = argv[9];
        R = stoi(argv[10]);
        if (R_flag != "-R") 
        {
            cerr << "Invalid flag. Please use -R flag." << endl;
            return -1;
        }

        string N_flag = argv[11];
        N = stoi(argv[12]);
        if (N_flag != "-N") 
        {
            cerr << "Invalid flag. Please use -N flag." << endl;
            return -1;
        }

        string l_flag = argv[13];
        L = stoi(argv[14]);
        if (l_flag != "-l") 
        {
            cerr << "Invalid flag. Please use -L flag." << endl;
            return -1;
        }

        string m_flag = argv[15];
        method = stoi(argv[16]);
        if (m_flag != "-m") 
        {
            cerr << "Invalid flag. Please use -m flag." << endl;
            return -1;
        }

        string output_flag = argv[17];
        string output_filename = argv[18];
        if (output_flag != "-o") 
        {
            cerr << "Invalid flag. Please use -o flag." << endl;
            return -1;
        }
        OutputF.open(output_filename);
        
        string str10;
        if(N > L)
        {    
            cout << "Error! N must be <= L. Give again N: ";
            cin >> str10;
            N = stoi(str10);
        }
    }
    else
    {
        cerr << "Wrong arguments!" << endl;
        cerr << "./graph_search –d <input file> –q <query file> –k <int> -E <int> -R <int> -N <int> -l <int, only for MRNG> -m <1 GNNS, 2 MRNG> -ο <output file>" << endl;
        return -1;
    }

    return 0;
}