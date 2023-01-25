/**
 * @file Button.h
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief Button class header file
 * @version 0.1
 * @date 2022-07-01
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef BUTTON_HEADER
#define BUTTON_HEADER
#include "Component.h"
#include "Constants.h"
#include "Text.h"
#include "Sound.h"


class Button : public Component
{
public:
    Button(GameObject &associated, std::string name, std::string sprite = "assets/img/button.png", bool clickable = true);

    std::string type = "Button";
    std::string name;

    bool clickable;
    bool isClicked;
    bool isSelected;
    int timesClicked;

    void Update(float dt);
    void Render();
    void NotifyCollision(GameObject &other);
    void ToggleSelect();
    bool Is(std::string type);
    bool GetIsInside(Vec2 position);
};
#endif