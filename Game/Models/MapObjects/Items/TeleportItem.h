#pragma once
#include "Item.h"

class TeleportItem : public Item
{
public:
	TeleportItem(uint8_t x, uint8_t y, uint8_t seconds, uint8_t teleportX, uint8_t teleportY);
	TeleportItem(Coord coords, uint8_t seconds, Coord teleportCoords);

	void teleportPlayer(Coord& coords) const;

	Item* clone() const override;

private:
	Coord m_TeleportCoords;
};

