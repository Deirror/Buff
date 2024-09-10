#include "Obsticle.h"
#include "../../Builds/MapSymbols.h"

Obsticle::Obsticle() : MapEntity(MapSymbols::Objects::ce_Obsticle)
{
}

Obsticle::Obsticle(uint8_t x, uint8_t y) : MapEntity({x,y}, MapSymbols::Objects::ce_Obsticle)
{
}

Obsticle::Obsticle(Coord coords) : MapEntity(coords, MapSymbols::Objects::ce_Obsticle)
{
}
