//sdi2000014 , sdi2000048
#include "Hash.h"

int main(int argc, char* argv[]) 
{
    int k_1 = Input(argc,argv);
    if(k_1 == -1)
        return 0;
    int Q_number = rand() % Q_Image.size();
    Hash_initialize(L);
    HashFunctions_initialize(k, L);
    Hash_clear(L);
    for(int i = 0; i < NUMBER_IMAGES; i++)
        Euclidian_Hash(i, L, k);
    LSH_OutFile(L, k, Q_number, N, R);
    while(1)
    {
        OutputF.close();
        string str;
        cout << "If you want to stop write END else for redoing the algorithm (for the initial dimension) type continue: ";
        cin >> str;
        if(str == "END")
            return 0;
        else if(str == "continue")
        {
            int k_1 = Input(1,argv);
            if(k_1 == -1)
                return 0;
            Hash_initialize(L);
            HashFunctions_initialize(k, L);
            Hash_clear(L);
            for(int i = 0; i < NUMBER_IMAGES; i++)
                Euclidian_Hash(i, L, k);
            LSH_OutFile(L, k, Q_number, N, R);
        }
    }
}