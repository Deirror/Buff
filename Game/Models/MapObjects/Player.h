#pragma once
#include "MapEntity.h"

class Player : public MapEntity
{
public:
	Player();
	Player(uint8_t x, uint8_t y);
	Player(Coord coords);

	bool areCoordsSet() const;
};