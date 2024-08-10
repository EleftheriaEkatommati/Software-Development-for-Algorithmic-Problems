#include "Image.h"

vector<MNIST_Image> Images;
int NUMBER_IMAGES = 0;
int k_LSH = 4;
int L = 3;
int M = 10;
int k_Cube = 3;
int probes = 2;
int K;
int CompFlag = 0;
ofstream OutputF;
ifstream Conf_F;
string Method;
string FileName = "output.txt";

vector<MNIST_Image> create_image(string& filename)
{
    ifstream file(filename, ios::binary);                                         //anoigoume binary arxeio me onoma filename 
    if(!file)                                                                     //elegxoume an to arxeio exei anoiksei 
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
    
    Images.clear();
    MNIST_Image image;

    for(int i = 0; i < number_images; i++)
    {
        file.read(reinterpret_cast<char*>(&image.pixels), sizeof(image.pixels));  //diabazoume mia mia thn eikona
        Images.push_back(image);
    }

    file.close();   //kleinoume to arxeio
    return Images;
}

void readFromFile(string filename)                                                //Diabazoume apo to configuration arxeio kai dinoume times stis katallhles metablhtes
{
    Conf_F.open(filename);
    vector <string> numbers;
    int count_line = 0;
    if (Conf_F.is_open()) 
    {
        string line;
        while (getline(Conf_F, line))                                             //Gia kathe grammh tou arxeiou
        {   
            istringstream iss(line);
            string word;
            for(int i = 0; i < 2; i++)                                            //Apothikeuoume ton akeraio h to keno pou uparxei meta thn anw katw teleia
            {
                getline(iss, word, ':');
                if(i == 1)
                {
                    numbers.push_back(word);
                }
            }
            count_line++;
        }
        K = stoi(numbers[0]);
        if(numbers[1].size() != 0)
            L = stoi(numbers[1]);
        if(numbers[2].size() != 0)
            k_LSH = stoi(numbers[2]);
        if(numbers[3].size() != 0)
            M = stoi(numbers[3]);
        if(numbers[4].size() != 0)
            k_Cube = stoi(numbers[4]);
        if(numbers[5].size() != 0)
            probes = stoi(numbers[5]);
    } 
    else 
    {
        cerr << "Failed to open the file: " << filename << endl;
        return;
    }
    Conf_F.close();
    return;
}

int Input(int argc, char* argv[])
{
    string Input_FName;
    string Output_FName;
    if (argc < 9)
    {
        cout << "We need more arguments!" << endl;
        cout << "./cluster –i <input file> –c <configuration file> -o <output file> -complete <optional> -m <method: Classic OR LSH or Hypercube>" << endl;
        return -1;
    }
    else
    {
        if (argc == 9)
        {
            string input_flag = argv[1];
            string input_filename = argv[2];

            if (input_flag != "-i") 
            {
                cerr << "Invalid flag. Please use -i flag." << endl;
                return -1;
            }
            Images = create_image(input_filename);  
            NUMBER_IMAGES = Images.size();

            string conf_flag = argv[3];
            string conf_filename = argv[4];

            if (conf_flag != "-c") 
            {
                cerr << "Invalid flag. Please use -c flag." << endl;
                return -1;
            }
            readFromFile(conf_filename);

            string output_flag = argv[5];
            string output_filename = argv[6];
            if (output_flag != "-o") 
            {
                cerr << "Invalid flag. Please use -o flag." << endl;
                return -1;
            }
            OutputF.open(output_filename);

            string method_flag = argv[7];
            string method = argv[8];
            if (method_flag != "-m") 
            {
                cerr << "Invalid flag. Please use -m flag." << endl;
                return -1;
            }
            Method = method;
            int flag = 0;
            if (method == "Classic" || method == "LSH" || method == "Hypercube")
            {
                flag = 1;
            }
            if (flag == 0)
            {
                cerr << "Inavlid method. Please use Classic, LSH or Hypercube." << endl;
                return -1;
            }
        }
        if (argc == 10)
        {
            CompFlag = 1;
            string input_flag = argv[1];
            string input_filename = argv[2];

            if (input_flag != "-i") 
            {
                cerr << "Invalid flag. Please use -i flag." << endl;
                return -1;
            }
            Images = create_image(input_filename);  
            NUMBER_IMAGES = Images.size();

            string conf_flag = argv[3];
            string conf_filename = argv[4];

            if (conf_flag != "-c") 
            {
                cerr << "Invalid flag. Please use -c flag." << endl;
                return -1;
            }
            readFromFile(conf_filename);

            string output_flag = argv[5];
            string output_filename = argv[6];
            if (output_flag != "-o") 
            {
                cerr << "Invalid flag. Please use -o flag." << endl;
                return -1;
            }
            OutputF.open(output_filename);

            string complete_flag = argv[7];
            if (complete_flag != "-complete") 
            {
                cerr << "Invalid flag. Please use -complete flag." << endl;
                return -1;
            }

            string method_flag = argv[8];
            string method = argv[9];
            if (method_flag != "-m") 
            {
                cerr << "Invalid flag. Please use -m flag." << endl;
                return -1;
            }
            Method = method;
            int flag = 0;
            if (method == "Classic" || method == "LSH" || method == "Hypercube")
            {
                flag = 1;
            }
            if (flag == 0)
            {
                cerr << "Inavlid method. Please use Classic, LSH or Hypercube." << endl;
                return -1;
            }
        }
    }
    return 0;
}