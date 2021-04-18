#ifndef RADIANCE_H
#define RADIANCE_H

#include "maptypes.h"
#include <istream>
#include <memory>

class RadianceMap: public SphereMap
{
    Size m_size = { 0, 0 };
    std::unique_ptr<char[]> m_data;

public:

    // Load from HDR (Radiance) file
    void load(std::istream &fin);

    Pixel getPixel(double p, double t) const override;
    void setPixel(double p, double t, Pixel v) override;

    Size size() const override
    {
        return m_size;
    }
};

#endif // RADIANCE_H
