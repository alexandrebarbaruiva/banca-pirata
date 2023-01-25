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
#ifndef BUTTONMANAGER_HEADER
#define BUTTONMANAGER_HEADER
#include "Component.h"
#include "GameObject.h"
#include "Button.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

class ButtonManager
{
private:
    void NextButton(std::shared_ptr<GameObject> button, bool next);
    std::unordered_map<std::string, std::vector<std::shared_ptr<GameObject>>> buttonTable;
    std::shared_ptr<GameObject> activeButton;
    std::string activeState = "";
public:
    ButtonManager();
    ~ButtonManager();

    void SetActiveScene(std::string key);
    void ToggleActive(std::vector<std::shared_ptr<GameObject>> vec);
    void AddButton(std::string key, GameObject *button);

    std::vector<std::weak_ptr<GameObject>> GetArray();
    void ToggleSelect();
    bool Is(std::string type);
};
#endif