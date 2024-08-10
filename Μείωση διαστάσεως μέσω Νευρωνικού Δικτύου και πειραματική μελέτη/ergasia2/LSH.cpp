#include "LSH.h"
#define TableSize (NUMBER_IMAGES/8)
#define maxElements 10000
long long int M (pow(2,32) - 5);
int w = 100;
vector<int> N_Points;    

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
    long long unsigned int pos;
    for(int i = 0; i < L; i++)
    {
        long long int Sum_2 = 0;
        for(int j = 0 ; j < k ; j++)
        {
            Res = 0;
            for(int m = 0; m < Dim; m++)                                               //Ypologizoume to eswteriko ginemeno tou dianusmatos mias eikonas me ton vector v
            {
                x = Images[number_image][m];
                Res = Res + x * v[HashFunctions_Amplified[i][j]][m];                   //Apothikeuoume to apotelesma sth metablhth Res 
            }
            Res += t[j];                                                               //Prosthetoume to dianusma t
            Res = floor(Res/(double) w);                                               //Briskoume to katw meros ths diaireshs tou Res me to window 
            Res = Res*R[j];
            Sum_2 += Res;
        }
        pos = modulo(Sum_2, M); 
		pos = modulo(pos,TableSize);
        Euclidian_Hash_Tables[i][pos].push_back(number_image);                         //Bazoume gia thn g_i function sth thesh pos tou slot ton arithmo ths kathe eikonas
    }
}

long long int Euclidian_Dist(int input_number, int query_number)                       //Ypologizoume thn eukleidia apostash metaksi 2 dianusmatwn diastashs Dim
{
    long long int dist = 0;
    for(int i = 0; i < Dim; i++)
    {
        dist += (Images[input_number][i]-Images[query_number][i])*(Images[input_number][i]-Images[query_number][i]);
    }
    return sqrt(dist);
}

long long int Euclidian_dist(int input_number, int query_number)                       //Ypologizoume thn eukleidia apostash metaksi 2 dianusmatwn diastashs Dim
{
    long long int dist = 0;
    for(int i = 0; i < Dim; i++)
    {
        dist += (Images[input_number][i]-Q_Image[query_number][i])*(Images[input_number][i]-Q_Image[query_number][i]);
    }
    return sqrt(dist);
}

long long int Euclidian_dist_initial(int input_number, int query_number)             //Ypologizoume thn eukleidia apostash metaksi 2 dianusmatwn diastashs 784
{
    long long int dist = 0;
    for(int i = 0; i < Dim_initial; i++)
    {
        dist += (Images_initial[input_number].pixels[i]-Q_Image_initial[query_number].pixels[i])*(Images_initial[input_number].pixels[i]-Q_Image_initial[query_number].pixels[i]);
    }
    return sqrt(dist);
}

long long unsigned int Query_Hash(int I_number, int L_th, int k)
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
            x = Images[I_number][m];
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

void N_NearestNeighbors_LSH(int I_number, int L, int k, int N)                         //N-nearest neighbors LSH
{
	int Pos_HT = 0;
	long long unsigned int Dist;
    vector<int> k_dist;
    N_Points.clear();
    k_dist.clear();
    
    for (int i = 0; i < L; i++)                                                        //Psaxnoume ola ta hash tables gia to query
    {
        Pos_HT = Query_Hash(I_number, i, k);
        for(auto j = Euclidian_Hash_Tables[i][Pos_HT].begin(); j != Euclidian_Hash_Tables[i][Pos_HT].end(); j++)
        {
            if(I_number != *j)
            {
                Dist = Euclidian_Dist(*j, I_number);
                
                if(k_dist.size() < N && *j != I_number)
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
                    if(k_dist.size() == N && Dist <= maxElement && find(N_Points.begin(), N_Points.end(), *j) == N_Points.end() && *j != I_number)
                    {    
                        k_dist[max_w] = Dist;
                        N_Points[max_w] = *j;
                    }
                }
            }
            else    
                break;
        }
    }
}

long long unsigned int Euclidian_Nearest_N(int Q_number)                               //Exhaustive gia nearest neighbors
{
    double Min_dist = numeric_limits<double>::infinity();
    long long unsigned int Dist;
    for(long long unsigned int i = 0; i < NUMBER_IMAGES; i++)
    {
        Dist = Euclidian_dist_initial(i, Q_number);
        if(Dist < Min_dist && i != Q_number)
        {  
            Min_dist = Dist;
        }
    }
    OutputF << "DistanceTrue: " << Min_dist << endl; 
    return Min_dist;
}

void Euclidian_NN(int Q_number, int N)                                                 //Exhaustive gia N-nearest neighbors
{
    vector<int> k_dist;
    vector<int> NN;
    NN.clear();
    k_dist.clear();
    long long unsigned int Dist = 0;
    for (long long unsigned int i = 0; i < NUMBER_IMAGES; i++)
    {
        Dist = Euclidian_dist_initial(i, Q_number);
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
