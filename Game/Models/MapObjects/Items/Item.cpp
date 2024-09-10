#include "Item.h"

Item::Item(uint8_t x, uint8_t y, uint8_t symbol, uint8_t points, uint8_t seconds) 
	: MapEntity({x,y}, symbol), m_Points(points), m_Seconds(seconds)
{
}

Item::Item(Coord coords, uint8_t symbol, uint8_t points, uint8_t seconds)
	: MapEntity(coords, symbol), m_Points(points), m_Seconds(seconds)
{
}

bool Item::isCollectable() const
{
	return m_Collectable;
}

void Item::modifyPoints(uint16_t& points) const
{
	points += m_Points;
}

void Item::modifySeconds(uint8_t& seconds) const
{
	seconds = m_Seconds;
}

Item* Item::clone() const
{
	return new Item(*this);
}
