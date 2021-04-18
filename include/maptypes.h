#ifndef SPHEREMAP_H
#define SPHEREMAP_H

struct Pixel
{
    float r, g, b;
};

struct Size
{
    int width, height;
};

class Map
{
public:
    virtual ~Map();

    virtual Size size() const = 0;
};

class SphereMap: public Map
{
public:
    virtual Pixel getPixel(double p, double t) const = 0;
    virtual void setPixel(double p, double t, Pixel px) = 0;
};

class CubeMap: public Map
{
public:
    enum class Side
    {
        pX = 0, nX, pY, nY, pZ, nZ
    };

    static const Side SIDES[6];

    virtual Pixel getPixel(Side s, int x, int y) const = 0;
    virtual void setPixel(Side s, int x, int y, Pixel px) = 0;

    // Set this cubemap's sides as projection from surrounding spheremap
    void setProjection(const SphereMap &src);
};

#endif // SPHEREMAP_H
