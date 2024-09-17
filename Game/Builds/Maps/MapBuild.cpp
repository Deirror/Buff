#include "MapBuild.h"
//--------------------------------------------------------------
#include "../../Models/ItemValidities/AlphabeticExtentedItems.h"
#include "../../Models/ItemValidities/RandomExtendedItems.h"
#include "../../Models/ItemValidities/AlphabeticOnlyItems.h"
#include "../../Models/ItemValidities/RandomOnlyItems.h"
//------------------------------------------------------
#include "../../Models/MapObjects/Items/TeleportItem.h"
#include "../../Models/MapObjects/Items/RandomItem.h"
#include "../../Models/MapObjects/Items/TrollItem.h"
#include "../../Models/MapObjects/Items/DeathItem.h"
#include "../../Models/MapObjects/Items/TimyItem.h"
#include "../../Models/MapObjects/Items/NullItem.h"
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
        static const Dimension s_ThePitDimensions = { 37, 28 };
        static const Dimension s_BlocksmcDimensions = { 31, 15 };
    }

    namespace ImposterDimensions
    {
        static const Dimension s_DOOMzDimensions = { 45, 27 };
        static const Dimension s_BAKDimensions = { 27, 28 };
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
    Map map(AlphabeticDimensions::s_FAKTDimensions, 23, make_polymorphic<AlphabeticExtentedItems>());

    map.setPlayer({ 24, 1 });

    #include "ObsticlesBuilds/FAKTObsticles.txt"

    const char deathSymbol = ' ';

    map.addItem(make_polymorphic<NullItem>(43, 24, 'A', false));
    map.addItem(make_polymorphic<NullItem>(44, 24, 'n', false));
    map.addItem(make_polymorphic<NullItem>(45, 24, 'd', false));
    map.addItem(make_polymorphic<NullItem>(46, 24, 'i', false));

    map.addItem(make_polymorphic<Item>(47, 20, 'F', 15, 15));
    map.addItem(make_polymorphic<DeathItem>(44, 20, deathSymbol));
    map.addItem(make_polymorphic<DeathItem>(44, 21, deathSymbol));

    map.addItem(make_polymorphic<NullItem>(42, 21, 'C', false));

    map.addItem(make_polymorphic<DeathItem>(47, 22, deathSymbol));
    map.addItem(make_polymorphic<DeathItem>(43, 23, deathSymbol));

    map.addItem(make_polymorphic<DeathItem>(47, 24, deathSymbol));
    map.addItem(make_polymorphic<DeathItem>(46, 23, deathSymbol));

    map.addItem(make_polymorphic<NullItem>(47, 27, 'l', false));
    map.addItem(make_polymorphic<NullItem>(46, 27, 'o', false));
    map.addItem(make_polymorphic<NullItem>(45, 27, 't', false));
    map.addItem(make_polymorphic<NullItem>(44, 27, 's', false));

    map.addItem(make_polymorphic<DeathItem>(37, 21, deathSymbol));
    map.addItem(make_polymorphic<DeathItem>(36, 21, deathSymbol));
    map.addItem(make_polymorphic<DeathItem>(35, 21, deathSymbol));
    map.addItem(make_polymorphic<DeathItem>(34, 21, deathSymbol));
    map.addItem(make_polymorphic<DeathItem>(33, 21, deathSymbol));
    map.addItem(make_polymorphic<DeathItem>(31, 21, deathSymbol));

    map.addItem(make_polymorphic<DeathItem>(33, 22, deathSymbol));

    map.addItem(make_polymorphic<DeathItem>(31, 20, deathSymbol));
    map.addItem(make_polymorphic<DeathItem>(33, 23, deathSymbol));
    map.addItem(make_polymorphic<DeathItem>(32, 23, deathSymbol));
    map.addItem(make_polymorphic<DeathItem>(34, 23, deathSymbol));
    map.addItem(make_polymorphic<DeathItem>(35, 23, deathSymbol));
    map.addItem(make_polymorphic<DeathItem>(36, 23, deathSymbol));

    map.addItem(make_polymorphic<DeathItem>(38, 23, deathSymbol));
    map.addItem(make_polymorphic<DeathItem>(39, 23, deathSymbol));
    map.addItem(make_polymorphic<DeathItem>(39, 22, deathSymbol));
    map.addItem(make_polymorphic<TimyItem>(39, 20, 'T', 255));
    map.addItem(make_polymorphic<TrollItem>(35, 22, 'T', 42, 3));

    map.addItem(make_polymorphic<NullItem>(2, 28, 'B', false));
    map.addItem(make_polymorphic<NullItem>(3, 28, 'I', false));
    map.addItem(make_polymorphic<NullItem>(4, 28, 'L', false));
    map.addItem(make_polymorphic<NullItem>(5, 28, 'L', false));
    map.addItem(make_polymorphic<NullItem>(6, 28, 'A', false));

    map.addItem(make_polymorphic<DeathItem>(5, 27, deathSymbol));

    map.addItem(make_polymorphic<Item>(4, 26, 'A', 44, 44));

    map.addItem(make_polymorphic<DeathItem>(1, 23, deathSymbol));
    map.addItem(make_polymorphic<TeleportItem>(4, 24, 2, 6));
    map.addItem(make_polymorphic<TeleportItem>(3, 6, 24, 1));
    map.addItem(make_polymorphic<Item>(1, 6, ' ', 20, 44));

    map.addItem(make_polymorphic<TeleportItem>(35, 8, 40, 2));
    map.addItem(make_polymorphic<TeleportItem>(40, 3, 24, 1));
    map.addItem(make_polymorphic<Item>(41, 1, 'K', 32, 50));
    map.addItem(make_polymorphic<DeathItem>(42, 1, deathSymbol));

    map.addItem(make_polymorphic<NullItem>(10, 24, 'd', false));
    map.addItem(make_polymorphic<NullItem>(11, 24, 'o', false));
    map.addItem(make_polymorphic<NullItem>(12, 24, 'n', false));
    map.addItem(make_polymorphic<NullItem>(13, 24, 't', false));

    map.addItem(make_polymorphic<NullItem>(10, 21, 'k', false));
    map.addItem(make_polymorphic<NullItem>(11, 21, 'n', false));
    map.addItem(make_polymorphic<NullItem>(12, 21, 'o', false));
    map.addItem(make_polymorphic<NullItem>(13, 21, 'w', false));

    map.addItem(make_polymorphic<NullItem>(16, 23, 'y', false));
    map.addItem(make_polymorphic<NullItem>(16, 22, 'e', false));
    map.addItem(make_polymorphic<NullItem>(16, 21, 't', false));

    map.addItem(make_polymorphic<DeathItem>(1, 18, deathSymbol));
    map.addItem(make_polymorphic<DeathItem>(2, 18, deathSymbol));
    map.addItem(make_polymorphic<NullItem>(1, 17, 'o', false));
    map.addItem(make_polymorphic<NullItem>(2, 17, 'o', false));
    map.addItem(make_polymorphic<NullItem>(3, 17, 'p', false));

    map.addItem(make_polymorphic<NullItem>(1, 16, 't', false));
    map.addItem(make_polymorphic<NullItem>(2, 16, 'e', false));
    map.addItem(make_polymorphic<NullItem>(3, 16, 'o', false));
    map.addItem(make_polymorphic<DeathItem>(4, 16, deathSymbol));
    map.addItem(make_polymorphic<DeathItem>(5, 16, deathSymbol));

    map.addItem(make_polymorphic<DeathItem>(26, 23, deathSymbol));
    map.addItem(make_polymorphic<NullItem>(8, 12, 'n', false));
    map.addItem(make_polymorphic<NullItem>(8, 11, 'z', false));

    map.addItem(make_polymorphic<DeathItem>(3, 9, deathSymbol));
    map.addItem(make_polymorphic<Item>(1, 9, ' ', 5, 20));
    map.addItem(make_polymorphic<Item>(9, 14, ' ', 4, 20));

    map.addItem(make_polymorphic<NullItem>(13, 13, 'h', false));
    map.addItem(make_polymorphic<NullItem>(13, 12, 'r', false));
    map.addItem(make_polymorphic<NullItem>(13, 11, 'a', false));
    map.addItem(make_polymorphic<NullItem>(15, 10, 'n', false));
    map.addItem(make_polymorphic<NullItem>(15, 9, 'a', false));

    map.addItem(make_polymorphic<Item>(11, 10, ' ', 2, 10));
    map.addItem(make_polymorphic<Item>(12, 10, ' ', 1, 20));
    map.addItem(make_polymorphic<Item>(11, 11, ' ', 2, 20));

    map.addItem(make_polymorphic<NullItem>(16, 17, 'r', false));
    map.addItem(make_polymorphic<NullItem>(21, 16, 'a', false));
    map.addItem(make_polymorphic<NullItem>(29, 18, 'n', false));
    map.addItem(make_polymorphic<NullItem>(34, 17, 'd', false));
    map.addItem(make_polymorphic<NullItem>(20, 14, 'o', false));
    map.addItem(make_polymorphic<NullItem>(28, 14, 'm', false));

    map.addItem(make_polymorphic<NullItem>(22, 12, 'h', false));
    map.addItem(make_polymorphic<NullItem>(25, 11, 'o', false));
    map.addItem(make_polymorphic<NullItem>(28, 12, 'r', false));
    map.addItem(make_polymorphic<NullItem>(30, 11, 'a', false));

    map.addItem(make_polymorphic<TeleportItem>(41, 11, 37, 11, ' '));
    map.addItem(make_polymorphic<TeleportItem>(35, 11, 33, 11, ' '));

    map.addItem(make_polymorphic<Item>(36, 10, ' ', 12, 30));

    map.addItem(make_polymorphic<NullItem>(45, 6, 'F', false));
    map.addItem(make_polymorphic<NullItem>(46, 6, 'i', false));
    map.addItem(make_polymorphic<NullItem>(47, 6, 'z', false));

    map.addItem(make_polymorphic<NullItem>(18, 7, 'N', false));
    map.addItem(make_polymorphic<NullItem>(19, 7, 'i', false));
    map.addItem(make_polymorphic<NullItem>(20, 7, 'k', false));
    map.addItem(make_polymorphic<NullItem>(28, 7, 'o', false));
    map.addItem(make_polymorphic<NullItem>(29, 7, 'l', false));
    map.addItem(make_polymorphic<NullItem>(30, 7, 'a', false));

    map.addItem(make_polymorphic<NullItem>(2, 4, 'a', false));
    map.addItem(make_polymorphic<NullItem>(3, 4, 'r', false));
    map.addItem(make_polymorphic<NullItem>(4, 4, 'e', false));
    map.addItem(make_polymorphic<NullItem>(1, 3, 'g', false));
    map.addItem(make_polymorphic<NullItem>(2, 3, 'o', false));
    map.addItem(make_polymorphic<NullItem>(3, 3, 'h', false));
    map.addItem(make_polymorphic<NullItem>(4, 3, 'o', false));
    map.addItem(make_polymorphic<NullItem>(5, 3, 'm', false));
    map.addItem(make_polymorphic<NullItem>(6, 3, 'e', false));

    map.addItem(make_polymorphic<DeathItem>(37, 1, deathSymbol));
    map.addItem(make_polymorphic<Item>(47, 2, ' ', 10, 34));

    map.addItem(make_polymorphic<Item>(6, 1, ' ', 5, 20));
    map.addItem(make_polymorphic<Item>(8, 1, ' ', 5, 20));

    return map;
}

Map RandomizerBuild::buildThePit()
{
    Map map(RandomizerDimensions::s_ThePitDimensions, 15, make_polymorphic<RandomOnlyItems>());

    map.setPlayer({ 18, 26 });

    #include "ObsticlesBuilds/ThePitObsticles.txt"

    map.addItem(make_polymorphic<RandomItem>(17, 23, 6, 10));
    map.addItem(make_polymorphic<RandomItem>(21, 22, 5, 4));
    map.addItem(make_polymorphic<RandomItem>(19, 21, 1, 3));

    map.addItem(make_polymorphic<RandomItem>(14, 17, 1, 4));
    map.addItem(make_polymorphic<RandomItem>(22, 17, 10, 5));
    map.addItem(make_polymorphic<RandomItem>(18, 18, 5, 3));

    map.addItem(make_polymorphic<RandomItem>(18, 14, 1, 4));
    map.addItem(make_polymorphic<RandomItem>(15, 10, 3, 4));
    map.addItem(make_polymorphic<RandomItem>(21, 12, 5, 3));

    map.addItem(make_polymorphic<RandomItem>(18, 5, 10, 19, 5, 10));

    map.addItem(make_polymorphic<RandomItem>(4, 21, 10, 30, 5, 10));
    map.addItem(make_polymorphic<RandomItem>(1, 16, 5, 14, 8, 10));
    map.addItem(make_polymorphic<RandomItem>(9, 10, 16, 30, 15, 30));
    map.addItem(make_polymorphic<RandomItem>(9, 23, 10, 20, 15, 30));

    map.addItem(make_polymorphic<RandomItem>(8, 13, 17, 20, 15, 30));
    map.addItem(make_polymorphic<RandomItem>(2, 10, 13, 20, 23, 30));
    map.addItem(make_polymorphic<RandomItem>(7, 6, 20, 30,  15, 20));
    map.addItem(make_polymorphic<RandomItem>(3, 3, 10, 20, 15, 30));

    map.addItem(make_polymorphic<RandomItem>(5, 6, 17, 20, 20, 24));
    map.addItem(make_polymorphic<RandomItem>(1, 8, 10, 13, 8, 16));
    map.addItem(make_polymorphic<RandomItem>(14, 1, 2, 20, 15, 30));
    map.addItem(make_polymorphic<RandomItem>(26, 1, 6, 20, 12, 30));

    map.addItem(make_polymorphic<RandomItem>(27, 4, 6, 20, 12, 20));
    map.addItem(make_polymorphic<RandomItem>(26, 8, 6, 20, 12, 20));

    map.addItem(make_polymorphic<RandomItem>(34, 2, 6, 20, 12, 20));
    map.addItem(make_polymorphic<RandomItem>(34, 7, 6, 20, 12, 20));
    map.addItem(make_polymorphic<RandomItem>(28, 8, 6, 20, 12, 20));

    map.addItem(make_polymorphic<RandomItem>(33, 10, 6, 20, 9, 15));
    map.addItem(make_polymorphic<RandomItem>(35, 14, 6, 20, 12, 20));
    map.addItem(make_polymorphic<RandomItem>(27, 14, 6, 20, 12, 20));
    map.addItem(make_polymorphic<RandomItem>(27, 21, 6, 20, 12, 20));

    map.addItem(make_polymorphic<RandomItem>(34, 23, 6, 20, 12, 20));
    map.addItem(make_polymorphic<RandomItem>(34, 17, 6, 20, 12, 20));

    return map;
}

Map RandomizerBuild::buildBlocksmc()
{
    Map map(RandomizerDimensions::s_BlocksmcDimensions, 20, make_polymorphic<RandomExtendedItems>());

    map.setPlayer({ 1, 1 });

    #include "ObsticlesBuilds/BlocksmcObsticles.txt"

    map.addItem(make_polymorphic<TeleportItem>(29, 13, 3, 3));
    map.addItem(make_polymorphic<TeleportItem>(27, 11, 5, 5));

    map.addItem(make_polymorphic<RandomItem>(6, 8, 255, 3));
    map.addItem(make_polymorphic<RandomItem>(7, 9, 255, 3));
    map.addItem(make_polymorphic<RandomItem>(8, 9, 255, 3));
    map.addItem(make_polymorphic<RandomItem>(9, 9, 255, 3));
    map.addItem(make_polymorphic<RandomItem>(10, 8, 255, 3));
    map.addItem(make_polymorphic<RandomItem>(9, 7, 255, 3));
    map.addItem(make_polymorphic<RandomItem>(8, 6, 255, 3));
    map.addItem(make_polymorphic<RandomItem>(8, 5, 255, 3));

    map.addItem(make_polymorphic<RandomItem>(13, 8, 255, 3));
    map.addItem(make_polymorphic<RandomItem>(14, 9, 255, 3));
    map.addItem(make_polymorphic<RandomItem>(15, 9, 255, 3));
    map.addItem(make_polymorphic<RandomItem>(16, 9, 255, 3));
    map.addItem(make_polymorphic<RandomItem>(17, 8, 255, 3));
    map.addItem(make_polymorphic<RandomItem>(16, 7, 255, 3));
    map.addItem(make_polymorphic<RandomItem>(15, 6, 255, 3));
    map.addItem(make_polymorphic<RandomItem>(15, 5, 255, 3));

    map.addItem(make_polymorphic<RandomItem>(20, 8, 255, 3));
    map.addItem(make_polymorphic<RandomItem>(21, 9, 255, 3));
    map.addItem(make_polymorphic<RandomItem>(22, 9, 255, 3));
    map.addItem(make_polymorphic<RandomItem>(23, 9, 255, 3));
    map.addItem(make_polymorphic<RandomItem>(24, 8, 255, 3));
    map.addItem(make_polymorphic<RandomItem>(23, 7, 255, 3));
    map.addItem(make_polymorphic<RandomItem>(22, 6, 255, 3));
    map.addItem(make_polymorphic<RandomItem>(22, 5, 255, 3));

    return map;
}

Map ImposterBuild::buildDOOMz()
{
    Map map(ImposterDimensions::s_DOOMzDimensions, 195, make_polymorphic<AcceptAllItems>());

    map.setPlayer({22, 3});

    #include "ObsticlesBuilds/DOOMzObsticles.txt"

    map.addItem(make_polymorphic<NullItem>(19, 3,'o', false));
    map.addItem(make_polymorphic<NullItem>(25, 3, 'o', false));

    map.addItem(make_polymorphic<TeleportItem>(13, 2, 10, 5));
    map.addItem(make_polymorphic<TeleportItem>(10, 2, 7, 5));
    map.addItem(make_polymorphic<TeleportItem>(7, 2, 4, 5));
    map.addItem(make_polymorphic<TeleportItem>(4, 2, 18, 10));
    map.addItem(make_polymorphic<TeleportItem>(18, 14, 4, 9));
    map.addItem(make_polymorphic<TeleportItem>(18, 12, 17, 16));
    map.addItem(make_polymorphic<TeleportItem>(3, 13, 22, 3));

    map.addItem(make_polymorphic<TeleportItem>(31, 2, 34, 5));
    map.addItem(make_polymorphic<TeleportItem>(34, 2, 37, 5));
    map.addItem(make_polymorphic<TeleportItem>(37, 2, 40, 5));
    map.addItem(make_polymorphic<TeleportItem>(40, 2, 26, 10));
    map.addItem(make_polymorphic<TeleportItem>(26, 14, 40, 9));
    map.addItem(make_polymorphic<TeleportItem>(26, 12, 27, 16));
    map.addItem(make_polymorphic<TeleportItem>(41, 13, 22, 3));

    uint8_t randomChoice = RandomGenerator::generateNext(10) + 1;

    switch (randomChoice)
    {
    case 1:
    {
        map.addItem(make_polymorphic<TeleportItem>(2, 12, 22, 11, ' '));
        break;
    }
    case 2:
    {
        map.addItem(make_polymorphic<TeleportItem>(42, 11, 22, 11, ' '));
        break;
    }
    case 3:
    {
        map.addItem(make_polymorphic<TeleportItem>(33, 7, 22, 11, ' '));
        break;
    }
    case 4:
    {
        map.addItem(make_polymorphic<TeleportItem>(42, 4, 22, 11, ' '));
        break;
    }
    case 5:
    {
        map.addItem(make_polymorphic<TeleportItem>(10, 4, 22, 11, ' '));
        break;
    }
    case 6:
    {
        map.addItem(make_polymorphic<TeleportItem>(27, 5, 22, 11, ' '));
        break;
    }
    case 7:
    {
        map.addItem(make_polymorphic<TeleportItem>(9, 20, 22, 11, ' '));
        break;
    }
    case 8:
    {
        map.addItem(make_polymorphic<TeleportItem>(42, 24, 22, 11, ' '));
        break;
    }
    case 9:
    {
        map.addItem(make_polymorphic<TeleportItem>(29, 19, 22, 11, ' '));
        break;
    }
    case 10:
    {
        map.addItem(make_polymorphic<TeleportItem>(3, 17, 22, 11, ' '));
        break;
    }
    }

    map.addItem(make_polymorphic<RandomItem>(22, 10, 255, 3));

    return map;
}

Map ImposterBuild::buildBAK()
{
    Map map(ImposterDimensions::s_BAKDimensions, 60, make_polymorphic<AcceptAllItems>());

    Coord playerCoords = { 13,3 };

    map.setPlayer(playerCoords);

    #include "ObsticlesBuilds/BAKObsticles.txt"

    uint8_t times = RandomGenerator::generateValidNext(10, 15);
    uint8_t itemChoice = RandomGenerator::generateNext(times);

    for (uint8_t iter = 0; iter < times; iter++)
    {
        MapSymbolType mapSymbolType = MapSymbolType::Unknown;
        Coord mapCoords;

        do
        {
            uint8_t x = RandomGenerator::generateValidNext(1, ImposterDimensions::s_BAKDimensions.Width - 2);
            uint8_t y = RandomGenerator::generateValidNext(1, ImposterDimensions::s_BAKDimensions.Height - 2);
            mapCoords = { x, y };

            mapSymbolType = map.whatMapEntityIs(mapCoords);
        } while (mapSymbolType != MapSymbolType::WhiteSpace);

        if (itemChoice == iter)
        {
            map.addItem(make_polymorphic<Item>(mapCoords, '$', 1, 1));
            continue;
        }

        map.addItem(make_polymorphic<TrollItem>(mapCoords, '$', playerCoords));
    }

    times = RandomGenerator::generateValidNext(5, 10);

    for (uint8_t iter = 0; iter < times; iter++)
    {
        MapSymbolType mapSymbolType = MapSymbolType::Unknown;
        Coord mapCoords;

        do
        {
            uint8_t x = RandomGenerator::generateValidNext(1, ImposterDimensions::s_BAKDimensions.Width - 2);
            uint8_t y = RandomGenerator::generateValidNext(1, ImposterDimensions::s_BAKDimensions.Height - 2);
            mapCoords = { x, y };

            mapSymbolType = map.whatMapEntityIs(mapCoords);
        } while (mapSymbolType != MapSymbolType::WhiteSpace);

        map.addItem(make_polymorphic<DeathItem>(mapCoords, ' '));
    }

    return map;
}