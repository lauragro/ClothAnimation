#ifndef GROUND_H
#define GROUND_H

#include "foundation.h"

class Ground
{
public:
    Ground(int width);
    ~Ground();

    draw();

private:
    int width;  // length of a side of the square ground
};

#endif // GROUND_H
