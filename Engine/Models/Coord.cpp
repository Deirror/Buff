#include "Coord.h"

bool operator>(Coord lhs, Coord rhs)
{
    return (lhs.X > rhs.X) && (lhs.Y > rhs.Y);
}

bool operator>=(Coord lhs, Coord rhs)
{
    return (lhs.X >= rhs.X) && (lhs.Y >= rhs.Y);
}

bool operator<(Coord lhs, Coord rhs)
{
    return (lhs.X < rhs.X) && (lhs.Y < rhs.Y);
}

bool operator<=(Coord lhs, Coord rhs)
{
    return (lhs.X <= rhs.X) && (lhs.Y <= rhs.Y);
}

bool operator==(Coord lhs, Coord rhs)
{
    return (lhs.X == rhs.X) && (lhs.Y == rhs.Y);
}

bool operator!=(Coord lhs, Coord rhs)
{
    return !(lhs == rhs);
}
