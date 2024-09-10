#pragma once
#include <stdint.h>
#define LBOUND 1

class MapRange
{
public:
	MapRange(uint8_t ubound);

	bool isInRange(uint8_t number) const;

private:
	uint8_t m_UBound = LBOUND;
};

namespace MapCounts
{
	static const MapRange s_MapVariantsCount  = { 3 };
	static const MapRange s_MapBuildsCounts[] = { 3, 2, 2 };
}