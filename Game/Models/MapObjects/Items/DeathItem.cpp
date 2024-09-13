#include "DeathItem.h"

DeathItem::DeathItem(uint8_t x, uint8_t y, uint8_t symbol)
	:Item(x,y,symbol,0,0)
{
	m_Collectable = false;
}

DeathItem::DeathItem(Coord coords, uint8_t symbol)
	:Item(coords, symbol, 0, 0)
{
	m_Collectable = false;
}

Item* DeathItem::clone() const
{
	return new DeathItem(*this);
}
