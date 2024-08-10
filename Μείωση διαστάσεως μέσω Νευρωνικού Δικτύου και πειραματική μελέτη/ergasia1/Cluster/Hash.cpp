#include "Hash.h"
#define TableSize (NUMBER_IMAGES/8)
#define maxElements 10000
long long int BigNumber (pow(2,32) - 5);
int w = 100;
vector<int> clusters_assigned;

double Random_Num_ND(void) 
{
    random_device Random_Device{};                                                      //Ftiaxnoume thn gennhtria tuxaiwn arithmwn  
    mt19937 generator{Random_Device()};

    normal_distribution<float> distr{0.0, 1.0};  
    double randomValue = distr(generator);

    return round(randomValue);
}

float Random_Num_Uniform(void) 
{
    random_device Random_Device;            
    uniform_real_distribution<float> distr (0.0, (float) w);
    float randomValue = distr(Random_Device);

    return randomValue;
}

void Hash_initialize(int L) 
{
    Euclidian_Hash_Tables.resize(L, vector<vector<long long unsigned int>>(TableSize, vector<long long unsigned int>(maxElements)));
    //Arxikopoioume ta HashTables pou einai mia trisdiastath domh. H mia diastash orizei ton arithmo twn tables pou tha exoume
    //kai einai isos me L. H deuterh diastash einai to megethos tou slot se kathe bucket. Kai h trith diastash perigrafei 
    //to poses eikones mporoume na exoume se kathe slot tou kathe bucket.
}

void Hash_clear(int L)                                                                  //Sbhnoume ola ta staixeiia me timh mhden apo ta hash_tables pou dhmiourghthhkan apo to arxiko resize
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
        v[i].clear();                                                                   //Svhnoume ola ta "skoupidia" pou einai apothikeumena ston vector me thn dhmiourgia tou
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

long long int modulo(long long int a, long long int b)                                  //Xrhsimopoioume auth thn sunartsh gia na eimaste sigouroi oti to apotelesma
{                                                                                       //tou modulo tha einai enas thetikos arithmos
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
            for(int m = 0; m < Dim; m++)                                                //Ypologizoume to eswteriko ginemeno tou dianusmatos mias eikonas me ton vector v
            {
                x = Images[number_image][m];
                Res = Res + x * v[HashFunctions_Amplified[i][j]][m];                    //Apothikeuoume to apotelesma sth metablhth Res 
            }
            Res += t[j];                                                                //Prosthetoume to dianusma t
            Res = floor(Res/(double) w);                                                //Briskoume to katw meros ths diaireshs tou Res me to window 
            Res = Res*R[j];
            Sum_2 += Res;
        }
        long long unsigned int pos = modulo(Sum_2, BigNumber); 
		pos = modulo(pos,TableSize);
        Euclidian_Hash_Tables[i][pos].push_back(number_image);                          //Bazoume gia thn g_i function sth thesh pos tou slot ton arithmo ths kathe eikonas
    }
}

long long int Euclidian_dist_LSH(int input_number, int centroid_number, vector<vector<double>> centroids)                       //Ypologizoume thn eukleidia apostash metaksi 2 dianusmatwn diastashs Dim
{
    long long int dist = 0;
    for(int i = 0; i < Dim; i++)
    {
        dist += (Images[input_number][i]-centroids[centroid_number][i])*(Images[input_number][i]-centroids[centroid_number][i]);
    }
    return sqrt(dist);
}

long long unsigned int Centroid_Hash(int C_number, int L_th, int k, vector<vector<double>> centroids)
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
            x = centroids[C_number][m];
            Res = Res + x * v[HashFunctions_Amplified[L_th][j]][m];                    //Apothikeuoume to apotelesma sth metablhth Res 
        }
        Res += t[j];                                                                   //Prosthetoume to dianusma t
        Res = floor(Res/(double) w);                                                   //Briskoume to katw meros ths diaireshs tou Res me to window 
        Res = Res*R[j];
        Sum_2 += Res;
    }
    long long unsigned int pos = modulo(Sum_2, BigNumber); 
    pos = modulo(pos,TableSize);
    return pos;
}

void LSH_RangeSearch(int C_number, int L, int k, double R, vector<vector<double>> centroids)     //Range Search LSH
{
    clusters_assigned.resize(NUMBER_IMAGES);
    short int Flag;
	int Pos_HT;
	long long unsigned int Dist;
    for (int i = 0; i < L; i++)                                                        //Psaxnoume ola ta hash tables gia to query
    {
        Pos_HT = Centroid_Hash(C_number, i, k, centroids);
        //Gia to kathe hash table psaxnoume se oloklhro to slot tou na broume to dianusma me thn mikroterh apostash
        for(auto j = Euclidian_Hash_Tables[i][Pos_HT].begin(); j != Euclidian_Hash_Tables[i][Pos_HT].end(); j++)
        {
            Dist = Euclidian_dist_LSH(*j, C_number, centroids);
            
            if(Dist < R)
            {
                Flag = 0;
                for(auto i = Points_Range.begin(); i != Points_Range.end(); i++)
                {
                    if(*i == *j)
                        Flag = 1;
                }
                if (Flag == 0)
                {    
                    clusters_assigned[*j] = C_number;
                    Points_Range.push_back(*j);
                }                                
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<bool>> BinaryImages;
vector<vector<bool>> BinaryCentroid;   

int HammingDistance(const vector<bool> a, const vector<bool> b) 
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

void Images_To_Binary(int k_cube, const vector<bool> probe, vector<vector<double>> centroids, int K)
{
    vector<int> Random;
    Random.resize(256);
    for(int l = 0; l < 256; l++)
        Random[l]= -2;
    BinaryImages.resize(NUMBER_IMAGES, vector<bool> (k_cube));
    BinaryCentroid.resize(K, vector<bool> (k_cube));

    for(int j = 0; j < NUMBER_IMAGES; j++)
    {        
        for(int i = 0; i < Dim; i++)
        {    
            if (Random[Images[j][i]] == -2)
            {
                int r = rand() % 2;
                BinaryImages[j][i%k_cube] = r;
                Random[Images[j][i]] = r;
            }
            else if(Images[j][i] != 0)
            {
                BinaryImages[j][i%k_cube] = Random[Images[j][i]];
            }
        }
    }
    for(int l = 0; l < K; l++)
    {    
        for(int i = 0; i < Dim; i++)
        {    
            if (Random[centroids[l][i]] == -2)
            {
                int r = rand() % 2;
                BinaryCentroid[l][i%k_cube] = r;
                Random[centroids[l][i]] = r;
            }
            else if(centroids[l][i] != 0)
            {
                BinaryCentroid[l][i%k_cube] =  Random[centroids[l][i]];
            }
        }
    }
}

vector<bool> GenerateRandomBinaryProbe(int k)
{
    vector<bool> probe;
    probe.resize(k);
    for (int i = 0; i < k; i++) 
    {  
        probe[i] = (rand() % 2);
    }
    return probe;
}

void FindSearchSpace(int M, int k, int C_number) 
{
    searchSpace.resize(NUMBER_IMAGES, vector<bool>(k));
    for (size_t i = 0; i < BinaryImages.size(); ++i) 
    {
        const vector<bool>& point = BinaryImages[i];
        if (HammingDistance(point, BinaryCentroid[C_number]) <= HammingDistance(Probe, BinaryCentroid[C_number])) 
        {
            searchSpace.push_back(point);
        }
    }
    RandomlySelectMPoints(searchSpace, M);
}

void RandomlySelectMPoints(vector<vector<bool>>& points, int M) 
{
    if (points.size() > M) 
    {
        random_shuffle(points.begin(), points.end());
        points.resize(M);
    }
}

void Random_projection_to_HyperCube_RangeSearch(int C_Number, int p, int k_Cube, int R, vector<vector<double>> centroids, int K)     //Ekteloume ton algorithmo tou uperkubou me Range Search
{
    int Flag;
    clusters_assigned.resize(NUMBER_IMAGES);
    for (size_t i = 0; i < searchSpace.size(); ++i) 
    {
        const vector<bool>& point = searchSpace[i];
        int distance = Euclidian_dist_LSH(i, C_Number, centroids);
        if (distance < R) 
        {
            Flag = 0;
            for(auto n = Points_Range.begin(); n != Points_Range.end(); n++)            //Elegxoume an exoume hdh brei thn eikona auth 
            {
                if(*n == i)
                    Flag = 1;
            }  
            if (Flag == 0)       
            {    
                Points_Range.push_back(i);
                clusters_assigned[i] = (C_Number);
            }
        }
    }
}