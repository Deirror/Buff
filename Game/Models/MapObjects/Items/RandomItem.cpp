#include "RandomItem.h"
//-------------------------------------
#include "../../../Builds/MapSymbols.h"
//-------------------------------------
#include <Source/RandomGenerator.h>

static uint8_t generateValidNumber(uint8_t lowerLimit, uint8_t upperLimit)
{
	uint8_t generatedSeconds = NULL;

	do
	{
		generatedSeconds = RandomGenerator::generateNext(upperLimit);
	} while (generatedSeconds < lowerLimit);

	return generatedSeconds;
}

static uint8_t generateValidNumber(uint8_t limit)
{
	return generateValidNumber(2, limit);
}


RandomItem::RandomItem(uint8_t x, uint8_t y, uint8_t pointsLimit, uint8_t secondsLimit)
	: Item(x,y,MapSymbols::Objects::Items::ce_RandomItem,
		   RandomGenerator::generateNext(pointsLimit),
	       generateValidNumber(secondsLimit))
{
}

RandomItem::RandomItem(Coord coords, uint8_t pointsLimit, uint8_t secondsLimit)
	: Item(coords, MapSymbols::Objects::Items::ce_RandomItem,
	       RandomGenerator::generateNext(pointsLimit),
		   generateValidNumber(secondsLimit))
{
}

RandomItem::RandomItem(uint8_t x, uint8_t y, uint8_t pointsLowerLimit, uint8_t pointsUpperLimit, 
					   uint8_t secondsLowerLimit, uint8_t secondsUpperLimit)
	: Item(x, y, MapSymbols::Objects::Items::ce_RandomItem,
		   generateValidNumber(pointsLowerLimit, pointsUpperLimit),
		   generateValidNumber(secondsLowerLimit, secondsUpperLimit))
{
}

RandomItem::RandomItem(Coord coords, uint8_t pointsLowerLimit, uint8_t pointsUpperLimit,
	                   uint8_t secondsLowerLimit, uint8_t secondsUpperLimit)
	: Item(coords, MapSymbols::Objects::Items::ce_RandomItem,
		   generateValidNumber(pointsLowerLimit, pointsUpperLimit),
		   generateValidNumber(secondsLowerLimit, secondsUpperLimit))
{
}
