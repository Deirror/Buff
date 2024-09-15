#include "MapFactory.h"
//------------------------
#include "Maps/MapBuild.h"
//---------------------------
#include <Source/addbutmcr.h>

namespace BuildFunction
{
    typedef Map(*buildFunction)();

    using namespace AlphabeticBuild;
    using namespace RandomizerBuild;
    using namespace TrainingBuild;

    static const Buffer2D<buildFunction, 3, 3> mapBuildCaller = { {buildAzbuki, buildXidiomas, buildFAKT},
                                                                  {buildThePit, buildBlocksmc},
                                                                  {buildDOOMz, buildBAK}, };
}

Map createMap(uint8_t mapVariant, uint8_t mapBuild)
{
    return BuildFunction::mapBuildCaller[TO_INDEX(mapVariant)][TO_INDEX(mapBuild)]();
}