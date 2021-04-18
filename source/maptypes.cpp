#include "maptypes.h"

#define _USE_MATH_DEFINES
#include <cmath>

Map::~Map()
{

}

const CubeMap::Side CubeMap::SIDES[6] = {
    Side::pX, Side::nX, Side::pY, Side::nY, Side::pZ, Side::nZ
};

void CubeMap::setProjection(const SphereMap &src)
{
    struct RayGuide
    {
        Side side;
        double startPhi, dirPhi;
        double startTheta, dirTheta;
    };

    // Mapping of cube sides to sphere surface.
    // - each side occupies (PI / 2) wide area;
    // - origin of sphere and cube is combined
    static const RayGuide SPHERE2CUBE[] = {
        { Side::pX, 0, 1, M_PI_4, 1 },
        { Side::nX, 0, 1, -M_PI_4, -1 },
        { Side::pY, M_PI_4, 1, M_PI_4, 1 },
        { Side::nY, -M_PI_4, -1, -M_PI_4, -1 },
        { Side::pZ, 0, 1, M_PI_4, -1 },
        { Side::nZ, 0, 1, M_PI_4 + M_PI_2, 1 }
    };

    const auto dim = size();
    const double stepx = M_PI_2 / dim.width,
                 stepy = M_PI_2 / dim.height;

    for (const auto sd: SPHERE2CUBE)
    {
        for (int y = 0; y <= dim.height; y++)
            for (int x = 0; x <= dim.width; x++)
            {
                const double p = sd.startPhi + x * stepx * sd.dirPhi,
                             t = sd.startTheta + y * stepy * sd.dirTheta;
                setPixel(sd.side, x, y, src.getPixel(p, t));
            }
    }
}
