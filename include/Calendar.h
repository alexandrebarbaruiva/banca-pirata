/**
 * @file Calendar.h
 * @author João Paulo Vaz Mendes (170002934@aluno.unb.br)
 * @brief Calendar class header file
 * @version 0.1
 * @date 2023-01-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef CALENDAR_HEADER
#define CALENDAR_HEADER
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "Component.h"
#include "Text.h"
#include <string>

class Calendar : public Component
{
private:
    int days;
    Text *textCalendar;

public:
    Calendar(GameObject &associated, int initialDay = 1);
    ~Calendar();

    std::string type = "Calendar";

    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void Restart();
    int GetDays();
    void SetDays(int daySetted);
};

#endif