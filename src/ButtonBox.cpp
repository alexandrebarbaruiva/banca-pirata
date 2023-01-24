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
    this->type = "ButtonBox";
}


std::shared_ptr<Button> ButtonBox::AddButton(Button *butt)
{
	std::shared_ptr<Button> sharedButton(butt);
	buttonArray.push_back(sharedButton);

	return std::shared_ptr<Button>(sharedButton);
}


std::shared_ptr<Button> ButtonBox::GetButtonPtr(Button *butt)
{
    std::shared_ptr<Button> sharedButton(butt);
	for (unsigned i = 0; i < buttonArray.size(); i++)
	{
		if (buttonArray[i].get() == sharedButton.get())
		{
			return std::shared_ptr<Button>(buttonArray[i]);
		}
	}
	return nullptr;
}


void ButtonBox::NextButton(std::shared_ptr<Button> butt, bool next)
{   
    unsigned i;
    std::shared_ptr<Button> sharedButton(butt);
    for (i = 0; i < buttonArray.size(); i++)
    {
        if (buttonArray[i].get() == sharedButton.get())
        {
            break;
        }
    }
    if(next){
        if (i > buttonArray.size()){
            activeButton = buttonArray[0];
            activeButton->isSelected = true;
        } else {
            activeButton = buttonArray[i+i];
            activeButton->isSelected = true;
        }
        buttonArray[i]->isSelected = false;
    } 
    else {
        if(i < 1){
            activeButton = buttonArray.back();
            activeButton->isSelected = true;
        }
        else {
            activeButton = buttonArray[i-1];
            activeButton->isSelected = true;
        }
        buttonArray[i]->isSelected = false;
    }
}


void ButtonBox::Update(float dt)
{
    InputManager input = InputManager::GetInstance();
    switch(input.curEvent){
    case InputOptions::MOUSE_DOWN:
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