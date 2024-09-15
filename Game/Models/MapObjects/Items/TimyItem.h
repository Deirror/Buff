#pragma once
#include "Item.h"

class TimyItem : public Item
{
public:
	TimyItem(uint8_t x, uint8_t y, uint8_t symbol, uint8_t seconds, bool collectable = true);
	TimyItem(Coord coords, uint8_t symbol, uint8_t seconds, bool collectable = true);

	Item* clone() const override;
};

