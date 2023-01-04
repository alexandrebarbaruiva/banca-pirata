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
#include "Vec2.h"

class GameItem : public Component
{
private:
public:
    // GameItem(GameObject &associated, int speed, int startPoint, int endPoint, std::string sprite, float frameTime, int frameCount);
    GameItem(GameObject &associated, std::string sprite, float scaleX = 1, float scaleY = 1, bool moveable = false, float frameTime=1.0, int frameCount=1);

    std::string type = "GameItem";
    std::string name;

    bool moveable = false;
    float startPoint = 0;
    float currentPoint = 0;
    float endPoint = 300;
    Vec2 speed = Vec2(10,0);

    bool clickable = false;
    bool isClicked = false;

    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void NotifyCollision(GameObject &other);
};

#endif
