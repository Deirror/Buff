#include "TeleportItem.h"

TeleportItem::TeleportItem(uint8_t x, uint8_t y, uint8_t teleportX, uint8_t teleportY, uint8_t symbol)
    : Item(x, y, symbol, 0, 0),
      m_TeleportCoords({ teleportX , teleportY })
{
    m_Collectable = false;
}

TeleportItem::TeleportItem(Coord coords, Coord teleportCoords, uint8_t symbol)
    : Item(coords, symbol, 0, 0),
     m_TeleportCoords(teleportCoords)
{
    m_Collectable = false;
}

Item* TeleportItem::clone() const
{
    return new TeleportItem(*this);
}

void TeleportItem::modifySeconds(uint8_t& seconds) const
{
    seconds += m_Seconds;
}

void TeleportItem::teleportPlayer(Coord& coords) const
{
    coords = m_TeleportCoords;
}
