#include "RandomGenerator.h"

void RandomGenerator::setSeed()
{
	srand(static_cast<unsigned int>(time(0)));
}

size_t RandomGenerator::generateNext(size_t limit)
{
	return rand() % limit;
}

size_t RandomGenerator::generateValidNext(size_t lowerLimit, size_t upperLimit)
{
	size_t generatedSeconds = NULL;

	do
	{
		generatedSeconds = RandomGenerator::generateNext(upperLimit);
	} while (generatedSeconds < lowerLimit);

	return generatedSeconds;
}
