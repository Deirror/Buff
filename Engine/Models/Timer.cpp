#include "Timer.h"

void Timer::start()
{
    m_Start = std::chrono::high_resolution_clock::now();
}

void Timer::report()
{
    m_End = std::chrono::high_resolution_clock::now();
}

unsigned short Timer::getCurrentDuration() const
{
    return static_cast<unsigned short>(std::chrono::duration<double>
           (std::chrono::high_resolution_clock::now() - m_Start).count());
}

unsigned short Timer::getLastReportDuration() const
{
    return static_cast<unsigned short>(std::chrono::duration<double>(m_End - m_Start).count());
}
