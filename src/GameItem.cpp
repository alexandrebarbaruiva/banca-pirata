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

GameItem::GameItem(GameObject &associated, std::string sprite, float scaleX, float scaleY, bool moveable, float frameTime, int frameCount) : Component(associated), moveable(moveable)
{
    Sprite *spriteItem = new Sprite(associated, sprite, frameCount, frameTime);
    spriteItem->SetScale(scaleX, scaleY);
    associated.AddComponent(spriteItem);
    associated.AddComponent(new Collider(associated));
}

void GameItem::Update(float dt)
{
    if (!this->moveable)
    {
        return;
    }

    // Update associated box location correctly
    associated.box = associated.box + speed * dt;
    this->currentPoint += (Vec2::Mag(speed * dt));
    if (this->currentPoint >= endPoint)
    {
        this->endPoint = this->startPoint;
        this->startPoint = this->currentPoint;
        // this->speed = (this->speed) * -1;
        this->speed = this->speed * 0;
    }
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
