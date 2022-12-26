/**
 * @file GameItem.cpp
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief GameItem class implementation file
 * @version 0.1
 * @date 2022-07-01
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "GameItem.h"

GameItem::GameItem(GameObject &associated, std::string sprite, float frameTime, int frameCount) : Component(associated)
{
    associated.AddComponent(new Sprite(associated, sprite, frameCount, frameTime));
    associated.AddComponent(new Collider(associated));
}

void GameItem::Update(float dt)
{
    if (!this->moveable)
    {
        return;
    }

    // Update associated box location correctly

    // associated.box = associated.box + speed * dt;
    // this->distanceLeft -= Vec2::Mag(speed * dt);
    // if (this->distanceLeft <= 0)
    // {
    //     associated.RequestDelete();
    // }
}

void GameItem::Render()
{
}

void GameItem::NotifyCollision(GameObject &other)
{
}

bool GameItem::Is(std::string type)
{
    return (type == GameItem::type);
}
