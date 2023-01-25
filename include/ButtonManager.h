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
#include "InputManager.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>


class ButtonManager
{
private:
    std::unordered_map<std::string, std::vector<std::string>> buttonTable;
    std::string activeButton = "";
    std::string activeState = "";
public:
    typedef enum typeEvents
    {
        Start = 1,
        Continue = 2,
        Quit = 3
    } Events;
    ButtonManager();
    ~ButtonManager();

    void SetActiveScene(std::string key);
    void SetActiveButton(std::string button);
    void ToggleActive(std::vector<std::shared_ptr<GameObject>> vec);
    void AddButton(std::string key, std::string button);
    std::string NextButton(std::string button, bool next);

    Events Update(std::vector<std::weak_ptr<GameObject>> buttons);

    void ToggleSelect();
    bool Is(std::string type);
};
#endif