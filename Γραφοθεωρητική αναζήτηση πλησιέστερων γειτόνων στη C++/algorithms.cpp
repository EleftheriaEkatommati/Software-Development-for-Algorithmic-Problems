#include "algorithms.h"

vector <int> set = {};
vector <long long int> U = {};
vector <int> Y = {};

vector<int> E_Neighbors(int E, int number_image, DirectedGraph graph)                            //Kratame E kontinoterous geitones
{ 
    vector<int> adj_list = graph.edges_for_a_vertex(number_image);
    vector<int> E_neighbors = {};
    
    for(int i = 0; i < E; i++)
    {
        E_neighbors.push_back(adj_list[i]);
    }
    return E_neighbors;
}

int Min_Number_Image(vector<int> E_neighbors, int Q_number)                                      //Briskoume apo tous E geitones ton kontinotero sto query
{
    double min_dist = numeric_limits<double>::infinity();
    long long unsigned int dist = 0;
    int Min_Number_Image = 0;
    for(int i = 0; i < E_neighbors.size(); i++)
    {
        dist = Euclidian_dist(E_neighbors[i], Q_number);                                         //Ypologizoume thn eukleidia apostash
        if(dist < min_dist)
        {
            min_dist = dist;
            Min_Number_Image = i;
        }
    }
    return Min_Number_Image;                                                                     //Epistrefoume ton arithmo ths eikonas pou einai pio konta sto query
}

void GNNS_algorithm(DirectedGraph graph, int Q_number, int E, int T, int R)                      //Ekteloume ton algorithmo
{
    set = {};
    U = {};
    Y.resize(T+1);
    Y = {};
    int Y_image = 0;
    for(int i = 0; i < R; i++)                                                                   //Gia R epanalhpseis
    {
        Y[0] = generateRandomNumber_uniform_distribution();                                      //Briskoume enan tuxaio kombo me thn uniform katanomh
        for(int t = 1; t <= T; t++)                                                              //Gia T bhmata
        {
            vector<int> E_neighbors = E_Neighbors(E, Y[t-1], graph);                             //Briskoume tous E kontinoterous geitones tou kombou
            Y_image = Min_Number_Image(E_neighbors, Q_number);                                   //Apo tous E geitones briskoume auton pou einai pio konta sto query
            if(Euclidian_dist(Y_image, Q_number) > Euclidian_dist(Y[t-1], Q_number))
            {
                set.push_back(Y[t-1]);
                break;
            }
            for(int e = 0; e < E; e++)
                if(find(set.begin(), set.end(), E_neighbors[e]) == set.end())                    //An den exoume ksana brei ton sugkekrimeno kombo ton bazoume sto S
                    set.push_back(E_neighbors[e]);
            if(find(Y.begin(), Y.end(), Y_image) == Y.end())                                     //Kai an den ton exoume ksana brei
                Y[t] = Y_image;                                                                  //Ton bazoume ston pinaka
        }
    }
    double dist = 0;
    for(int i: set)
    {
        dist = Euclidian_dist(i, Q_number);
        U.push_back(dist);
    }
    
    sorted_neighbors.resize(set.size(), vector<int> (2));
    for(int i = 0; i < set.size(); i++)
    {
        sorted_neighbors[i][0] = set[i];
        sorted_neighbors[i][1] = U[i];
    }
    sort(sorted_neighbors.begin(), sorted_neighbors.end(), compareSecondColumn);
    OutputF << "Nearest neighbor-1: " << sorted_neighbors[0][0] << endl;
    OutputF << "distanceApproximate: " << sorted_neighbors[0][1] << endl;
}

void OutfileGNNS(DirectedGraph graph, int Q_number, int E, int T, int R, int N)                  //Kaloume tis sunarthseis twn algorithmwn
{
    OutputF << "GNNS Result" << endl;
    OutputF << "Query:" << Q_number << endl << endl;

    auto start0 = chrono::high_resolution_clock::now();
    GNNS_algorithm(graph, Q_number, E, T, R);
    auto finish0 = chrono::high_resolution_clock::now();                        
    chrono::duration<double> Duration0 = finish0 - start0;                                       //Xronos gia GNNS

    long long unsigned int true_dist = Euclidian_Nearest_N(Q_number);                            //Xronos gia exhaustive search

    OutputF << endl << "Nearest neighbor-N: " << sorted_neighbors[N-1][0] << endl;
    OutputF << "distanceApproximate: " << sorted_neighbors[N-1][1] << endl;

    auto start2 = chrono::high_resolution_clock::now();
    Euclidian_NN(Q_number,N);
    auto finish2 = chrono::high_resolution_clock::now();                        
    chrono::duration<double> Duration2 = finish2 - start2;                                       //Xronos gia exhaustive N-nearest neighbors
    
    OutputF << endl << "tAverageApproximate: " << Duration0.count() << endl;
    OutputF << "tAverageTrue: " << Duration2.count() << endl << endl;

    double MAF = (double)sorted_neighbors[0][1] / true_dist;
    OutputF << "MAF: " << MAF << endl;
}

void Search_On_Graph_algorithm(DirectedGraph graph, int Q_number, int L)                         //Ekteloume ton algorithmo
{
    int i = 0;
    set = {};
    vector<vector<int>> images_marked;
    vector<int> neighbors = {};

    images_marked.resize(NUMBER_IMAGES, vector<int> (2));
    for(int i = 0; i < NUMBER_IMAGES; i++)
    {
        images_marked[i].clear();
    }
    for(int i = 0; i < NUMBER_IMAGES; i++)
    {
        images_marked[i][1] = 0;                                                                 //Kanoume unmarked ola ta shmeia
    }

    int p = generateRandomNumber_uniform_distribution();                                         //Briskoume ena tuxaio shmeio
    set.push_back(p);
    i = 1;
    
    while(i < L)
    {
        images_marked[p][1] = 1;                                                                 //Markaroume to shmeio p
        neighbors = graph.edges_for_a_vertex(p);                                                 //Briskoume tous kontinoterous geitones tou p
        for(int n: neighbors)                                                                    //Gia kathe geitona tou p                     
        {
            if(find(set.begin(), set.end(), n) == set.end())                                     //An den uparxei sto set 
            {
                set.push_back(n);                                                                //Ton kanoume push
                i++;
            }
        }
        set = sort_R(set, Q_number);                                                             //Sortaroume to set me bash tis apostaseis twn shmeiwn apo to query
        if(set.size() > L)                                                                       //An to set exei megethos megalutero apo L
        {
            set.resize(L);                                                                       //Sbhnoume ta stoixeia pou briskontai sth thesh i >= l
        }
        for(int j: set)                                                                          //Pame na upologisoume to neo p gia thn epomenh epanalipsi
        {
            if(images_marked[j][1] == 0)                                                         //An h eikona einai un_marked 
            {
                p = j;                                                                           //Brhkame to p gia thn epomenh epanalipsi
                break;                                                                           //Kai stamatame
            }
        }
    }
    OutputF << "Nearest neighbor-1: " << set[0] << endl;
    OutputF << "distanceApproximate: " << Euclidian_dist(set[0], Q_number) << endl;
}

void OutfileSearch_On_Graph_algorithm(DirectedGraph graph, int L, int N, int Q_number)           //Kaloume tis sunarthseis twn algorithmwn
{
    OutputF << "MRNG Result" << endl;
    OutputF << "Query:" << Q_number << endl << endl;

    auto start0 = chrono::high_resolution_clock::now();
    Search_On_Graph_algorithm(graph, Q_number, L);
    auto finish0 = chrono::high_resolution_clock::now();                        
    chrono::duration<double> Duration0 = finish0 - start0;                                       //Xronos gia GNNS

    long long unsigned int true_dist = Euclidian_Nearest_N(Q_number);                            //Xronos gia exhaustive search

    OutputF << endl << "Nearest neighbor-N: " << set[N-1] << endl;
    OutputF << "distanceApproximate: " << Euclidian_dist(set[N-1], Q_number) << endl;

    auto start2 = chrono::high_resolution_clock::now();
    Euclidian_NN(Q_number,N);
    auto finish2 = chrono::high_resolution_clock::now();                        
    chrono::duration<double> Duration2 = finish2 - start2;                                       //Xronos gia exhaustive N-nearest neighbors
    
    OutputF << endl << "tAverageApproximate: " << Duration0.count() << endl;
    OutputF << "tAverageTrue: " << Duration2.count() << endl << endl;

    double MAF = (double)Euclidian_dist(set[0], Q_number) / true_dist;
    OutputF << "MAF: " << MAF << endl;
}