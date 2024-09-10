#pragma once
#include "Item.h"

class RandomItem : public Item
{
public:
	RandomItem(uint8_t x, uint8_t y, uint8_t pointsLimit, uint8_t secondsLimit);
	RandomItem(Coord coords, uint8_t pointsLimit, uint8_t secondsLimit);
};

