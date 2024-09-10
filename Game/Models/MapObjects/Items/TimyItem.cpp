#include "TimyItem.h"
//---------------------------------
#include <Source/RandomGenerator.h>

#define UPPER_BOUND 3

TimyItem::TimyItem(uint8_t x, uint8_t y, uint8_t symbol, uint8_t seconds)
    : Item(x,y,symbol, RandomGenerator::generateNext(UPPER_BOUND), seconds)
{
}

TimyItem::TimyItem(Coord coords, uint8_t symbol, uint8_t seconds)
    : Item(coords, symbol, RandomGenerator::generateNext(UPPER_BOUND), seconds)
{
}

Item* TimyItem::clone() const
{
    return new TimyItem(*this);
}
