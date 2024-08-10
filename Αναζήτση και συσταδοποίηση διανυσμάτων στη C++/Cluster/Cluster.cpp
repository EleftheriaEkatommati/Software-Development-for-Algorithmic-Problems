#include "Cluster.h"
#define Dim 784

vector<vector<double>> centroids;
vector<int> clusters;
vector<int> Points_Range;  
vector<bool> Probe;
vector<vector<bool>> searchSpace;

long long int Euclidian_dist(int input_number1, int input_number2)                      //Ypologizoume thn eukleidia apostash metaksi 2 dianusmatwn diastashs 784
{
    long long int dist = 0;
    for(int i = 0; i < Dim; i++)
    {
        dist += (Images[input_number1].pixels[i]-centroids[input_number2][i])*(Images[input_number1].pixels[i]-centroids[input_number2][i]);
    }
    return sqrt(dist);
}

void k_MeansPlusPlus_Init(int k)                                                        //Arxikopoihsh centroids
{
    centroids.resize(k, vector<double> (Dim));
    for(int i = 0; i < Dim; i++)                                                        //Arxikopoioume to prwto kentro me mia tuxaia eikona
        centroids[0][i] = Images[rand() % NUMBER_IMAGES].pixels[i];
    for(int i = 1; i < k; i++)
    {
        vector <double> minDistances(NUMBER_IMAGES, numeric_limits<double>::max());     //Arxikopoioume enan vector me NUMBER_IMAGES stoixeia kai kathe ena exei timh to apeiro
        double totalDistance = 0.0;
        for(size_t j = 0; j < NUMBER_IMAGES; j++)                                       //Gia kathe eikona
        {
            for(int c = 0; c < i; c++)                                                  //Gia ta mexri twra kentra pou exoume arxikopoihsei 
            {
                double Dist = Euclidian_dist(j, c);
                minDistances[j] = min(minDistances[j], Dist);                           //Ypologizoume thn apostash
            }
            totalDistance = totalDistance + minDistances[j];                            //Prosthetoume oles tis apostaseis
        }

        double PossibleTargetDist = (rand() % static_cast<int> (totalDistance * 1000)) / 1000.0;  //Exoume mia pithanh apostash apo 0 - totalDistance-1
        for(size_t j = 0; j < NUMBER_IMAGES; j++)
        {
            PossibleTargetDist = PossibleTargetDist - minDistances[j];
            if(PossibleTargetDist <= 0.0)                                               //Otan h apostash ginei mhdedn h arnhtikh shmainei oti eimaste arketa makria apo ta upoloipa kentra ara
            {
                for(int l = 0; l < Dim; l++)
                    centroids[i][l] = Images[j].pixels[l];                              //arxikopoioume to epomeno kentro me thn eikona sthn opoia mhdenithke h apostash 
                break;
            }
        } 
    }
}

void AssignToClusters(int k)                                                            //Anathetoume tis eikones sta clusters
{
    clusters.resize(NUMBER_IMAGES);
    for(size_t i = 0; i < NUMBER_IMAGES; i++)                                           //Gia kathe eikona
    {
        double minDistance = numeric_limits<double>::max();
        int clusterIndex = -1;
        for(int j = 0; j < k; j++)
        {
            double Dist = Euclidian_dist(i, j);                                         //Ypologizoume thn apostash ths kathe eikonas apo ola ta kentra
            if (Dist < minDistance)
            {
                minDistance = Dist;                                                     //Briskoume to kentro apo to opoio h eikona apozei ligotero kai thn bazoume se auto to cluster
                clusterIndex = j;
            }
        }
        clusters[i] = clusterIndex;                                                     //Ara sthn thesi i tou pinaka tha exoume apothikeumeno ton arithmo tou cluster sto opoio brisketai h eikona me arithmo i
    }
}

void updateCentroids(int k)                                                             //Auth h sunarthsh xrhsimopoieitai gia ton algorithmo tou Classic clustering enw h prohgoumenh gia LSh                       
{
    vector<int> clusterSizes(k, 0);
    vector<vector<double>> newCentroids(k, vector<double>(Dim, 0.0));

    for(size_t i = 0; i < NUMBER_IMAGES; i++)                                           //Gia kathe eikona
    {
        int clusterIndex = clusters[i];
        clusterSizes[clusterIndex]++;
        for(int j = 0; j < 784; j++)
        {
            newCentroids[clusterIndex][j] = newCentroids[clusterIndex][j] + Images[i].pixels[j];    //Prosthetoume tis suntetagmenes olwn twn eikonwn pou einai sto idio cluster
        }
    }

    for(int i = 0; i < k; i++)
    {
        if(clusterSizes[i] > 0)
        {
            for (size_t j = 0; j < 784; ++j) 
            {
                centroids[i][j] = newCentroids[i][j] / clusterSizes[i];                  //briskoume ton meso oro autwn twn suntetagmenwn kai etsi brhkame tis nees suntetagmenes tou kentrou 
            }
        }
    }
}

void AssignToClusters_LSH(int k, int L, int k_lsh, int MAXITERATION)                    //Kanoume clustering me Range Search LSH
{
    clusters.resize(NUMBER_IMAGES);
    k_MeansPlusPlus_Init(k);                                                            //Arxikopoioume ta kentra
    double R;
    for(int i = 0; i < Dim; i++)
    {
        R += (centroids[0][i]-centroids[1][i])*(centroids[0][i]-centroids[1][i]);       //Arxikopoioume thn aktina 
    }
    R = sqrt(R) / 2.0;
   
    Hash_initialize(L);                                                                 //Arxikopoioume tis domes gia ton algorithmo tou LSH
    HashFunctions_initialize(k_lsh, L);
    Hash_clear(L);
    for(int n = 0; n < NUMBER_IMAGES; n++)
        Euclidian_Hash(n, L, k_lsh);

    for (int m = 0; m < MAXITERATION; m++)                                              //Gia ena max plhthos epanalhpsewn 
    {
        Points_Range.clear();                   
        for(int i = 0; i < k; i++)                                                      
        {
            LSH_RangeSearch(i, L, k_lsh, R, centroids);                                 //Ekteloume ton algorithmo Range search LSH kai gemizoume ta clusters me eikones
            for (int a = 0; a < clusters_assigned.size(); a++)
            {
                clusters[a] = clusters_assigned[a];
            }
            updateCentroids(k);  
       }
       R *= 2.0;                                                                        //Se kathe epanalhpsh diaplasiazoume thn aktina
    }
    for (int m = 0; m < NUMBER_IMAGES; m++)                                             //Meta psaxnoueme oles tis eikones 
    {
        if (find(Points_Range.begin(), Points_Range.end(), m) == Points_Range.end())    //Autes poy den tis exoume balei se kapoio cluster
        {
            double min_dist = Euclidian_dist(m, 0);                                   
            int nearest_centroid = 0;
            for(int i = 0; i < k; i++)
            {
                double Dist = Euclidian_dist(m, i);                                     //Ypologizoume thn apostash apo ta kentra briskoume thn mikroterh 
                if (Dist < min_dist)
                {
                    min_dist = Dist;
                    nearest_centroid = i;
                }
                clusters[m] = nearest_centroid;                                         //Kai kanoume thn anathesi ths eikonas sto katallhlo cluster
            }
        }
    }
}

void AssignToClusters_Cube(int k, int M, int k_Cube, int MAXITERATION, int p)           //Kanoume clustering me Range Search LSH
{
    clusters.resize(NUMBER_IMAGES);
    k_MeansPlusPlus_Init(k);                                                            //Arxikopoioume ta kentra
    double R;
    for(int i = 0; i < Dim; i++)
    {
        R += (centroids[0][i]-centroids[1][i])*(centroids[0][i]-centroids[1][i]);       //Arxikopoioume thn aktina 
    }
    R = sqrt(R) / 2.0;

    Probe = GenerateRandomBinaryProbe(k_Cube);
    Images_To_Binary(k_Cube, Probe, centroids, k);
    for(int i = 0; i < k; i++)
        FindSearchSpace(M, k_Cube, i);
    clusters_assigned.clear();
    for (int m = 0; m < MAXITERATION; m++)
    {
        Points_Range.clear();
        for(int i = 0; i < k; i++)
        {
            Random_projection_to_HyperCube_RangeSearch(i, p, k_Cube, R, centroids, k);  //Ekteloume ton algorithmo Range search Hypercube kai gemizoume ta clusters me eikones
            for (int a = 0; a < clusters_assigned.size(); a++)
            {
                clusters[a] = (clusters_assigned[a]);
            }
            updateCentroids(k);  
       }
       R *= 2.0;                                                                        //Se kathe epanalhpsh diaplasiazoume thn aktina
    } 
    for (int m = 0; m < NUMBER_IMAGES; m++)                                             //Meta psaxnoueme oles tis eikones 
    {
        double min_dist = Euclidian_dist(m, 0);
        int nearest_centroid = 0;
        if (find(Points_Range.begin(), Points_Range.end(), m) == Points_Range.end())    //Autes poy den tis exoume balei se kapoio cluster
        {    
            for(int i = 0; i < k; i++)
            {
                double Dist = Euclidian_dist(m, i);
                if (Dist < min_dist)                                                     //Ypologizoume thn apostash apo ta kentra briskoume thn mikroterh 
                {
                    min_dist = Dist;
                    nearest_centroid = i;
                }
                clusters[m] = nearest_centroid;                                         //Kai kanoume thn anathesi ths eikonas sto katallhlo cluster
            }
        }
    }
}

void macQueen(int k, int L, int k_lsh, int MaxIteration, int p, int M, int k_Cube)      //Ektelesh algorithmou tou katallhlou algorithmou
{
    vector<int> clusterSizes(k, 0);
    if (Method == "Classic")
    {
        k_MeansPlusPlus_Init(k);
        for(int i = 0; i < MaxIteration; i++)
        {
            AssignToClusters(k);
            updateCentroids(k);
        }
    }
    if (Method == "LSH")
    {
        AssignToClusters_LSH(k, L, k_lsh, MaxIteration);
    }
    if (Method == "Hypercube")
    {
       AssignToClusters_Cube(k, M, k_Cube, MaxIteration, p);
    }
    for(int n = 0; n < NUMBER_IMAGES; n++)
    {
        int clusterIndex = clusters[n];
        clusterSizes[clusterIndex]++;
    }
    
    OutputF << "Algorithm: " << Method << endl << endl;
    for(int j = 0; j < k; j++)
    {
        OutputF << "CLUSTER-" << j << " { size: " << clusterSizes[j] <<  ", centroid:" << endl;
        for(int c = 0; c < 784; c++)
            OutputF << centroids[j][c] << " ";
        OutputF << "}" << endl << endl;
    }
}

double Euclidian_dist_between_images(int input_number1, int input_number2)              //Ypologizoume thn eukleidia apostash metaksi duo eikonwn         
{
    double dist = 0;
    for(int i = 0; i < Dim; i++)
    {
        dist += (Images[input_number1].pixels[i]-Images[input_number2].pixels[i])*(Images[input_number1].pixels[i]-Images[input_number2].pixels[i]);
    }
    return sqrt(dist);
}

double CalculateA(int N_Image)                                                          //Ypologizoume to a gia to Silhouette
{
    int cluster = clusters[N_Image];
    double sumDistance = 0.0;
    int count = 0;
    for(int i = 0; i < NUMBER_IMAGES; i++)                                              //Gia oles tis eikones
    {
        if(N_Image != i && clusters[i] == cluster)                                      //Gia oles tis eikones pou einai sto idio cluster
        {
            sumDistance = sumDistance + Euclidian_dist_between_images(N_Image, i);      //Ypologizoume to athroisma twn apostasewn autwn twn eikonwn
            count++;
        }
    }
    if(count == 0)
        return 0.0;
    return sumDistance/count;                                                           //Briskoume thn mesh apostash
}

double CalculateB(int N_Image, int k)                                                   //Ypologizoume to b gia to Silhouette
{
    double Min_Dist = numeric_limits<double>::infinity();
    int cluster = clusters[N_Image];
    for (int i = 0; i < k; i++)                                                         //Gia kathe cluster
    {
        if(cluster == i)                                                                //Kane skip thn epanalhpsi an to cluster ths eikonas einai idio me auto ths loupas                       
            continue;
        double sumDistance = 0.0;
        int count = 0;
        for(int j = 0; j < NUMBER_IMAGES; j++)                                          //Gia oles tis eikones
        {
            if(clusters[j] == i)
            {
                sumDistance = sumDistance + Euclidian_dist_between_images(N_Image, j);  //Ypologizoume thn apostash ths eikonas apo tis eikones enos allou cluster
                count++;
            }
        }
        sumDistance = sumDistance / count;                                              //Ypologizoume thn mesh apostash
        if(count > 0)
        {
            Min_Dist = min(Min_Dist, sumDistance);                                      //Apo oles tis meses apostaseis kratame thn mikroterh 
        }
    }
    return Min_Dist;
}

void OutFile(int k, int k_lsh, int maxIterations, int L, int probes, int M, int k_Cube)
{
    auto start = chrono::high_resolution_clock::now();
    macQueen(k, L, k_LSH, maxIterations, probes, M, k_Cube);   
    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> Duration = finish - start;       
    OutputF << endl << "Clustering_time: " << Duration.count() << endl;      

    if(CompFlag == 1)                                                                   //An o xrhsths dwsei sth grammh entolwn to -complete
    {
        vector <vector<int>> NumberImages_Cluster;                                      //Sto vector auto tha apothikeuoume poio cluster exei poies eikones
        NumberImages_Cluster.resize(k, vector<int>(NUMBER_IMAGES));                     //Ton kanoume resize
        for(int g = 0; g < k; g++)
        {
            NumberImages_Cluster[g].erase(remove(NumberImages_Cluster[g].begin(), NumberImages_Cluster[g].end(), 0), NumberImages_Cluster[g].end());
            //Afairoume ola ta stoixeia me timh mhden apo ton NumberImages_Cluster pou dhmiourghthikan kanontas to resize
        }
        for(int i = 0; i < NUMBER_IMAGES; i++)                                          //Gemizoume ton NumberImages_Cluster
        {
            int cluster = clusters[i];                                                  //Xrhsimopoioume ton pinaka clusters pou exoume apothikeusei sto index i ton arithmo tou cluster sto opoio brisketai h eikona i 
            NumberImages_Cluster[cluster].push_back(i);                                 //Pame sto kathe cluster kai bazoume ton arithmo ths eikonas
        }
        for(int c = 0; c < k; c++)                                                      //kanoume tis ektupwseis sto arxeio eksodou
        {    
            OutputF << "CLUSTER-" << c+1 << " { ";
            for(int j = 0; j < NumberImages_Cluster[c].size(); j++)
                OutputF << NumberImages_Cluster[c][j] << " ";
            OutputF << "}" << endl;
        }
    } 
    OutputF << "Silhouette: [";                                                         //Gia to silhouette
    vector<int> Images_Cluster;
    Images_Cluster.resize(k);
    for(int i = 0; i < NUMBER_IMAGES; i++)
    {
        for(int j = 0; j < k; j++)
        {
            if(clusters[i] == j)
                Images_Cluster[j] = i;
        }
    }
    double stotal = 0.0;
    for(int l = 0; l < k; l++)
    {
        double a = CalculateA(Images_Cluster[l]);                                       //Ypologizoume to a gia kathe cluster
        double b = CalculateB(Images_Cluster[l], k);                                    //Ypologizoume to b gia kathe cluster
        double s = (b - a) / max(a, b);                                                 //Briskoume ta s_i 
        stotal = stotal + s;                                                            //Kai upologizoume to stotal 
        OutputF << s << " , ";
    }
    stotal = stotal / k;
    OutputF << stotal << "]" << endl;                                                   //Kanoume tis ektupwseis sto arxeio eksodou
}