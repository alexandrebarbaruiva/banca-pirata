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
    Button(GameObject &associated, std::string name, float scaleX = 1, float scaleY = 1, std::string sprite = "assets/img/placeholders/botao menu longo.png", bool clickable = true);

    std::string type = "Button";
    std::string name;

    bool clickable;
    bool isClicked;
    bool isSelected;
    int timesClicked;

    void Update(float dt);
    void Render();
    bool Is(std::string type);
    int GetHealth();
    void NotifyCollision(GameObject &other);
};
#endif