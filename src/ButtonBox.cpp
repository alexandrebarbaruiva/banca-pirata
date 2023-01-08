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
#include <vector>
#include <string>
#include <memory>


ButtonBox::ButtonBox(GameObject &associated, std::string name) : Component(associated)
{
    this->name = name;
    this->type = "ButtonBox";
}


std::weak_ptr<Button> ButtonBox::AddButton(Button *butt)
{
	std::shared_ptr<Button> sharedButton(butt);
	buttonArray.push_back(sharedButton);

	return std::weak_ptr<Button>(sharedButton);
}


std::weak_ptr<Button> ButtonBox::GetButtonPtr(Button *butt)
{
	for (unsigned i = 0; i < buttonArray.size(); i++)
	{
		if (buttonArray[i].get() == butt)
		{
			return std::weak_ptr<Button>(buttonArray[i]);
		}
	}

	return {};
}


void ButtonBox::NextButton(Button *butt, bool next)
{   
    unsigned i;
    for (i = 0; i < buttonArray.size(); i++)
    {
        if (buttonArray[i].get() == butt)
        {
            break;
        }
    }
    if(next){
        if (i > buttonArray.size()){
            this->activeButton = buttonArray[0];
            this->activeButton->isSelected = true;
        } else {
            this->activeButton = buttonArray[i+i];
            this->activeButton->isSelected = true;
        }
        buttonArray[i]->isSelected = false;
    } 
    else {
        if(i < 1){
            this->activeButton = buttonArray.back();
            this->activeButton->isSelected = true;
        }
        else {
            this->activeButton = buttonArray[i-1];
            this->activeButton->isSelected = true;
        }
        buttonArray[i]->isSelected = false;
    }
}


void ButtonBox::Update(float dt)
{
    InputManager input = InputManager::GetInstance();
    switch(input.curEvent){
        case MOUSE_PRESS:
            if (input.MousePress(LEFT_MOUSE_BUTTON) and this->activeButton->clickable)
            {
                bool mouseInButton = this->activeButton->GetIsInside(input.GetMousePosition());
                if (mouseInButton)
                {
                    this->activeButton->isClicked = true;
                    this->activeButton->timesClicked++;
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
        case KEY_DOWN:
            if(input.IsKeyDown(W_KEY) or input.IsKeyDown(UP_ARROW_KEY))
            {
                this->NextButton(this->activeButton, true);
            }
            else if(input.IsKeyDown(S_KEY) or input.IsKeyDown(UP_ARROW_KEY))
            {
                this->NextButton(this->activeButton, false);
            }
            break;
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