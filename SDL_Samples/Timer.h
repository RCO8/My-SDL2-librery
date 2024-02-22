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
            if (curTick - lastTick >= 1000)
            {
                second++; lastTick = curTick;
            }
            if (second >= 60)
            {
                minute++; second = 0;
            }
            if (minute >= 60)
            {
                hour++; minute = 0;
            }
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
    int GetClockHour() { return GetNowDateTime().tm_hour; }
    int GetClockMinute() { return GetNowDateTime().tm_min; }
    int GetClockSecond() { return GetNowDateTime().tm_sec; }
    //현재날짜 반환
    int GetCalenderMonth() { return GetNowDateTime().tm_mon + 1; }
    int GetCalenderDay() { return GetNowDateTime().tm_mday; }
    int GetCalenderWeek() { return GetNowDateTime().tm_wday; }  //0 is Sunday to 6 is Saturday
private:
    tm GetNowDateTime()
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

class Timeline  //스레드 구현 필요
{
private:
    unsigned int count = 0;
    int ms = 100;
    unsigned int maxFrame = 10;
    SDL_Thread* thread;
public:
    //count가 0이면 무한반복

    void SetMaxFrame(int f) { maxFrame = f; }
    void SetDelayTime(int ms) { if(ms > 0) this->ms = ms;  }
    void StartTimeLine()
    {
        count = 0;
    }
private:
    int SendKeyFrame()
    {
        SDL_Delay(ms);
        count++;
        return count;
    }
};