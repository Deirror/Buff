#pragma once
#include <chrono>

class SecondChecker 
{
public:
    SecondChecker();

    void reset();

    bool hasOneSecondPassed() const;

private:
    std::chrono::high_resolution_clock::time_point start;
};
