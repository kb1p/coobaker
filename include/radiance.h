#ifndef RADIANCE_H
#define RADIANCE_H

#include "maptypes.h"

class RadianceMap: public SphereMap
{
public:
    Pixel getPixel(double p, double t) const override;
    void setPixel(double p, double t, Pixel v) override;
};

#endif // RADIANCE_H
