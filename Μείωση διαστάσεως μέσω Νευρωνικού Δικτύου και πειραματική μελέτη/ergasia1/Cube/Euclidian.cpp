#include "Euclidian.h"
int True_Neighbor = 0;

long long int Euclidian_dist(int input_number, int query_number)    //Ypologizoume thn eukleidia apostash metaksi 2 dianusmatwn diastashs Dim
{
    long long int dist = 0;
    for(int i = 0; i < Dim; i++)
    {
        dist += (Images[input_number][i]-Q_Image[query_number][i])*(Images[input_number][i]-Q_Image[query_number][i]);
    }
    return sqrt(dist);
}

long long int Euclidian_dist_initial(int input_number, int query_number)             
{
    long long int dist = 0;
    for(int i = 0; i < Dim_initial; i++)
    {
        dist += (Images_initial[input_number].pixels[i]-Q_Image_initial[query_number].pixels[i])*(Images_initial[input_number].pixels[i]-Q_Image_initial[query_number].pixels[i]);
    }
    return sqrt(dist);
}

void Euclidian_Nearest_N(int Q_number)                              //Ypologizoume me ton exhaustive algorithmo ton plhsiestero geitona                   
{
    double Min_dist = numeric_limits<double>::infinity();
    long long unsigned int Dist, Min_Number_Image = 1;
    for(long long unsigned int i = 0; i < NUMBER_IMAGES; i++)
    {
        Dist = Euclidian_dist_initial(i, Q_number);
        if(Dist < Min_dist && i != Q_number)
        {  
            Min_dist = Dist;
            Min_Number_Image = i;
        }
    }
    True_Neighbor = Min_Number_Image;
    OutputF << "DistanceTrue: " << Min_dist << endl; 
}

void Euclidian_NNN(int Q_number, int N)                             //exhaustive gia N-nearest neighbors
{
    vector<int> k_dist;
    vector<int> NN;
    NN.clear();
    k_dist.clear();
    long long unsigned int Dist;
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
    OutputF << "DistanceTrue: " << k_dist[N-1] << endl;
}