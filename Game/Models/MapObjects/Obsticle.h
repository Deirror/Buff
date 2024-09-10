#pragma once
#include "MapEntity.h"

class Obsticle : public MapEntity
{
public:
	Obsticle();
	Obsticle(uint8_t x, uint8_t y);
	Obsticle(Coord coords);
};

