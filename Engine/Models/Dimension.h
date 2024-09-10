#pragma once

struct Dimension
{
	unsigned short Width = 0;
	unsigned short Height = 0;

	operator unsigned int() const;
};

bool operator>(Dimension lhs, Dimension rhs);
bool operator>=(Dimension lhs, Dimension rhs);
bool operator<(Dimension lhs, Dimension rhs);
bool operator<=(Dimension lhs, Dimension rhs);
bool operator==(Dimension lhs, Dimension rhs);
bool operator!=(Dimension lhs, Dimension rhs);
