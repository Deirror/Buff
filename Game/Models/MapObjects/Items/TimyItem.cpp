#include "TimyItem.h"
//---------------------------------
#include <Source/RandomGenerator.h>

#define UPPER_BOUND 3

TimyItem::TimyItem(uint8_t x, uint8_t y, uint8_t symbol, uint8_t seconds, bool collectable)
    : Item(x,y,symbol, RandomGenerator::generateNext(UPPER_BOUND), seconds)
{
    m_Collectable = collectable;
}

TimyItem::TimyItem(Coord coords, uint8_t symbol, uint8_t seconds, bool collectable)
    : Item(coords, symbol, RandomGenerator::generateNext(UPPER_BOUND), seconds)
{
    m_Collectable = collectable;
}

Item* TimyItem::clone() const
{
    return new TimyItem(*this);
}
