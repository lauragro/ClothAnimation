#ifndef FLAG_H
#define FLAG_H

#include "spring.h"
class Spring;

class Flag
{
public:
    // constructor/destructor
    Flag();
    ~Flag();

    // grid contataining all springs
    static const int springsWide = 9;
    static const int springsHigh = 6;
    Spring *springs[springsHigh][springsWide];

};

#endif // FLAG_H
