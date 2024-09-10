#include "Dimension.h"

Dimension::operator unsigned int() const
{
	return Width * Height;
}

bool operator>(Dimension lhs, Dimension rhs)
{
	return (lhs.Width > rhs.Width) && (lhs.Height > rhs.Height);
}

bool operator>=(Dimension lhs, Dimension rhs)
{
	return (lhs.Width >= rhs.Width) && (lhs.Height >= rhs.Height);
}

bool operator<(Dimension lhs, Dimension rhs)
{
	return (lhs.Width < rhs.Width) && (lhs.Height < rhs.Height);
}

bool operator<=(Dimension lhs, Dimension rhs)
{
	return (lhs.Width <= rhs.Width) && (lhs.Height <= rhs.Height);
}

bool operator==(Dimension lhs, Dimension rhs)
{
	return (lhs.Width == rhs.Width) && (lhs.Height == rhs.Height);
}

bool operator!=(Dimension lhs, Dimension rhs)
{
	return !(lhs == rhs);
}