#pragma once
#include <SDL.h>

class Timer
{
private:
    int lastTick = SDL_GetTicks();
    int curTick = lastTick;

    bool isTick = true;
    int hour = 0, minute = 0, second = 0;
public:
    void StartCount()
    {
        if (isTick)
        {
            curTick = SDL_GetTicks();
            if (curTick - lastTick >= 1000)
            {
                second++;
                lastTick = curTick;
            }
            if (second >= 60)
            {
                minute++;
                second = 0;
            }
            if (minute >= 60)
            {
                hour++;
                minute = 0;
            }
            SDL_Log("Timer %d:%02d:%02d", hour, minute, second);
        }
    }
    void StopCount(bool tickOff)
    {
        isTick = tickOff;
    }
    void ResetCount()
    {
        curTick = 0;
        second = 0;
        minute = 0;
        hour = 0;
    }

    int GetSecond() { return second; }
    int GetMinute() { return minute; }
    int GetHour() { return hour; }
};