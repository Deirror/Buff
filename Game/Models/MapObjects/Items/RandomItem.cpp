#include "RandomItem.h"
//-------------------------------------
#include "../../../Builds/MapSymbols.h"
//-------------------------------------
#include <Source/RandomGenerator.h>

static uint8_t generateValidSeconds(uint8_t limit)
{
	static uint8_t lowerBound = 3;
	uint8_t generatedSeconds = NULL;

	do
	{
		generatedSeconds = RandomGenerator::generateNext(limit);
	} while (generatedSeconds <= lowerBound);

	return generatedSeconds;
}

RandomItem::RandomItem(uint8_t x, uint8_t y, uint8_t pointsLimit, uint8_t secondsLimit)
	: Item(x,y,MapSymbols::Objects::Items::ce_RandomItem,
		   RandomGenerator::generateNext(pointsLimit),
		   generateValidSeconds(secondsLimit))
{
}

RandomItem::RandomItem(Coord coords, uint8_t pointsLimit, uint8_t secondsLimit)
	: Item(coords, MapSymbols::Objects::Items::ce_RandomItem,
	       RandomGenerator::generateNext(pointsLimit),
		   generateValidSeconds(secondsLimit))
{
}