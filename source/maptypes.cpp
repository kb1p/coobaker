#include "maptypes.h"

const CubeMap::Side CubeMap::SIDES[6] = {
    Side::pX, Side::nX, Side::pY, Side::nY, Side::pZ, Side::nZ
};

SphereMap::~SphereMap()
{

}

CubeMap::~CubeMap()
{

}

void CubeMap::setProjection(const SphereMap &src)
{

}
