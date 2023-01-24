/**
 * @file ButtonBox.cpp
 * @author Eileen Lima Ribeiro <160049458@aluno.unb.br>
 * @brief ButtonBox class implementation file
 * @version 0.1
 * @date 2023-01-01
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "Button.h"
#include "ButtonBox.h"
#include "Sprite.h"
#include "Collider.h"
#include "InputManager.h"
#include <vector>
#include <string>
#include <memory>


ButtonBox::ButtonBox(GameObject &associated, std::string name) : Component(associated)
{
    this->name = name;
}


ButtonBox::~ButtonBox(){
    buttonArray.clear();
}


std::shared_ptr<GameObject> ButtonBox::AddButton(GameObject *butt)
{
	std::shared_ptr<GameObject> sharedButton(butt);
	buttonArray.push_back(sharedButton);

	return std::shared_ptr<GameObject>(sharedButton);
}


void ButtonBox::NextButton(std::shared_ptr<GameObject> butt, bool next)
{   
    unsigned i;
    for (i = 0; i < buttonArray.size(); i++)
    {
        if (buttonArray[i].get() == butt.get())
        {
            break;
        }
    }
    if(next){
        if (i > buttonArray.size()){
            activeButton = buttonArray[0];
        } else {
            activeButton = buttonArray[i+i];
        }
    } 
    else {
        if(i < 1){
            activeButton = buttonArray.back();
        }
        else {
            activeButton = buttonArray[i-1];
        }
    }
    Button *curButton = (Button *)activeButton->GetComponent("Button");
    curButton->isSelected = true;
    Button *pastButton = ((Button *)(buttonArray[i]->GetComponent("Button")));
    pastButton->isSelected = false;
}


void ButtonBox::Update(float dt)
{
    InputManager input = InputManager::GetInstance();
    Button *button = ((Button *)(this->activeButton->GetComponent("Button")));
    switch(input.curEvent){
    case InputOptions::MOUSE_DOWN:
        if (input.MousePress(LEFT_MOUSE_BUTTON) and button->clickable)
        {
            bool mouseInButton = button->GetIsInside(input.GetMousePosition());
            if (mouseInButton)
            {
                button->isClicked = true;
                button->timesClicked++;
        #ifdef DEBUG
                Sound *sound = new Sound(associated, "assets/audio/quack.mp3");
                sound->Play();
                std::cout << GREEN;
                std::cout << this->name;
                std::cout << RESET;
                std::cout << " has been clicked " << this->timesClicked << " times.\n";
        #endif
            }
        }
        break;
    case InputOptions::KEY_DOWN:
        if(input.IsKeyDown(W_KEY) or input.IsKeyDown(UP_ARROW_KEY))
        {
            NextButton(activeButton, true);
        }
        else if(input.IsKeyDown(S_KEY) or input.IsKeyDown(UP_ARROW_KEY))
        {
            NextButton(activeButton, false);
        }
        break;
    }

}

void ButtonBox::Render()
{
}

void ButtonBox::NotifyCollision(GameObject &other)
{
}

bool ButtonBox::Is(std::string type)
{
    return (type == ButtonBox::type);
}


std::vector<std::weak_ptr<GameObject>> ButtonBox::GetArray()
{
    std::vector<std::weak_ptr<GameObject>> array;
    for(std::shared_ptr<GameObject> button: this->buttonArray){
        std::weak_ptr<GameObject> butt(button);
        array.push_back(butt);
    }
    return array;
}