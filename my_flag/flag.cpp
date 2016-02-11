#include "flag.h"

Flag::Flag()
{
    for(int i=0; i<springsHigh; i++)
    {
        for(int j=0; j<springsWide; j++)
        {
            springs[i][j] = new Spring();
        }
    }

}

Flag::~Flag()
{
    cout << "Flag Destruction\n";
}
