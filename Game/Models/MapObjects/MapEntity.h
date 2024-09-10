#pragma once
#include <Models/Coord.h>
//-----------------------
#include <stdint.h>

class MapEntity
{
public:
	MapEntity() = default;
	MapEntity(uint8_t symbol);
	MapEntity(Coord coords);
	MapEntity(Coord coords, uint8_t symbol);

	void setCoords(Coord coords);
	void setSymbol(uint8_t symbol);

	Coord   getCoords() const;
	uint8_t getSymbol() const;

protected:
	Coord   m_Coords;
	uint8_t m_Symbol = 0;
};