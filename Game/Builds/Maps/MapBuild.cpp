#include "MapBuild.h"
//-----------------------
#include "../../Models/ItemValidities/AlphabeticOnlyItems.h"
#include "../../Models/ItemValidities/RandomOnlyItems.h"
#include "../../Models/MapObjects/Items/TeleportItem.h"

namespace MapDimensions
{
    namespace AlphabeticDimensions
    {
        static const Dimension s_AzbukiDimensions = { 48, 28 };
        static const Dimension s_XidiomasDimensions = { 34, 20 };
        static const Dimension s_FAKTDimensions = { 58, 30 };
    }

    namespace RandomizerDimensions
    {
        static const Dimension s_ThePitDimensions = { 56, 28 };
        static const Dimension s_BlocksmcDimensions = { 30, 15 };
    }

    namespace ImposterDimensions
    {
        static const Dimension s_DOOMzDimensions = { 44, 27 };
        static const Dimension s_BAKDimensions = { 33, 28 };
    }
}

using namespace MapDimensions;

Map AlphabeticBuild::buildAzbuki()
{
    Map map(AlphabeticDimensions::s_AzbukiDimensions, 100, make_polymorphic<AlphabeticOnlyItems>());

    map.setPlayer({ 24, 13 });

    #include "ObsticlesBuilds/AzbukiObsticles.txt"

    map.addItem(make_polymorphic<Item>(24, 10, 'z', 5, 10));
    map.addItem(make_polymorphic<Item>(23, 10, 'a', 7, 10));

    return map;
}

Map AlphabeticBuild::buildXidiomas()
{
    Map map(AlphabeticDimensions::s_XidiomasDimensions, 7, make_polymorphic<AlphabeticOnlyItems>());

    return map;
}

Map AlphabeticBuild::buildFAKT()
{
    Map map(AlphabeticDimensions::s_FAKTDimensions, 7, make_polymorphic<AlphabeticOnlyItems>());

    return map;
}

Map RandomizerBuild::buildThePit()
{
    Map map(RandomizerDimensions::s_ThePitDimensions, 7, make_polymorphic<RandomOnlyItems>());

    return map;
}

Map RandomizerBuild::buildBlocksmc()
{
    Map map(RandomizerDimensions::s_BlocksmcDimensions, 7, make_polymorphic<RandomOnlyItems>());

    return map;
}

Map ImposterBuild::buildDOOMz()
{
    Map map(ImposterDimensions::s_DOOMzDimensions, 7, make_polymorphic<AcceptAllItems>());

    return map;
}

Map ImposterBuild::buildBAK()
{
    Map map(ImposterDimensions::s_BAKDimensions, 7, make_polymorphic<AcceptAllItems>());

    map.setPlayer({ 1,2 });

    map.addItem(make_polymorphic<Item>(3, 3, 'z', 12, 12));
    map.addItem(make_polymorphic<Item>(5, 12, 'a', 13, 13));
    map.addItem(make_polymorphic<TeleportItem>(11, 12, 13, 12, 14));

    return map;
}
