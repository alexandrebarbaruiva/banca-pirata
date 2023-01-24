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
    ~ButtonBox();
    std::string name;
    std::string type = "ButtonBox";
    std::vector<std::shared_ptr<GameObject>> buttonArray;
    std::shared_ptr<GameObject> activeButton;

    std::shared_ptr<GameObject> AddButton(GameObject *butt);
    std::vector<std::weak_ptr<GameObject>> GetArray();
    
    void Update(float dt);
    void Render();
    void NotifyCollision(GameObject &other);
    void ToggleSelect();
    bool Is(std::string type);
private:
   void NextButton(std::shared_ptr<GameObject> butt, bool next);
};
#endif