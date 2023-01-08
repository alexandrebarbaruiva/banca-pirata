/**
 * @file ButtonBox.h
 * @author Eileen Lima Ribeiro <160049458@aluno.unb.br>
 * @brief ButtonBox class header file
 * @version 0.1
 * @date 2023-01-01
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef BUTTONBOX_HEADER
#define BUTTONBOX_HEADER
#include "Component.h"
#include "Button.h"
#include <vector>
#include <string>
#include <memory>

class ButtonBox: public Component
{
public:
    ButtonBox(GameObject &associated, std::string name);

    std::string name;
    std::string type;
    std::vector<std::shared_ptr<Button>> buttonArray;
    std::shared_ptr<Button> activeButton;

    virtual std::weak_ptr<Button> AddButton(Button *butt);
    virtual std::weak_ptr<Button> GetButtonPtr(Button *butt);
    void NextButton(Button *butt, bool next);
    
    void Update(float dt);
    void Render();
    void NotifyCollision(GameObject &other);
    void ToggleSelect();
    bool Is(std::string type);
};
#endif