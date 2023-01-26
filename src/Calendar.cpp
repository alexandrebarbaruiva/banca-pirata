#include "Text.h"
#include "GameData.h"
#include "Calendar.h"
#include <iostream>


Calendar::Calendar(GameObject &associated, int initialDay) : Component(associated) {
    days = initialDay;

    textCalendar = new Text(associated, "assets/font/five.ttf", 40, Text::SOLID, ("Day " + std::to_string(days)) ,{255, 255, 255, SDL_ALPHA_OPAQUE}) ;
    associated.AddComponent(textCalendar);
}

Calendar::~Calendar() {

}
void Calendar::Update(float dt) {
    float time;
    time += dt;
    
    if(days != GameData::currentDay) {
        days = GameData::currentDay;

        textCalendar->SetText(("Day " + std::to_string(days)));
    }
}

void Calendar::Restart(){
    days = 1;
    GameData::currentDay = 1;
}

int Calendar::GetDays() {
    return days;
}

void Calendar::SetDays(int daySetted) {
    days = daySetted;
    GameData::currentDay = daySetted;
}

void Calendar::Render()
{
}

bool Calendar::Is(std::string type)
{
    return (type == Calendar::type);
}