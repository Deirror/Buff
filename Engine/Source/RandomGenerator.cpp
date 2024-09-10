#include "RandomGenerator.h"

void RandomGenerator::setSeed()
{
	srand(static_cast<unsigned int>(time(0)));
}

size_t RandomGenerator::generateNext(size_t limit)
{
	return rand() % limit;
}
