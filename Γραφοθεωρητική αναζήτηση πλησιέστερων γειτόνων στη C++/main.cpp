//sdi2000014 , sdi2000048
#include "algorithms.h"
#define L_lsh 5
#define k_lsh 4
#define T 50
#define Q_number 200

int main(int argc, char* argv[])
{
    int k_1 = Input(argc, argv);
    if(k_1 == -1)
        return 0;

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
        OutputF.close();
        string str;
        cout << "If you want to stop write END else for redoing the algorithm type continue: ";
        cin >> str;
        if(str == "END")
            return 0;
        else if(str == "continue")
        {
            int k_1 = Input(1, argv);
            if(k_1 == -1)
                return 0;

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
    return 0;
}