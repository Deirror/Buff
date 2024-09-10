#include "SecondChecker.h"

SecondChecker::SecondChecker() : start(std::chrono::high_resolution_clock::now()) {}

void SecondChecker::reset() 
{
    start = std::chrono::high_resolution_clock::now();
}

bool SecondChecker::hasOneSecondPassed() const
{
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double>(now - start).count();
    return duration >= 1.0;
}
