/**
 * @file GameItem.h
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief GameItem class header file
 * @version 0.1
 * @date 2022-08-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef GAMEITEM_HEADER
#define GAMEITEM_HEADER
#include "Component.h"
#include "Sprite.h"
#include "Collider.h"

class GameItem : public Component
{
private:
public:
    // GameItem(GameObject &associated, int speed, int startPoint, int endPoint, std::string sprite, float frameTime, int frameCount);
    GameItem(GameObject &associated, std::string sprite, float frameTime=1.0, int frameCount=1);

    std::string type = "GameItem";
    std::string name;

    bool moveable = false;
    int startPoint = 0;
    int endPoint = 300;
    int speed = 10;

    bool clickable = false;
    bool isClicked = false;

    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void NotifyCollision(GameObject &other);
};

#endif
