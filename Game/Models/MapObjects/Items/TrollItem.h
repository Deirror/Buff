#pragma once
#include "TeleportItem.h"

class TrollItem : public TeleportItem
{
public:
	TrollItem(uint8_t x, uint8_t y, uint8_t teleportX, uint8_t teleportY);
	TrollItem(Coord coords, Coord teleportCoords);

	void modifyPoints(uint16_t& points) const override;
	Item* clone() const override;
};