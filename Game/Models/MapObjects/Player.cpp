#include "Player.h"
//----------------------------------
#include "../../Builds/MapSymbols.h"

Player::Player() : MapEntity(MapSymbols::Objects::ce_Player)
{
}

Player::Player(uint8_t x, uint8_t y) : MapEntity({x,y})
{
}

Player::Player(Coord coords) : MapEntity(coords, MapSymbols::Objects::ce_Player)
{
}

bool Player::areCoordsSet() const
{
	return m_Coords.X > 0 && m_Coords.Y > 0;
}
