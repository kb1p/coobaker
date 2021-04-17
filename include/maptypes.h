#ifndef SPHEREMAP_H
#define SPHEREMAP_H

struct Pixel
{
    float r, g, b;
};

class SphereMap
{
public:
    virtual ~SphereMap();

    virtual Pixel getPixel(double p, double t) const = 0;
    virtual void setPixel(double p, double t, Pixel px) = 0;
};

class CubeMap
{
public:
    enum class Side
    {
        pX = 0, nX, pY, nY, pZ, nZ
    };

    static const Side SIDES[6];

    virtual ~CubeMap();

    virtual Pixel getPixel(Side s, int x, int y) const = 0;
    virtual void setPixel(Side s, int x, int y, Pixel px) = 0;

    void setProjection(const SphereMap &src);
};

#endif // SPHEREMAP_H
