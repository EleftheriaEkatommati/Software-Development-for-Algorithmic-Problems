#include "Cube.h"
#define Dim 784

vector<vector<bool>> searchSpace;
vector<vector<bool>> BinaryImages;
vector<bool> BinaryQuery;
vector<bool> Probe;

int HammingDistance(const vector<bool> a, const vector<bool> b)                //Ypologizoume thn hamming apostash metaksi duo binary dianusmatwn 
{
    int distance = 0;
    for (size_t i = 0; i < a.size(); ++i) 
    {
        if (a[i] != b[i]) 
        {
            distance++;
        }
    }
    return distance;
}

void Images_To_Binary(int Q_number, int k, const vector<bool> probe)           //Metatrepoume to dianusma ths apostashs se bianry dianusma diastashs k
{
    vector<int> Random;
    Random.resize(256);
    for(int l = 0; l < 256; l++)                                               //Se auton ton pinaka tha apothikeuoume sth thesh i 0 h 1. Wste an mas esei erthei o arithmos i na kseroume me ti na ton antikatasthsoume
        Random[l]= -2;                                                         //Ton arxikopoioume me -2 etsi wste na mporoume na kseroume an mas exei erthei o arithmos
    BinaryImages.resize(NUMBER_IMAGES, vector<bool> (k));
    BinaryQuery.resize(k);
    for(int j = 0; j < NUMBER_IMAGES; j++)                                     //Gia kathe eikona
    {        
        for(int i = 0; i < 784; i++)                                           
        {    
           if (Random[Images[j].pixels[i]] == -2)                              //An den mas exei ksana erthei o arithmos i tote kalooume thn rand 
            {
                int r = rand() % 2;
                BinaryImages[j][i%k] = r;                                      //To binary images einai diplos vector kai apothikeuoume gia oles tis eikones to binaary vector megethous k
                Random[Images[j].pixels[i]] = r;                               //Apothikeuoume to apotelesma ths rand ston pinaka
            }
            else if(Images[j].pixels[i] != 0)                                  //An mas exei erthei o arithmos tote den ksana kaloume thn rand apla briskoume thn timh pou exoume apothikeusei ston pinaka
            {
                BinaryImages[j][i%k] = Random[Images[j].pixels[i]];
            }
        }
    }
    for(int i = 0; i < 784; i++)                                               //Kanoume thn idia diadikasia kai gia to query
    {    
        if (Random[Q_Image[Q_number].pixels[i]] == -2)
        {
            int r = rand() % 2;
            BinaryQuery[i%k] = r;
            Random[Q_Image[Q_number].pixels[i]] = r;
        }
        else if(Q_Image[Q_number].pixels[i] != 0)
        {
            BinaryQuery[i%k] = Random[Q_Image[Q_number].pixels[i]];
        }
    }
}

vector<bool> GenerateRandomBinaryProbe(int k)                                  //Ftiaxnoume ena tuxaio dianusma me 0 kai 1 megethous k
{
    vector<bool> probe;
    probe.resize(k);
    for (int i = 0; i < k; i++) 
    {  
        probe[i] = (rand() % 2);
    }
    return probe;
}

void FindSearchSpace(int M)                                                    //Briskoume tis eikones gia tis opoies tha ektelesoume ton algorithmo
{
    searchSpace.resize(NUMBER_IMAGES, vector<bool>(k));
    for (size_t i = 0; i < BinaryImages.size(); ++i)                           //Gia kathe eikona
    {
        const vector<bool>& point = BinaryImages[i];
        if (HammingDistance(point, BinaryQuery) <= HammingDistance(Probe, BinaryQuery)) 
        {
            searchSpace.push_back(point);                                      //Kratame thn eikona mono an h hamming apostash tou query kai tou shmeiou einai mikroterh apo auth tou query me to probe
        }
    }
    RandomlySelectMPoints(searchSpace, M);                                     //Kratame M apo autes tis eikones
}

void RandomlySelectMPoints(vector<vector<bool>>& points, int M)                //Sunarthsh gia na dialegoume tuxaia M apo oles tis eikones
{
    if (points.size() > M) 
    {
        random_shuffle(points.begin(), points.end());
        points.resize(M);
    }
}

int best_distance_aprox = 0;
void Random_projection_to_HyperCube(int p, int k, int Q_number)                //Ekteloume ton algorithmo Hypercube
{
    int bestDistance = k;
    int nearestNeighbor;
    for (int probe = 0; probe < p; probe++)                                    //Gia oles tis korufes
    {       
        for (size_t i = 0; i < searchSpace.size(); ++i)                        //Gia oles tis eikones pou uparxoun sth sugkekrimenh perioxh 
        {
            const vector<bool>& point = searchSpace[i];
            int distance = HammingDistance(point, BinaryQuery);                //Ypologizoume thn hamming apostash 
            if (distance < bestDistance && i != Q_number)                      //Briskoume thn mikroterh apostash kai ton kontinotero geitona
            {
                bestDistance = distance;
                nearestNeighbor = i; 
            }
        }
        Probe = GenerateRandomBinaryProbe(k);
    }
    bestDistance = Euclidian_dist(nearestNeighbor, Q_number);
    best_distance_aprox = bestDistance;
    OutputF << "Query: " << Q_number << endl;                                  //Kanoume tis katallhles ektupwseis sto arxeio eksodou
    OutputF << "Nearest neighbor-1: " << nearestNeighbor << endl;
    OutputF << "DistanceCube: " << bestDistance << endl;
}

void Random_projection_to_HyperCube_N(int Q_number, int p, int k, int N)       //Psaxnoume tous N kontinoterous geitones
{
	long long unsigned int Dist;
    vector<int> k_dist;
    N_Points.clear();
    k_dist.clear();

    for (int probe = 0; probe < p; probe++)                                    //Psaxnoume oles tis korufes
    {
        for (size_t i = 0; i < searchSpace.size(); ++i)                        //Gia oles tis eikones pou uparxoun sth sugkekrimenh perioxh 
        {
            const vector<bool>& point = searchSpace[i];
            int distance = HammingDistance(point, BinaryQuery);                //Ypologizoume thn hamming distance    
            if(k_dist.size() < N && i != Q_number)                             //Kratame tis N prwtes apostaseis se enan pinaka kai tous arithmous twn eikonwn se enan allo         
            {
                N_Points.push_back(i);                                                       
                k_dist.push_back(distance);
            }
            else                                                               //An o pinakas autos exei gemisei 
            {
                int maxElement = k_dist[0];                                    //Briskoume to max element kathe fora tou pinaka twn apostasevn 
                int max_w = 0;
                for (int w = 0; w < k_dist.size(); w++) 
                {
                    if (k_dist[w] > maxElement) 
                    {
                        maxElement = k_dist[w];  
                        max_w = w;
                    }
                }                                                              //Sugkrinoume thn max apostash kai an broume mikroterh antikathistoume thn megaluterh me auth 
                if(k_dist.size() == N && distance < maxElement && find(N_Points.begin(), N_Points.end(), i) == N_Points.end() && i != Q_number)
                {    
                    k_dist[max_w] = distance;
                    N_Points[max_w] = i;
                }
            }
        }
        Probe = GenerateRandomBinaryProbe(k);
    }
    double bestDistance = Euclidian_dist(N_Points[N-1], Q_number);
    OutputF << endl << "N-Near Neighbours: " << N_Points[N-1] << endl;         //Katallhles ektupwseis sto arxeio eksodou
    OutputF << "DistanceCube: " << bestDistance << endl;
}

void Random_projection_to_HyperCube_RangeSearch(int Q_Number, int p, int k, int R)     //Ekteloume ton algorithmo tou uperkubou me Range Search
{
    int Flag;
    for (int probe = 0; probe < p; probe++)                                            //Gia kathe korufh
    {
        for (size_t i = 0; i < searchSpace.size(); ++i)                                //Gia oles tis eikones pou uparxoun sth sugkekrimenh perioxh 
        {
            const vector<bool>& point = searchSpace[i];
            int distance = Euclidian_dist(i, Q_Number);
            if (distance < R && i != Q_Number)                                         //An h apostash einai mirkoterh apo to R kratame thn eikona
            {
                Flag = 0;
                for(auto n = Points_Range.begin(); n != Points_Range.end(); n++)       //Elegxoume an exoume hdh brei thn eikona auth 
                {
                    if(*n == i)
                        Flag = 1;
                }  
                if (Flag == 0)                                                         //An den exoume brei thn eikona tote thn kanoume push ston katallhlo pinaka 
                    Points_Range.push_back(i);
            }
        }
        Probe = GenerateRandomBinaryProbe(k);
    }
    OutputF << endl << "R-Near Neighbours: " << endl;                                  //Kanoume tis katallhles ektupwseis sto arxeio eksodou
    for(auto j = Points_Range.begin(); j != Points_Range.end(); j++)
        OutputF << "Image: " << *j << endl;
}

void Cube_OutFile(int p, int k, int Q_number, int N, int R)                            //Kaloume tis katallhles sunarthseis gia thn ektelesh twn algorithmwm kai ypologizoume kai tous xronous
{
    FindSearchSpace(M);
    auto start = chrono::high_resolution_clock::now();                                 //Xronos gia Cube
    Random_projection_to_HyperCube(p, k, Q_number);
    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> Duration = finish - start;        

    auto start1 = chrono::high_resolution_clock::now();
    Euclidian_Nearest_N(Q_number);
    auto finish1 = chrono::high_resolution_clock::now();                        
    chrono::duration<double> Duration1 = finish1 - start1;                             //Xronos gia exhaustive    

    auto start3 = chrono::high_resolution_clock::now();
    Random_projection_to_HyperCube_N(Q_number, p, k, N);                               //Xronos gia N-nearest neighbors       
    auto finish3 = chrono::high_resolution_clock::now();                        
    chrono::duration<double> Duration3 = finish3 - start3;   

    auto start4 = chrono::high_resolution_clock::now();
    Euclidian_NNN(Q_number,N);
    auto finish4 = chrono::high_resolution_clock::now();                        
    chrono::duration<double> Duration4 = finish4 - start4;                             //Xronos gia exhaustive N-nearest neighbors          

    auto start2 = chrono::high_resolution_clock::now();
    Random_projection_to_HyperCube_RangeSearch(Q_number, p, k, R);
    auto finish2 = chrono::high_resolution_clock::now();                        
    chrono::duration<double> Duration2 = finish2 - start2;   

    chrono::duration<double> Duration5 = Duration + Duration2 + Duration3;             //Sunolikos xronos Cube
    chrono::duration<double> Duration6 = Duration1 + Duration4;                        //Sunolikos xronos TRUE

    OutputF << endl << "tCube: " << Duration5.count() << endl;
    OutputF << "tTrue: " << Duration6.count() << endl;         
}