#pragma once
#include "../MapEntity.h"

class Item : public MapEntity
{
public:
	Item(uint8_t x, uint8_t y, uint8_t symbol, uint8_t points, uint8_t seconds);
	Item(Coord coords, uint8_t symbol, uint8_t points, uint8_t seconds);

	virtual void modifyPoints(uint16_t& points) const;
	virtual void modifySeconds(uint8_t& seconds) const;

	virtual Item* clone() const;
	virtual ~Item() = default;

protected:
	uint8_t m_Points = 0;
	uint8_t m_Seconds = 0;
};

//classes TrollItem..