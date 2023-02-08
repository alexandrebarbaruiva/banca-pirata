/**
 * @file AssetItem.cpp
 * @author João Paulo Vaz Mendes (170002934@aluno.unb.br)
 * @brief AssetItem class header file
 * @version 0.1
 * @date 2023-02-07
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "AssetItem.h"

AssetItem::AssetItem(GameObject &associated, AssetGame *gameLinked , std::string sprite, float scaleX, float scaleY, bool moveable, float frameTime, int frameCount) : Component(associated), moveable(moveable)
{
    Sprite *spriteItem = new Sprite(associated, sprite, frameCount, frameTime);
    spriteItem->SetScale(scaleX, scaleY);
    associated.AddComponent(spriteItem);
    associated.AddComponent(new Collider(associated));

    gameOrigin = gameLinked;
    this->name = gameLinked->name;
}

void AssetItem::Update(float dt)
{
    if (!gameOrigin->gameChoosed)
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
    else
    {
        associated.RequestDelete();
    }
}

void AssetItem::Render()
{
}

void AssetItem::NotifyCollision(GameObject &other)
{
}

bool AssetItem::Is(std::string type)
{
    return (type == AssetItem::type);
}
