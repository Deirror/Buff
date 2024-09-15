#pragma once
#include <cstdlib>
#include <ctime>

namespace RandomGenerator
{
	void setSeed();

	size_t generateNext(size_t limit);

	size_t generateValidNext(size_t lowerLimit, size_t upperLimit);
}

