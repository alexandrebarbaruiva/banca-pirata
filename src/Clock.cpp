#include "Clock.h"
#include "Text.h"
#include "GameData.h"
#include <iostream>

Clock::Clock(GameObject &associated, int initialHour, int initialMinute) : Component(associated)
{
    time = 0;
    hours = initialHour;
    minutes = initialMinute;

    paused = false;

    WriteClock();

    textClock = new Text(associated, "assets/font/five.ttf", 40, Text::SOLID, (this->clockTime), {255, 255, 255, SDL_ALPHA_OPAQUE});
    associated.AddComponent(textClock);
}

Clock::~Clock()
{
}

void Clock::Update(float dt)
{
    if (!paused)
    {
        time += dt;

        if (time >= 1)
        {
            if (minutes < 59)
            {
                minutes++;
            }
            else
            {
                minutes = 0;
                if (hours < 17)
                {
                    hours++;
                }
                else
                {
                    GameData::endDay = true;
                    hours = 18;
                }
            }

            time = 0;
            WriteClock();
            GameData::currentMinute = minutes;
            GameData::currentHour = hours;

            textClock->SetText(this->clockTime);
        }
    }
}

void Clock::Restart()
{

    time = 0;
    hours = 8;
    minutes = 0;

    GameData::currentMinute = minutes;
    GameData::currentHour = hours;

    this->clockTime = "08:00";
    textClock->SetText(this->clockTime);
}

void Clock::Pause()
{
    paused = true;
}

void Clock::Resume()
{
    paused = false;
}

std::string Clock::GetClock()
{
    return this->clockTime;
}

int Clock::GetHours()
{
    return hours;
}

int Clock::GetMinutes()
{
    return minutes;
}

void Clock::WriteClock()
{
    std::string hourString;
    std::string minuteString;
    if (hours >= 0 && hours < 10)
    {
        hourString = "0" + std::to_string(hours);
    }
    if (hours >= 10 && hours < 24)
    {
        hourString = std::to_string(hours);
    }
    if (minutes >= 0 && minutes < 10)
    {
        minuteString = "0" + std::to_string(minutes);
    }
    if (minutes >= 10 && minutes < 60)
    {
        minuteString = std::to_string(minutes);
    }
    this->clockTime = hourString + ":" + minuteString;
}

void Clock::AssertClock() {
    if(this->hours != GameData::currentHour) {
        this->hours = GameData::currentHour;
        this->minutes = GameData::currentMinute;

        WriteClock();
        textClock->SetText(this->clockTime);
    }
}
void Clock::Render()
{
}

bool Clock::Is(std::string type)
{
    return (type == Clock::type);
}
