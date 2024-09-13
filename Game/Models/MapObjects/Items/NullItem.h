#pragma once
#include "Item.h"

class NullItem : public Item
{
public:
	NullItem(uint8_t x, uint8_t y, uint8_t symbol, bool collectable = true);
	NullItem(Coord coords, uint8_t symbol, bool collectable = true);

	void modifySeconds(uint8_t& seconds) const override;

	Item* clone() const override;
};

