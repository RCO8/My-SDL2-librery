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
    
    //ÇöÀç½Ã°£ ¹ÝÈ¯
    int GetClockHour() { return GetNowDateTime().tm_hour; }
    int GetClockMinute() { return GetNowDateTime().tm_min; }
    int GetClockSecond() { return GetNowDateTime().tm_sec; }
    //ÇöÀç³¯Â¥ ¹ÝÈ¯
    int GetCalenderMonth() { return GetNowDateTime().tm_mon + 1; }
    int GetCalenderDay() { return GetNowDateTime().tm_mday; }
    int GetCalenderWeek() { return GetNowDateTime().tm_wday; }
    char* GetCalenderWeek(int ver)
    {
        char defaulting[7][10] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
        char eng[7][4] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
        char kor[7][3] = { "ÀÏ", "¿ù", "È­", "¼ö", "¸ñ", "±Ý", "Åä" };
        char jap[7][3] = { "ìí", "êÅ", "ûý", "â©", "ÙÊ", "ÑÑ", "÷Ï" };
        switch (ver)
        {
            case 0:
                return defaulting[GetNowDateTime().tm_wday];
            case 1:
                return eng[GetNowDateTime().tm_wday];
            case 2:
                return kor[GetNowDateTime().tm_wday];
            case 3:
                return jap[GetNowDateTime().tm_wday];
        }
    }
private:
    tm GetNowDateTime()
    {
        time_t nowTime = time(NULL);
        struct tm pTimeInfo;
        localtime_s(&pTimeInfo, &nowTime);
        return pTimeInfo;
    }
};