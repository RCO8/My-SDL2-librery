#pragma once
#include <SDL.h>
#include <SDL_thread.h>
#include <ctime>
#include <iostream>
class Timer
{
private:
    int lastTick = SDL_GetTicks();
    int curTick = lastTick;

    bool isTick = true;
    int hour = 0, minute = 0, second = 0;
    //알람 설정
    bool alarm = false;
    struct alarmInfo { int aHour = 999, aMinute = 59, aSecond = 59; } nowAlarm;

public:
    void StartCount()
    {
        if (isTick)
        {
            curTick = SDL_GetTicks();
            if (curTick - lastTick >= 1000) second++; lastTick = curTick;
            if (second >= 60) minute++; second = 0;
            if (minute >= 60) hour++; minute = 0;
            //SDL_Log("Timer %d:%02d:%02d", hour, minute, second);
            WaitAlarm();
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

    void SetAlarm(int h, int m, int s)
    {
        nowAlarm.aHour = h;
        try
        {
            if (nowAlarm.aMinute > 59) throw m;
            nowAlarm.aMinute = m;

            if (nowAlarm.aSecond > 59) throw s;
            nowAlarm.aSecond = s;
        }
        catch(int e) { SDL_Log("Set Alarm Error : %d", e); }
    }
    alarmInfo CheckAlarm() const { return nowAlarm; }
    bool GetAlarm() { return alarm; }

    int GetSecond() { return second; }
    int GetMinute() { return minute; }
    int GetHour() { return hour; }
    
    //현재시간 반환
    static int GetClockHour() { return GetNowDateTime().tm_hour; }
    static int GetClockMinute() { return GetNowDateTime().tm_min; }
    static int GetClockSecond() { return GetNowDateTime().tm_sec; }
    //현재날짜 반환
    static int GetCalenderMonth() { return GetNowDateTime().tm_mon + 1; }
    static int GetCalenderDay() { return GetNowDateTime().tm_mday; }
    static int GetCalenderWeek() { return GetNowDateTime().tm_wday; }  //0 is Sunday to 6 is Saturday
private:
    static tm GetNowDateTime()
    {
        time_t nowTime = time(NULL);
        struct tm pTimeInfo;
        localtime_s(&pTimeInfo, &nowTime);
        return pTimeInfo;
    }
    void WaitAlarm()
    {
        alarm = (hour >= nowAlarm.aHour &&
            minute >= nowAlarm.aMinute &&
            second >= nowAlarm.aSecond);
    }
};