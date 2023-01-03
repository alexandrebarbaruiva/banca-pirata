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


std::weak_ptr<Button> ButtonBox::NextButton(Button *butt, bool next)
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
            return std::weak_ptr<Button>(buttonArray[0]);
        }
        return std::weak_ptr<Button>(buttonArray[i+1]);
    } 
    else {
        if(i < 1){
            return std::weak_ptr<Button>(buttonArray.back());
        }
        return std::weak_ptr<Button>(buttonArray[i-1]);
    }
}
