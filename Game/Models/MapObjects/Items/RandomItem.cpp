#include "RandomItem.h"
//-------------------------------------
#include "../../../Builds/MapSymbols.h"
//-------------------------------------
#include <Source/RandomGenerator.h>

RandomItem::RandomItem(uint8_t x, uint8_t y, uint8_t pointsLimit, uint8_t secondsLimit)
	: Item(x,y,MapSymbols::Objects::Items::ce_RandomItem,
		   RandomGenerator::generateNext(pointsLimit),
		   RandomGenerator::generateValidNext(2, secondsLimit))
{
}

RandomItem::RandomItem(Coord coords, uint8_t pointsLimit, uint8_t secondsLimit)
	: Item(coords, MapSymbols::Objects::Items::ce_RandomItem,
	       RandomGenerator::generateNext(pointsLimit),
		   RandomGenerator::generateValidNext(2, secondsLimit))
{
}

RandomItem::RandomItem(uint8_t x, uint8_t y, uint8_t pointsLowerLimit, uint8_t pointsUpperLimit, 
					   uint8_t secondsLowerLimit, uint8_t secondsUpperLimit)
	: Item(x, y, MapSymbols::Objects::Items::ce_RandomItem,
		   RandomGenerator::generateValidNext(pointsLowerLimit, pointsUpperLimit),
		   RandomGenerator::generateValidNext(secondsLowerLimit, secondsUpperLimit))
{
}

RandomItem::RandomItem(Coord coords, uint8_t pointsLowerLimit, uint8_t pointsUpperLimit,
	                   uint8_t secondsLowerLimit, uint8_t secondsUpperLimit)
	: Item(coords, MapSymbols::Objects::Items::ce_RandomItem,
		   RandomGenerator::generateValidNext(pointsLowerLimit, pointsUpperLimit),
		   RandomGenerator::generateValidNext(secondsLowerLimit, secondsUpperLimit))
{
}
