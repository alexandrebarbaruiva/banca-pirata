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
#include "Collider.h"

class ComputerBox : public Component
{
private:
    std::vector<std::weak_ptr<GameObject>> tabArray;
    std::vector<std::weak_ptr<GameObject>> tabIconArray;
    std::vector<std::weak_ptr<GameObject>> gameIconArray;
    std::vector<std::weak_ptr<GameObject>> gameCoverArray;
    GameObject *gameRecorderButton;
    GameObject *selectedGameIcon;
    std::string coverOptions[3] = {"fundo", "1", "2"};
    bool changedTab = false;
    int selectedTab = 1;
    Vec2 selectedGamePosition[3] = {Vec2(0,0), Vec2(0,0), Vec2(0,0)};

public:
    ComputerBox(GameObject &associated);

    std::string type = "ComputerBox";
    int selectedGame[3] = {-1, -1, -1};

    void Start();
    void Update(float dt);
    void UpdateTab();
    void UpdateTabIcon();
    void UpdateGameIcon();
    void UpdateGameCover();
    void UpdateGameSelector();
    void Render();
    bool Is(std::string type);
    void NotifyCollision(GameObject &other);
};

#endif
