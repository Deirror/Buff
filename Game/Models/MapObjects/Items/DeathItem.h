#pragma once
#include "Item.h"

class DeathItem : public Item
{
public:
	DeathItem(uint8_t x, uint8_t y, uint8_t symbol);
	DeathItem(Coord coords, uint8_t symbol);

	Item* clone() const override;
};

