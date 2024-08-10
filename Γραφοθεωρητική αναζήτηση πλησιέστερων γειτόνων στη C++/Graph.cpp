#include "Graph.h"

DirectedGraph::DirectedGraph(int vertices) : numVertices(vertices), adjacencyList(vertices) {}  //Constuctor ths clashs

void DirectedGraph::Edge_init(void)                                     //Arxikopoioume to adjacency list
{
    adjacencyList.resize(numVertices, vector<int> (k));
    for(int i = 0; i < numVertices; i++)
        adjacencyList[i].clear();
} 

void DirectedGraph::addEdge(int from, int to)                           //Prosthetoume akmh ston grafo
{
    adjacencyList[from].push_back(to);
}

void DirectedGraph::print_number_vertex()                               //Ektupwnoume ton arithmo twn komvwn tou grafou
{
    cout << numVertices << endl;
}

void DirectedGraph::printGraph()                                        //Ektupwnoume ton grafo
{
    for (int i = 0; i < NUMBER_IMAGES; ++i) 
    {
        cout << "Vertex " << i << " is connected to:";
        for (int neighbor : adjacencyList[i]) 
        {
            cout << " " << neighbor;
        }
        cout << endl;
    }
}

vector<int> DirectedGraph::edges_for_a_vertex(int number)               //Epistrefei tous komvous me tous opoious sundeetai mia sugkekrimenh akmh 
{
    return adjacencyList[number];
} 

void k_NN_graph(int k, DirectedGraph &graph, int L, int k_lsh)          //Ftiaxnoume to k-Nearest-Neighbor grafo
{
    graph.Edge_init();                                                  //Arxikopoioume thn domh gia thn lista geitniashs
    for(int i = 0; i < NUMBER_IMAGES; i++)                              //Gia kathe eikona 
    {
        N_NearestNeighbors_LSH(i, L, k_lsh, k);                         //Briskoume tous N kontinoterous geitones
        for(int j = 0; j < k; j++)                                      //Gia kathe kontinotero geitone ths eikonas i
        {
            graph.addEdge(i, N_Points[j]);                              //Prosthtoume thn katallhlh akmh sto grafo
        }
        for(int j = 0; j < k; j++)                                      //Katharizoume ton pinaka me tous kontinoterous geitones
        {
            N_Points.clear();
        }
    }
}

bool compareSecondColumn(const vector<int>& a, const vector<int>& b)    //Sunarthsh sugkrishs
{
    return a[1] < b[1];
}

vector<int> sort_R(vector<int> R, int number_image)                     //Xrhsimopoieitai gia na sortarei enan pinaka me bash tis apostaseis twn shmeiwn apo to p
{
    vector<int> dist;
    dist.resize(NUMBER_IMAGES-1);
    dist = {};

    vector<vector<int>> sorted_R;
    sorted_R.resize(R.size(), vector<int> (2));

    for(int i: R)
    {
        dist.push_back(Euclidian_dist(i, number_image));                //Ypologizoume tis apostaseis twn shmeiwn tou pinaka apo to p
    }
    for(int i = 0; i < R.size(); i++)                                   //Ftiaxnoume enan dusdiastato pinaka
    {
        sorted_R[i][0] = R[i];                                          //H prwth sthlh periexei tous arithmous twn eikonwn
        sorted_R[i][1] = dist[i];                                       //Kai h deuterh sthlh periexei tis apostashs apo to p
    }
    sort(sorted_R.begin(), sorted_R.end(), compareSecondColumn);        //Sortaroume ton pinaka me bash thn deuterh sthlh xwris na xathoun oi plhrofories gia to poia eikona exei thn sugkekrimenh apostash
    
    vector<int> R_return;
    R_return.resize(R.size());
    R_return = {};

    for(int i = 0; i < R.size(); i++)                                   //Apothikeuoume se enan pinaka thn prwth sthlh tou prohgoumenou pinaka kai thn epistrefoume
        R_return.push_back(sorted_R[i][0]);
    return R_return;
}

double distance(int number_image1, int number_image2)                   //Ypologizoume apostash metaksi duo eikonwn
{
    long long int dist = 0;
    for(int i = 0; i < 784; i++)
    {
        dist += (Images[number_image1].pixels[i]-Images[number_image2].pixels[i])*(Images[number_image1].pixels[i]-Images[number_image2].pixels[i]);
    }
    return sqrt(dist);
}

bool isLongestEdge(int p, int r, int t)                                 //Epistrefoume true an h pr einai h megaluterh akmh tou trigwnou prt
{
    double pr = distance(p, r);
    return pr == max({distance(p, t), distance(r, t), distance(p, r)});
}

void MRNG(int N, DirectedGraph &graph, int L_lsh, int k_lsh)            //Ftiaxnei ton grafo MRNG
{
    bool condition;
    int counter = 0;
    vector<vector<int>> R; 
    vector<vector<int>> L; 
   
    R.resize(NUMBER_IMAGES, vector<int>(NUMBER_IMAGES-1));
    L.resize(NUMBER_IMAGES, vector<int>(N+1));
    for(int p = 0; p < NUMBER_IMAGES; p++)
    {
        R[p].clear();
        L[p].clear();
    }

    for(int p = 0; p < NUMBER_IMAGES; p++)                              //Gia kathe eikona 
    {
        for(int i = 0; i < NUMBER_IMAGES; i++)
        {    
            if(i != p)
            {    
                R[p].push_back(i);                                      //Bazoume sto R[p] oles tis eikones tou dataset ektos apo thn p
            }
        }
        R[p] = sort_R(R[p], p);                                         //Sortaroume to R[p] me bash thn apostash ths kathe eikonas apo to p

        N_NearestNeighbors_LSH(p, L_lsh, k_lsh, N);
        L[p] = N_Points;                                                //Sto L[p] bazoume tous N kontinoterous geitones tou p pou briskoume me LSH
        condition = true; 
        
        for(int r: R[p])                                                //Gia kathe eikona sto R[p]                     
        {
            for(int t: L[p])                                            //Kai gia kathe geitona tou p
            {
                if(isLongestEdge(p,r,t) == true)                        //Koitame to trigwno an h akmh pr einai h megaluterh sto rigwno prt tote kanoume break
                {
                    condition = false;
                    break;
                }
            }
            if(condition == false)
                break;
            if(condition == true && find(L[p].begin(), L[p].end(), r) == L[p].end())               //An h pr den einai h megaluterh sto rigwno prt tote thn bazoume sto L[p]
                L[p].push_back(r);
        }
        
        for(int i = 0; i < L[p].size(); i++)
        {
            graph.addEdge(p,L[p][i]);                                   //Ftiaxnouem tis akmes tou grafou
        }
    }
}