#include "MapBuild.h"
//--------------------------------------------------------------
#include "../../Models/ItemValidities/AlphabeticExtentedItems.h"
#include "../../Models/ItemValidities/AlphabeticOnlyItems.h"
#include "../../Models/ItemValidities/RandomOnlyItems.h"
//------------------------------------------------------
#include "../../Models/MapObjects/Items/TeleportItem.h"
#include "../../Models/MapObjects/Items/RandomItem.h"
#include "../../Models/MapObjects/Items/TrollItem.h"
#include "../../Models/MapObjects/Items/TimyItem.h"
//-------------------------------------------------
#include <Source/RandomGenerator.h>

namespace MapDimensions
{
    namespace AlphabeticDimensions
    {
        static const Dimension s_AzbukiDimensions = { 48, 28 };
        static const Dimension s_XidiomasDimensions = { 27, 15 };
        static const Dimension s_FAKTDimensions = { 49, 30 };
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
    Map map(AlphabeticDimensions::s_AzbukiDimensions, 26, make_polymorphic<AlphabeticExtentedItems>());

    map.setPlayer({ 24, 15 });

    #include "ObsticlesBuilds/AzbukiObsticles.txt"

    bool randomChoice = RandomGenerator::generateNext(2);

    if (randomChoice)
    {
        map.addItem(make_polymorphic<Item>(21, 20, 'a', 0, 'a' - 'a'));
        map.addItem(make_polymorphic<TrollItem>(21, 16, 'a', 24, 15));
    }
    else
    {
        map.addItem(make_polymorphic<TrollItem>(21, 20, 'a', 24, 15));
        map.addItem(make_polymorphic<Item>(21, 16, 'a', 0, 'a' - 'a'));
    }

    map.addItem(make_polymorphic<Item>(1, 1, 'z' , 'z' - 'a', 5));
    map.addItem(make_polymorphic<Item>(14, 2, 'b', 'b' - 'a', 4));
    map.addItem(make_polymorphic<Item>(22, 4, 'u', 'u' - 'a', 4));
    map.addItem(make_polymorphic<Item>(28, 4, 'k', 'k' - 'a', 4));
    map.addItem(make_polymorphic<Item>(34, 4, 'i', 'i' - 'a', 7));

    map.addItem(make_polymorphic<TeleportItem>(41, 3, 23, 18));

    map.addItem(make_polymorphic<Item>(36, 9, 'c', 'c' - 'a', 5));
    map.addItem(make_polymorphic<Item>(44, 7, 'd', 'd' - 'a', 10));
    map.addItem(make_polymorphic<Item>(39, 9, 'e', 'e' - 'a', 12));

    map.addItem(make_polymorphic<Item>(43, 24, 'f', 'f' - 'a', 3));
    map.addItem(make_polymorphic<Item>(11, 19, 'g', 'g' - 'a', 11));
    map.addItem(make_polymorphic<Item>(6, 13, 'h', 'h' - 'a', 15));
    map.addItem(make_polymorphic<Item>(12, 13, 'j', 'j' - 'a', 7));
    map.addItem(make_polymorphic<Item>(5, 17, 'l', 'l' - 'a', 10));

    map.addItem(make_polymorphic<Item>(7, 10, 'm', 'm' - 'a', 5));
    map.addItem(make_polymorphic<Item>(14, 10, 'n', 'n' - 'a', 5));
    map.addItem(make_polymorphic<Item>(41, 13, 'o', 'o' - 'a', 7));
    map.addItem(make_polymorphic<Item>(43, 16, 'p', 'p' - 'a', 11));

    map.addItem(make_polymorphic<Item>(43, 18, 's', 55, 2));
    map.addItem(make_polymorphic<TimyItem>(44, 19, 't', 95));
    map.addItem(make_polymorphic<Item>(6, 22, 'r', 'r' - 'a', 20));

    map.addItem(make_polymorphic<Item>(21, 25, 'v', 'v' - 'a', 21));
    map.addItem(make_polymorphic<Item>(33, 23, 'q', 'q' - 'a', 13));
    map.addItem(make_polymorphic<Item>(32, 18, 'y', 'y' - 'a', 7));
    map.addItem(make_polymorphic<Item>(37, 20, 'x', 'x' - 'a', 5));

    map.addItem(make_polymorphic<Item>(46, 5, 'w', 'w' - 'a', 5));

    return map;
}

Map AlphabeticBuild::buildXidiomas()
{
    Map map(AlphabeticDimensions::s_XidiomasDimensions, 7, make_polymorphic<AlphabeticExtentedItems>());

    map.setPlayer({ 13, 7 });

    #include "ObsticlesBuilds/XidiomasObsticles.txt"

    map.addItem(make_polymorphic<TeleportItem>(13, 8, 13, 13));
    map.addItem(make_polymorphic<TeleportItem>(12, 7, 1, 7));
    map.addItem(make_polymorphic<TeleportItem>(13, 6, 13, 1));
    map.addItem(make_polymorphic<TeleportItem>(14, 7, 25, 7));

    map.addItem(make_polymorphic<TeleportItem>(13, 10, 13, 7));
    map.addItem(make_polymorphic<TeleportItem>(8, 5, 13, 7));
    map.addItem(make_polymorphic<TeleportItem>(13, 3, 13, 7));
    map.addItem(make_polymorphic<TeleportItem>(18, 7, 13, 7));

    map.addItem(make_polymorphic<TeleportItem>(25, 4, 25, 2));
    map.addItem(make_polymorphic<TeleportItem>(25, 10, 25, 12));
    map.addItem(make_polymorphic<TeleportItem>(22, 3, 21, 4));
    map.addItem(make_polymorphic<TeleportItem>(22, 11, 21, 10));

    map.addItem(make_polymorphic<Item>(11, 5, 'x', 5, 6));
    map.addItem(make_polymorphic<Item>(15, 5, 'x', 7, 6));
    map.addItem(make_polymorphic<Item>(8, 1, 'x', 1,  6));
    map.addItem(make_polymorphic<Item>(18, 1, 'x', 4, 6));
    map.addItem(make_polymorphic<Item>(3, 1, 'x', 10, 6));
    map.addItem(make_polymorphic<Item>(23, 1, 'x', 10,6));

    map.addItem(make_polymorphic<Item>(23, 4, 'x', 15, 6));
    map.addItem(make_polymorphic<Item>(23, 10, 'x', 4, 6));
    map.addItem(make_polymorphic<Item>(17, 6, 'x', 12, 6));
    map.addItem(make_polymorphic<Item>(17, 8, 'x', 8, 6));

    map.addItem(make_polymorphic<Item>(4, 13, 'x', 18, 8));
    map.addItem(make_polymorphic<Item>(22, 13, 'x', 4, 8));
    map.addItem(make_polymorphic<Item>(9, 11, 'x', 12, 8));
    map.addItem(make_polymorphic<Item>(17, 11, 'x', 8, 8));

    map.addItem(make_polymorphic<Item>(1, 12, 'x', 12, 6));
    map.addItem(make_polymorphic<Item>(3, 9, 'x', 14, 7));
    map.addItem(make_polymorphic<Item>(5, 6, 'x', 12, 8));
    map.addItem(make_polymorphic<Item>(9, 8, 'x', 8, 12));
    map.addItem(make_polymorphic<Item>(2, 4, 'x', 10, 10));
    map.addItem(make_polymorphic<Item>(2, 2, 'x', 2, 14));

    return map;
}

Map AlphabeticBuild::buildFAKT()
{
    Map map(AlphabeticDimensions::s_FAKTDimensions, 69, make_polymorphic<AlphabeticExtentedItems>());

    map.setPlayer({ 24, 1 });

    #include "ObsticlesBuilds/FAKTObsticles.txt"

    map.addItem(make_polymorphic<Item>(24, 4, 'x', 2, 14));


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
    Map map(ImposterDimensions::s_BAKDimensions, 27, make_polymorphic<AcceptAllItems>());

    map.setPlayer({ 1,2 });

    map.addItem(make_polymorphic<Item>(3, 3, 'z', 12, 30));
    map.addItem(make_polymorphic<Item>(5, 12, 'a', 13, 21));
    map.addItem(make_polymorphic<TeleportItem>(11, 12, 13, 16));
    map.addItem(make_polymorphic<TrollItem>(17, 19, '@', 5, 5));
    map.addItem(make_polymorphic<TimyItem>(22, 20, 't', 252));
    map.addItem(make_polymorphic<RandomItem>(10, 20, 200, 20));

    return map;
}
