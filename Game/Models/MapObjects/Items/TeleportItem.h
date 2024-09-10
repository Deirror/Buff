#pragma once
#include "Item.h"

class TeleportItem : public Item
{
public:
	TeleportItem(uint8_t x, uint8_t y, uint8_t teleportX, uint8_t teleportY);
	TeleportItem(Coord coords, Coord teleportCoords);

	void modifySeconds(uint8_t& seconds) const;
	virtual void teleportPlayer(Coord& coords) const;

	Item* clone() const override;

protected:
	Coord m_TeleportCoords;
};

