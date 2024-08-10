#include "Random.h"

double Random_Num_ND(void) 
{
    random_device Random_Device{};            //Ftiaxnoume thn gennhtria tuxaiwn arithmwn  
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