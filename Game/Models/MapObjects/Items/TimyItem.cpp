#include "TimyItem.h"

TimyItem::TimyItem(uint8_t x, uint8_t y, uint8_t symbol, uint8_t seconds)
    : Item(x,y,symbol, 0, seconds)
{
}

TimyItem::TimyItem(Coord coords, uint8_t symbol, uint8_t seconds)
    : Item(coords, symbol, 0, seconds)
{
}

Item* TimyItem::clone() const
{
    return new TimyItem(*this);
}
