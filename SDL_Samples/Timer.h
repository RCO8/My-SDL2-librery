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
    //알람 설정
    bool alarm = false;
    struct alarmInfo
    {
        int aHour = 999, aMinute = 59, aSecond = 59;
    } nowAlarm;
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
        catch(int e)
        {
            SDL_Log("Set Alarm Error : %d", e);
        }
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
    char* GetCalenderWeek(int ver)
    {
        char defaulting[7][10] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
        char eng[7][4] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
        char kor[7][3] = { "일", "월", "화", "수", "목", "금", "토" };
        char chi[7][3] = { "日", "月", "火", "水", "木", "金", "土" };
        switch (ver)
        {
            case 0:
                return defaulting[GetNowDateTime().tm_wday];
            case 1:
                return eng[GetNowDateTime().tm_wday];
            case 2:
                return kor[GetNowDateTime().tm_wday];
            case 3:
                return chi[GetNowDateTime().tm_wday];
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
    void WaitAlarm()
    {
        if (hour >= aHour && minute >= aMinute && second >= aSecond) alarm = true;
        else alarm = false;
    }
};

class Timeline  //스레드 구현 필요
{
private:
    unsigned int count;
    int ms = 100;
public:
    //count가 0이면 무한반복
    void LoopFrame(int count = 1)  //끝까지 갔으면 처음부터
    {
        int tmp = 0;
        while (tmp <= count)
        {
            SDL_Delay(ms);
            if (count > 0) tmp++;
        }
    }
    void ReverseFrame(int count = 1)   //끝까지 갔으면 거꾸로
    {
        SDL_Delay(ms);
    }
    void CustomFrame(int count, int* frameIndex)   //배열로 프레임 지정
    {
        
        SDL_Delay(ms);
    }
    void SetDelayTime(int ms) 
    {
        if(ms > 0)
            this->ms = ms; 
    }
    
private:
    void StartTimeline();
};