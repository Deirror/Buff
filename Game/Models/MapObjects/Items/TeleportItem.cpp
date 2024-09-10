#include "TeleportItem.h"
#include "../../../Builds/MapSymbols.h"

TeleportItem::TeleportItem(uint8_t x, uint8_t y,uint8_t seconds, uint8_t teleportX, uint8_t teleportY)
    : Item(x, y, MapSymbols::Objects::Items::ce_TeleportItem, 0, seconds), 
      m_TeleportCoords({ teleportX , teleportY })
{
}

TeleportItem::TeleportItem(Coord coords, uint8_t seconds, Coord teleportCoords)
    : Item(coords, MapSymbols::Objects::Items::ce_TeleportItem, 0, seconds), 
      m_TeleportCoords(teleportCoords)
{
}

Item* TeleportItem::clone() const
{
    return new TeleportItem(*this);
}

void TeleportItem::teleportPlayer(Coord& coords) const
{
    coords = m_TeleportCoords;
}
