#include "Hash.h"
#define Dim 784
#define TableSize (NUMBER_IMAGES/8)
#define maxElements 10000
long long int M (pow(2,32) - 5);
int w = 100;

void Hash_initialize(int L) 
{
    Euclidian_Hash_Tables.resize(L, vector<vector<long long unsigned int>>(TableSize, vector<long long unsigned int>(maxElements)));
    //Arxikopoioume ta HashTables pou einai mia trisdiastath domh. H mia diastash orizei ton arithmo twn tables pou tha exoume
    //kai einai isos me L. H deuterh diastash einai to megethos tou slot se kathe bucket. Kai h trith diastash perigrafei 
    //to poses eikones mporoume na exoume se kathe slot tou kathe bucket.
}

void Hash_clear(int L)                                                                 //Sbhnoume ola ta staixeiia me timh mhden apo ta hash_tables pou dhmiourghthhkan apo to arxiko resize
{
    int Max = TableSize;
    for(int g = 0; g < L; g++)
    {
        for(int i = 0; i < Max;i ++)
        {
            Euclidian_Hash_Tables[g][i].erase(remove(Euclidian_Hash_Tables[g][i].begin(), Euclidian_Hash_Tables[g][i].end(), 0), Euclidian_Hash_Tables[g][i].end());
            //Afairoume ola ta stoixeia me timh mhden apo ta hash_Tables xwris na allaksei to megethos tou
        }
    }
}

void HashFunctions_initialize(int k, int L)
{
    //Arxikopoioume ton vector v 
    v.resize(k, vector<double>(Dim));     
    for(int i = 0; i < k; i++)
    {
        v[i].clear();                                                                  //Svhnoume ola ta "skoupidia" pou einai apothikeumena ston vector me thn dhmiourgia tou
        for(int j = 0; j < Dim; j++)
        {
            double Random_ND = Random_Num_ND();
            v[i].push_back(Random_ND);
        }
    }

    //Arxikopoioume tis sunarthseis g
    HashFunctions_Amplified.resize(L, vector<int> (k));
    srand(time(0));
    int m = 0; 
    int f_number = 0;
    for(int i = 0; i < L; i++)
    {
        HashFunctions_Amplified[i].clear();
        //orizoume thn seira pou kathe g tha kalei tis h_i functions
        while(m < k)
        {
            f_number = rand() % k; 
            if(find(HashFunctions_Amplified[i].begin(), HashFunctions_Amplified[i].end(), f_number) == HashFunctions_Amplified[i].end())
            {
                m++;
                HashFunctions_Amplified[i].push_back(f_number);
            }
        }
    }

    //Tha arxikopoihsoume to t gia kathe hash function
    t.clear();
    float random_number;
    for(int i = 0; i < k; i++)
    {
        random_number = Random_Num_Uniform();
        t.push_back(random_number);
    }
}

long long int modulo(long long int a, long long int b)                                 //Xrhsimopoioume auth thn sunartsh gia na eimaste sigouroi oti to apotelesma
{                                                                                      //tou modulo tha einai enas thetikos arithmos
    long long int c = a % b;
    long long int d = c + b;
	return d % b;
}

void Euclidian_Hash(int number_image, int L, int k)
{   
    long long int Res;
    double x;
    vector <int> R;

    R.clear();
    for(int i = 0; i < k; i++)
    {    
        R.push_back(random());
    } 
    for(int i = 0; i < L; i++)
    {
        long long int Sum_2 = 0;
        for(int j = 0 ; j < k ; j++)
        {
            Res = 0;
            for(int m = 0; m < Dim; m++)                                               //Ypologizoume to eswteriko ginemeno tou dianusmatos mias eikonas me ton vector v
            {
                x = Images[number_image].pixels[m];
                Res = Res + x * v[HashFunctions_Amplified[i][j]][m];                   //Apothikeuoume to apotelesma sth metablhth Res 
            }
            Res += t[j];                                                               //Prosthetoume to dianusma t
            Res = floor(Res/(double) w);                                               //Briskoume to katw meros ths diaireshs tou Res me to window 
            Res = Res*R[j];
            Sum_2 += Res;
        }
        long long unsigned int pos = modulo(Sum_2, M); 
		pos = modulo(pos,TableSize);
        Euclidian_Hash_Tables[i][pos].push_back(number_image);                         //Bazoume gia thn g_i function sth thesh pos tou slot ton arithmo ths kathe eikonas
    }
}

long long int Euclidian_dist(int input_number, int query_number)                       //Ypologizoume thn eukleidia apostash metaksi 2 dianusmatwn diastashs 784
{
    long long int dist = 0;
    for(int i = 0; i < Dim; i++)
    {
        dist += (Images[input_number].pixels[i]-Q_Image[query_number].pixels[i])*(Images[input_number].pixels[i]-Q_Image[query_number].pixels[i]);
    }
    return sqrt(dist);
}

long long unsigned int Query_Hash(int Q_number, int L_th, int k)
{   
    long long int Res;
    double x;
    vector <int> R;

    R.clear();
    for(int i = 0; i < k; i++)
    {    
        R.push_back(random());
    } 
    long long int Sum_2 = 0;
    for(int j = 0 ; j < k ; j++)
    {
        Res = 0;
        for(int m = 0; m < Dim; m++)                                                   //Ypologizoume to eswteriko ginemeno tou dianusmatos mias eikonas me ton vector v
        {
            x = Q_Image[Q_number].pixels[m];
            Res = Res + x * v[HashFunctions_Amplified[L_th][j]][m];                    //Apothikeuoume to apotelesma sth metablhth Res 
        }
        Res += t[j];                                                                   //Prosthetoume to dianusma t
        Res = floor(Res/(double) w);                                                   //Briskoume to katw meros ths diaireshs tou Res me to window 
        Res = Res*R[j];
        Sum_2 += Res;
    }
    long long unsigned int pos = modulo(Sum_2, M); 
    pos = modulo(pos,TableSize);
    return pos;
}

int best_distance_true = 0;
int best_distance_aprox = 0;

void Euclidian_Nearest_N(int Q_number)                             
{
    double Min_dist = numeric_limits<double>::infinity();
    long long unsigned int Dist, Min_Number_Image = 0;
    for(long long unsigned int i = 0; i < NUMBER_IMAGES; i++)
    {
        Dist = Euclidian_dist(i, Q_number);
        if(Dist < Min_dist && i != Q_number)
        {  
            Min_dist = Dist;
            Min_Number_Image = i;
        }
    }
    best_distance_true = Min_dist;
    OutputF << "DistanceTrue:: " << Min_dist << endl; 
}

void LSH_Nearest_N(int Q_number, int L, int k)                                         //Ekteloume kai ton exhaustive algorithmo kai ton LSH gia Nearest neighbor
{
    int Pos_HT;
    short int Time_Break = 10*L;            
    long long unsigned int Dist;
    double Min_Dist = numeric_limits<double>::infinity();
    long long unsigned int Min_Number_Image = 1;
    for(int i = 0; i < L; i++)                                                         //Psaxnoume ola ta hash tables
    {
        Pos_HT = Query_Hash(Q_number, i, k);
        //Gia to kathe hash table psaxnoume se oloklhro to slot tou na broume to dianusma me thn mikroterh apostash
        for(auto j = Euclidian_Hash_Tables[i][Pos_HT].begin(); j != Euclidian_Hash_Tables[i][Pos_HT].end(); j++)
        {
            Dist = Euclidian_dist(*j, Q_number);
            if(Dist < Min_Dist && *j != Q_number)
            {
                Min_Dist = Dist;
                Min_Number_Image = *j;
            }
            Time_Break--;
            if(Time_Break <= 0)                                                        //Kanoume break otan o xronos mhdenisei giati shmainei oti o algorithmos 
                break;                                                                 //exei brei ton kontinotero geitona kai autos einai to beltisto apotelesma kai stamataei na psaxnei
        }
        Time_Break = 10*L;
    }
    best_distance_aprox = Min_Dist;
    OutputF << "Query: " << Q_number << endl;
    OutputF << "Nearest neighbor-1: " << Min_Number_Image << endl;
    OutputF << "DistanceLSH: " << Min_Dist << endl;
}

void LSH_RangeSearch(int Q_number, int L, int k, double R)                             //Range Search LSH
{
    short int Flag;
	int Pos_HT;
	long long unsigned int Dist;

    for (int i = 0; i < L; i++)                                                        //Psaxnoume ola ta hash tables gia to query
    {
        Pos_HT = Query_Hash(Q_number, i, k);
        //Gia to kathe hash table psaxnoume se oloklhro to slot tou na broume to dianusma me thn mikroterh apostash
        for(auto j = Euclidian_Hash_Tables[i][Pos_HT].begin(); j != Euclidian_Hash_Tables[i][Pos_HT].end(); j++)
        {
            Dist = Euclidian_dist(*j, Q_number);
            
            if(Dist < R && *j != Q_number)
            {
                Flag = 0;
                for(auto i = Points_Range.begin(); i != Points_Range.end(); i++)
                {
                    if(*i == *j)
                        Flag = 1;
                }
                if (Flag == 0)
                    Points_Range.push_back(*j);                                        //Apothikeuoume sthn domh Points_Range ta R pio kontina dianusmata
            }
           
        }
    }
	OutputF << endl << "R-Near Neighbours: " << endl;
    for(auto j = Points_Range.begin(); j != Points_Range.end(); j++)
        OutputF << "Image: " << *j << endl;
}

void N_NearestNeighbors_LSH(int Q_number, int L, int k, int N)                         //N-nearest neighbors LSH
{
	int Pos_HT;
	long long unsigned int Dist;
    vector<int> k_dist;
    N_Points.clear();
    k_dist.clear();

    for (int i = 0; i < L; i++)                                                        //Psaxnoume ola ta hash tables gia to query
    {
        Pos_HT = Query_Hash(Q_number, i, k);
        for(auto j = Euclidian_Hash_Tables[i][Pos_HT].begin(); j != Euclidian_Hash_Tables[i][Pos_HT].end(); j++)
        {
            Dist = Euclidian_dist(*j, Q_number);
            if(k_dist.size() < N && *j != Q_number)
            {
                N_Points.push_back(*j);
                k_dist.push_back(Dist);
            }
            else 
            {   
                int maxElement = k_dist[0];
                int max_w = 0;
                for (int w = 0; w < k_dist.size(); w++) 
                {
                    if (k_dist[w] > maxElement) 
                    {
                        maxElement = k_dist[w];  
                        max_w = w;
                    }
                }
                if(k_dist.size() == N && Dist < maxElement && find(N_Points.begin(), N_Points.end(), *j) == N_Points.end() && *j != Q_number)
                {    
                    k_dist[max_w] = Dist;
                    N_Points[max_w] = *j;
                }
            }
        }
    }
	OutputF << endl << "N-Near Neighbours: " << N_Points[N-1] <<  endl;
    OutputF << "DistanceLSH: " << k_dist[N-1] << endl;
}

void Euclidian_NN(int Q_number, int N)                                                 //exhaustive gia N-nearest neighbors
{
    vector<int> k_dist;
    vector<int> NN;
    NN.clear();
    k_dist.clear();
    long long unsigned int Dist;
    for (long long unsigned int i = 0; i < NUMBER_IMAGES; i++)
    {
        Dist = Euclidian_dist(i, Q_number);
        if(k_dist.size() < N && i != Q_number)
        {
            k_dist.push_back(Dist);
            NN.push_back(i);
        }
        else
        {
            int maxElement = k_dist[0];
            int max_w = 0;
            for (int w = 0; w < k_dist.size(); w++) 
            {
                if (k_dist[w] > maxElement) 
                {
                    maxElement = k_dist[w];  
                    max_w = w;
                }
            }
            if(k_dist.size() == N && Dist < maxElement && find(NN.begin(), NN.end(), i) == NN.end() && i != Q_number)
            {
                k_dist[max_w] = Dist;
                NN[max_w] = i;
            }
        }
    }
    OutputF << "Distancetrue: " << k_dist[N-1] << endl;
}

void LSH_OutFile(int L, int k, int Q_number, int N, int R)
{
    auto start = chrono::high_resolution_clock::now();
    LSH_Nearest_N(Q_number, L, k);
    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> Duration = finish - start;                                //Xronos gia LSH

    auto start1 = chrono::high_resolution_clock::now();
    Euclidian_Nearest_N(Q_number);
    auto finish1 = chrono::high_resolution_clock::now();                        
    chrono::duration<double> Duration1 = finish1 - start1;                             //Xronos gia exhaustive LSH

    auto start3 = chrono::high_resolution_clock::now();
    N_NearestNeighbors_LSH(Q_number, L, k, N);
    auto finish3 = chrono::high_resolution_clock::now();
    chrono::duration<double> Duration3 = finish - start;                               //Xronos gia N-nearest neighbors

    auto start4 = chrono::high_resolution_clock::now();
    Euclidian_NN(Q_number,N);
    auto finish4 = chrono::high_resolution_clock::now();                        
    chrono::duration<double> Duration4 = finish4 - start4;                             //Xronos gia exhaustive N-nearest neighbors

    auto start2 = chrono::high_resolution_clock::now();
    LSH_RangeSearch(Q_number, L, k, R);
    auto finish2 = chrono::high_resolution_clock::now();
    chrono::duration<double> Duration2 = finish2 - start2;                             //Xronos gia RangeSearch


    chrono::duration<double> Duration5 = Duration + Duration2 + Duration3;             //Sunolikos xronos LSH
    chrono::duration<double> Duration6 = Duration1 + Duration4;                        //Sunolikos xronos TRUE

    OutputF << endl << "tLsh: " << Duration5.count() << endl;
    OutputF << "tTrue: " << Duration6.count() << endl;
}