/**
 * @file ComputerBox.h
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief ComputerBox class header file
 * @version 0.1
 * @date 2022-08-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef COMPUTER_BOX_HEADER
#define COMPUTER_BOX_HEADER
#include "Component.h"
#include "Sprite.h"
#include "State.h"
#include "Siren.h"
#include "Collider.h"

class ComputerBox : public Component
{
private:
    std::vector<std::weak_ptr<GameObject>> tabArray;
    std::vector<std::weak_ptr<GameObject>> tabIconArray;
    std::vector<std::weak_ptr<GameObject>> gameIconArray;
    bool changedTab = false;
    int selectedTab = 0;
    int selectedGame[3] = {-1, -1, -1};

public:
    ComputerBox(GameObject &associated);

    std::string type = "ComputerBox";

    void Start();
    void Update(float dt);
    void UpdateTab();
    void UpdateTabIcon();
    void UpdateGameIcon();
    void Render();
    bool Is(std::string type);
    void NotifyCollision(GameObject &other);
};

#endif
