#include "MapCounts.h"

MapRange::MapRange(uint8_t ubound)
{
    if (ubound >= LBOUND)
    {
        m_UBound = ubound;
    }
}

bool MapRange::isInRange(uint8_t number) const
{
    return (LBOUND <= number && number <= m_UBound);
}
