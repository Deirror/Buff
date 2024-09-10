#pragma once
#include <chrono>

class Timer 
{
public:
    void start();

    unsigned short getDuration() const;

private:
    std::chrono::high_resolution_clock::time_point m_Start;
};

