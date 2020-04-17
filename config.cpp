#include "config.h"

using namespace std;

void Config::nextLevel(int &score)
{
    if(score>=20)
    {
        multiplier = 2;
    }
}
