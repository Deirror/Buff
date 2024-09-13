#include "NullItem.h"

NullItem::NullItem(uint8_t x, uint8_t y, uint8_t symbol, bool collectable)
	: Item(x, y, symbol, 0, 0)
{
	m_Collectable = collectable;
}

NullItem::NullItem(Coord coords, uint8_t symbol, bool collectable)
	: Item(coords, symbol, 0, 0)
{
	m_Collectable = collectable;
}

void NullItem::modifySeconds(uint8_t& seconds) const
{
	seconds += m_Seconds;
}

Item* NullItem::clone() const
{
	return new NullItem(*this);
}
