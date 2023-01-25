/**
 * @key ButtonManager.cpp
 * @author Eileen Lima Ribeiro <160049458@aluno.unb.br>
 * @brief ButtonManager class implementation key
 * @version 0.1
 * @date 2023-01-01
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "Button.h"
#include "ButtonManager.h"
#include "Sprite.h"


ButtonManager::ButtonManager()
{

}


ButtonManager::~ButtonManager(){
    this->buttonTable.clear();
}


void ButtonManager::AddButton(std::string key, std::string button)
{
    std::vector<std::string> vec;
    std::unordered_map<std::string, std::vector<std::string>>::const_iterator search = buttonTable.find(key);
    if (search != this->buttonTable.end())
    {
        std::vector<std::string> found = search->second;
        found.emplace_back(button);
    }
    else
    {   
        buttonTable.emplace(key, vec);
        buttonTable[key].emplace_back(button);
    }
}


std::string ButtonManager::NextButton(std::string curButton, bool next)
{   
    unsigned i;
    for (i = 0; i < buttonTable[activeState].size(); i++)
    {
        if (buttonTable[activeState][i] == curButton)
        {
            break;
        }
    }
    if(next){
        if (i > buttonTable[activeState].size()){
            activeButton = buttonTable[activeState][0];
        } else {
            activeButton = buttonTable[activeState][i+i];
        }
    } 
    else {
        if(i < 1){
            activeButton = buttonTable[activeState].back();
        }
        else {
            activeButton = buttonTable[activeState][i-1];
        }
    }
    return activeButton;
}


bool ButtonManager::Is(std::string type)
{
    return (type == "ButtonManager");
}


void ButtonManager::SetActiveScene(std::string key)
{
    activeState = key;
}


void ButtonManager::SetActiveButton(std::string button)
{
    activeButton = button;
}


    ButtonManager::Events ButtonManager::Update(std::vector<std::weak_ptr<GameObject>> buttons)
{
    InputManager input = InputManager::GetInstance();
    std::string pressedButton;
    for (unsigned i = 0; i < buttons.size(); i++)
    {
        Button *button = ((Button *)(buttons[i].lock()->GetComponent("Button")));
        if (button->isClicked)
        {
            pressedButton = button->name;
            button->isClicked = false;
        }
    }

    if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) or InputManager::GetInstance().QuitRequested() or pressedButton == "exitButton")
    {
        return Events::Quit;
    }

    else if (InputManager::GetInstance().KeyPress(SPACE_KEY) or pressedButton == "startButton")
    {
        return Events::Start;
    }

    else if (InputManager::GetInstance().KeyPress(SPACE_KEY) or pressedButton == "continueButton")
    {
        return Events::Continue;
    }

}