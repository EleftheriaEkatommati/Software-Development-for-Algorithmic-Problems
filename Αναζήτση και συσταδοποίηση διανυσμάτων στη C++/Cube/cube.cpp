//sdi2000014 , sdi2000048
#include "Cube.h"
#define Q_number 100

int main(int argc, char* argv[]) 
{
    int In = Input(argc,argv);
    if(In == -1)
        return 0; 

    Probe = GenerateRandomBinaryProbe(k);
    Images_To_Binary(Q_number, k, Probe);
    Cube_OutFile(probes, k, Q_number, N, R);
    
    while(1)
    {
        OutputF.close();
        string str;
        cout << "If you want to stop write END else for redoing the algorithm type continue: ";
        cin >> str;
        if(str == "END")
            return 0;
        else if(str == "continue")
        {
            int k_1 = Input(1,argv);
            if(k_1 == -1)
                return 0;
            Probe = GenerateRandomBinaryProbe(k);
            Images_To_Binary(Q_number, k, Probe);
            Cube_OutFile(probes, k, Q_number, N, R);
        }
    }
    return 0;
}