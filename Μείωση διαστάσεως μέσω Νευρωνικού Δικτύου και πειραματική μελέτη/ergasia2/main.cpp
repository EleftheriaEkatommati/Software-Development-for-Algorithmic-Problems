//sdi2000014 , sdi2000048
#include "algorithms.h"
#define L_lsh 5
#define k_lsh 4
#define T 50

int Dim_initial = 0;
string filename_initial = " ";
string query_initial = " ";
vector<MNIST_Image> Images_initial;
vector<MNIST_Image> Q_Image_initial;

int main(int argc, char* argv[])
{
    int k_1 = Input(argc, argv);
    if(k_1 == -1)
        return 0;
    int Q_number = rand() % Q_Image.size();

    cout << "Give the path for the input file for the initial dataset: ";
    cin >> filename_initial;
    cout << "Give the path for the query file for the initial queryset: ";
    cin >> query_initial;

    Images_initial = create_image_initial(filename_initial);
    Q_Image_initial = create_image_initial(query_initial);
    Dim_initial = sizeof(Images_initial[0].pixels) / sizeof(Images_initial[0].pixels[0]);
   
    Hash_initialize(L_lsh);
    HashFunctions_initialize(k_lsh, L_lsh);
    Hash_clear(L_lsh);
    for(int i = 0; i < NUMBER_IMAGES; i++)
        Euclidian_Hash(i, L_lsh, k_lsh);

    DirectedGraph graph(NUMBER_IMAGES);

    if(method == 1)                                            //An o xrhsths zhtaei ton algorithmo GNNS
    {
        k_NN_graph(k, graph, L_lsh, k_lsh);
        OutfileGNNS(graph, Q_number, E, T, R, N);
    }

    string str;
    if(method == 2)                                            //An o xrhsths zhtaei ton algorithmo search on graph
    {    
        cout << "Write yes if you want to use a MRNG graph which is already created or no to create a new one: ";
        cin >> str;
    }
    if(method == 2 && str == "no")
    {
        fstream GraphFile("graph.txt", std::ios::in | std::ios::out | std::ios::trunc);
        vector<int> adjacencyList = {};
        MRNG(N, graph, L_lsh, k_lsh);
        for (int i = 0; i < NUMBER_IMAGES; ++i) 
        {
            adjacencyList = graph.edges_for_a_vertex(i);
            for (int neighbor : adjacencyList) 
            {
                GraphFile << neighbor << " ";
            }
            GraphFile << endl;
        }
        OutfileSearch_On_Graph_algorithm(graph , L, N, Q_number);
    }
    if(method == 2 && str == "yes")
    {
        fstream GraphFile;
        GraphFile.open("graph.txt");
        string line;
        int number_image = 0;
        while (getline(GraphFile, line)) 
        {
            vector<int> lineData;
            istringstream iss(line);

            int num;
            while (iss >> num) 
            {
                graph.addEdge(number_image, num);
            }
            number_image++;
        }
        OutfileSearch_On_Graph_algorithm(graph , L, N, Q_number);
    }

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
            int k_1 = Input(1, argv);
            if(k_1 == -1)
                return 0;

            cout << "Give the path for the input file for the initial dataset: ";
            cin >> filename_initial;
            cout << "Give the path for the query file for the initial queryset: ";
            cin >> query_initial;

            Images_initial = create_image_initial(filename_initial);
            Q_Image_initial = create_image_initial(query_initial);
            Dim_initial = sizeof(Images_initial[0].pixels) / sizeof(Images_initial[0].pixels[0]);
            
            Hash_initialize(L_lsh);
            HashFunctions_initialize(k_lsh, L_lsh);
            Hash_clear(L_lsh);
            for(int i = 0; i < NUMBER_IMAGES; i++)
                Euclidian_Hash(i, L_lsh, k_lsh);

            DirectedGraph graph(NUMBER_IMAGES);

            if(method == 1)                                    //An o xrhsths zhtaei ton algorithmo GNNS
            {
                k_NN_graph(k, graph, L_lsh, k_lsh);
                OutfileGNNS(graph, Q_number, E, T, R, N);
            }

            string str4;
            if(method == 2)                                    //An o xrhsths zhtaei ton algorithmo search on graph
            {    
                cout << "Write yes if you want to use a MRNG graph which is already created or no to create a new one: ";
                cin >> str4;
            }
            if(method == 2 && str4 == "no")
            {
                fstream GraphFile("graph.txt", std::ios::in | std::ios::out | std::ios::trunc);
                vector<int> adjacencyList = {};
                MRNG(N, graph, L_lsh, k_lsh);
                for (int i = 0; i < NUMBER_IMAGES; ++i) 
                {
                    adjacencyList = graph.edges_for_a_vertex(i);
                    for (int neighbor : adjacencyList) 
                    {
                        GraphFile << neighbor << " ";
                    }
                    GraphFile << endl;
                }
                OutfileSearch_On_Graph_algorithm(graph , L, N, Q_number);
            }
            if(method == 2 && str4 == "yes")
            {
                fstream GraphFile;
                GraphFile.open("graph.txt");
                string line;
                int number_image = 0;
                while (getline(GraphFile, line)) 
                {
                    vector<int> lineData;
                    istringstream iss(line);

                    int num;
                    while (iss >> num) 
                    {
                        graph.addEdge(number_image, num);
                    }
                    number_image++;
                }
                OutfileSearch_On_Graph_algorithm(graph , L, N, Q_number);
            }
        }
    }

    const char* program = "./initial/graph_search";
    const char* outputfile = "output_initial.txt";
    ostringstream commandStream;
    if (method == 1)
        commandStream << program << " -d " << filename_initial << " -q " << query_initial << " -k " << k << " -E " << E << " -R " << R <<  " -N " << N << " -m " << method << " -o " << outputfile;
    if (method == 2)
        commandStream << program << " -d " << filename_initial << " -q " << query_initial << " -k " << k << " -E " << E << " -R " << R <<  " -N " << N << " -l " << L << " -m " << method << " -o " << outputfile;
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

    for (int i = 0; i < 4; ++i) 
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
    if (method == 1)
        OutputF << endl << "AF: " << (double) Euclidian_dist_initial(sorted_neighbors[0][0], Q_number) / dist_approx_neighbor << endl;
    if (method == 2)
        OutputF << endl << "AF: " << (double) Euclidian_dist_initial(set[0], Q_number) / dist_approx_neighbor << endl;
    file.close();
    OutputF.close();

    return 0;
}