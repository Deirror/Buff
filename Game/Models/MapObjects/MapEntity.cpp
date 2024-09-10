#include "MapEntity.h"

MapEntity::MapEntity(uint8_t symbol) : m_Symbol(symbol)
{
}

MapEntity::MapEntity(Coord coords) : m_Coords(coords)
{
}

MapEntity::MapEntity(Coord coords, uint8_t symbol) : m_Coords(coords), m_Symbol(symbol)
{
}

void MapEntity::setCoords(Coord coords)
{
	m_Coords = coords;
}

void MapEntity::setSymbol(uint8_t symbol)
{
	m_Symbol = symbol;
}

Coord MapEntity::getCoords() const
{
	return m_Coords;
}

uint8_t MapEntity::getSymbol() const
{
	return m_Symbol;
}
