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


void ButtonManager::AddButton(std::string key, std::shared_ptr<GameObject> button)
{
	std::shared_ptr<GameObject> sharedButton(button);
    std::vector<std::shared_ptr<GameObject>> vec;
    std::unordered_map<std::string, std::vector<std::shared_ptr<GameObject>>>::const_iterator search = buttonTable.find(key);
    if (search != this->buttonTable.end())
    {
        std::vector<std::shared_ptr<GameObject>> found = search->second;
        found.emplace_back(sharedButton);
    }
    else
    {   
        buttonTable.emplace(key, vec);
        buttonTable[key].emplace_back(sharedButton);
    }
}


void ButtonManager::NextButton(std::shared_ptr<GameObject> button, bool next)
{   
    unsigned i;
    for (i = 0; i < buttonTable[activeState].size(); i++)
    {
        if (buttonTable[activeState][i].get() == button.get())
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
    Button *curButton = (Button *)activeButton->GetComponent("Button");
    curButton->isSelected = true;
    Button *pastButton = ((Button *)(buttonTable[activeState][i]->GetComponent("Button")));
    pastButton->isSelected = false;
}


bool ButtonManager::Is(std::string type)
{
    return (type == "ButtonManager");
}


void ButtonManager::ToggleActive(std::vector<std::shared_ptr<GameObject>> vec)
{
    for(auto& it: vec)
    {
        Button *button = (Button *) (it->GetComponent("Button"));
        button->active = ! (button->active);
    }
}


void ButtonManager::SetActiveScene(std::string key)
{
    if (activeState != "")
    {
        ToggleActive(buttonTable[activeState]);
    }
    ToggleActive(buttonTable[key]);
    activeState = key;
}
