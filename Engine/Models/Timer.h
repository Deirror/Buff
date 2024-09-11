#pragma once
#include <chrono>

class Timer 
{
public:
    void start();
    void report();

    unsigned short getCurrentDuration() const;
    unsigned short getLastReportDuration() const;

private:
    std::chrono::high_resolution_clock::time_point m_Start;
    std::chrono::high_resolution_clock::time_point m_End;
};

