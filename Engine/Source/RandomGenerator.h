#pragma once
#include <cstdlib>
#include <ctime>

namespace RandomGenerator
{
	void setSeed();

	size_t generateNext(size_t limit);
}

