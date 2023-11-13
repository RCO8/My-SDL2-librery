#pragma once
#include <SDL.h>
#include <ctime>
#include <iostream>
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
            //SDL_Log("Timer %d:%02d:%02d", hour, minute, second);
        }
    }
    void StopCount(bool tickOff) { isTick = tickOff; }
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

    int* GetClock()     //현재시간 반환
    {
        time_t nowTime = time(NULL);
        struct tm pTimeInfo;

        localtime_s(&pTimeInfo, &nowTime);

        int* dayTime = nullptr;
        *(dayTime + 1) = pTimeInfo.tm_hour;
        *(dayTime + 2) = pTimeInfo.tm_min;
        *(dayTime + 3) = pTimeInfo.tm_sec;
        return dayTime;
    }
    int* GetCalender()  //현재날짜 반환
    {
        time_t nowTime = time(NULL);
        struct tm pTimeInfo;

        localtime_s(&pTimeInfo, &nowTime);

        int* nowDate = nullptr;
        *(nowDate + 1) = pTimeInfo.tm_mon + 1;
        *(nowDate + 2) = pTimeInfo.tm_mday;
        *(nowDate + 3) = pTimeInfo.tm_wday;
        return nowDate;
    }
};