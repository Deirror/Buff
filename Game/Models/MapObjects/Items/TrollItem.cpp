#include "TrollItem.h"

TrollItem::TrollItem(Coord coords, uint8_t symbol, Coord teleportCoords)
    : TeleportItem(coords, teleportCoords)
{
    m_Collectable = false;
    m_Symbol = symbol;
}

TrollItem::TrollItem(uint8_t x, uint8_t y, uint8_t symbol, uint8_t teleportX, uint8_t teleportY)
    : TeleportItem(x, y, teleportX, teleportY)
{
    m_Collectable = false;
    m_Symbol = symbol;
}

void TrollItem::modifyPoints(uint16_t& points) const
{
    points = m_Points;
}

Item* TrollItem::clone() const
{
    return new TrollItem(*this);
}
