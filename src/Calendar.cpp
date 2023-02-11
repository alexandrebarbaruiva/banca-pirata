#include "Text.h"
#include "Calendar.h"
#include "GameData.h"
#include <iostream>


Calendar::Calendar(GameObject &associated, int initialDay) : Component(associated) {
    this->days = initialDay;

    textCalendar = new Text(associated, "assets/font/five.ttf", 40, Text::SOLID, ("Day " + std::to_string(this->days)) ,{255, 255, 255, SDL_ALPHA_OPAQUE}) ;
    associated.AddComponent(textCalendar);
}

Calendar::~Calendar() {

}
void Calendar::Update(float dt) {
    if(this->days != GameData::currentDay) {
        this->days = GameData::currentDay;

        textCalendar->SetText(("Day " + std::to_string(this->days)));
    }
}

void Calendar::Restart(){
    this->days = GameData::currentDay = 1;
}

int Calendar::GetDays() {
    return this->days;
}

void Calendar::SetDays(int daySetted) {
    this->days = daySetted;
    GameData::currentDay = daySetted;
}

void Calendar::Render()
{
}

bool Calendar::Is(std::string type)
{
    return (type == Calendar::type);
}