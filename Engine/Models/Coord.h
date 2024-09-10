#pragma once

struct Coord
{
	unsigned short X = 0;
	unsigned short Y = 0;
};

bool operator>(Coord lhs, Coord rhs);
bool operator>=(Coord lhs, Coord rhs);
bool operator<(Coord lhs, Coord rhs);
bool operator<=(Coord lhs, Coord rhs);
bool operator==(Coord lhs, Coord rhs);
bool operator!=(Coord lhs, Coord rhs);
