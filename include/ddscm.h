#ifndef DDSCM_H
#define DDSCM_H

#include "maptypes.h"

class DDSCubeMap: public CubeMap
{
public:
    Pixel getPixel(Side s, int x, int y) const override;
    void setPixel(Side s, int x, int y, Pixel px) override;
};

#endif // DDSCM_H
