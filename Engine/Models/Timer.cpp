#include "Timer.h"

void Timer::start()
{
    m_Start = std::chrono::high_resolution_clock::now();
}

unsigned short Timer::getDuration() const
{
    return static_cast<unsigned short>(std::chrono::duration<double>
        (std::chrono::high_resolution_clock::now() - m_Start).count());
}