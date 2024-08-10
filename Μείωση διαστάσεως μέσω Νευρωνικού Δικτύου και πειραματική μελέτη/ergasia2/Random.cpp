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

int generateRandomNumber_uniform_distribution() 
{
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> distribution(0, NUMBER_IMAGES-1);
    int random_number = distribution(gen);

    return random_number;
}