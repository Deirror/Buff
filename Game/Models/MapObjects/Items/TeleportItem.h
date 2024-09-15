#pragma once
#include "Item.h"
//-------------------------------------
#include "../../../Builds/MapSymbols.h"

class TeleportItem : public Item
{
public:
	TeleportItem(uint8_t x, uint8_t y, uint8_t teleportX, uint8_t teleportY, uint8_t symbol = MapSymbols::Objects::Items::ce_TeleportItem);
	TeleportItem(Coord coords, Coord teleportCoords, uint8_t symbol = MapSymbols::Objects::Items::ce_TeleportItem);

	void modifySeconds(uint8_t& seconds) const;
	virtual void teleportPlayer(Coord& coords) const;

	Item* clone() const override;

protected:
	Coord m_TeleportCoords;
};

