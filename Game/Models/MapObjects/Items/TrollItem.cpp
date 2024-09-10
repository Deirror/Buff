#include "TrollItem.h"

TrollItem::TrollItem(Coord coords, Coord teleportCoords)
    : TeleportItem(coords, teleportCoords)
{
}

TrollItem::TrollItem(uint8_t x, uint8_t y, uint8_t teleportX, uint8_t teleportY)
    : TeleportItem(x, y, teleportX, teleportY)
{
}

void TrollItem::modifyPoints(uint16_t& points) const
{
    points = m_Points;
}

Item* TrollItem::clone() const
{
    return new TrollItem(*this);
}
