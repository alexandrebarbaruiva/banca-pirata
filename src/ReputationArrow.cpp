/**
 * @file ReputationArrow.cpp
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief ReputationArrow class implementation file
 * @version 0.1
 * @date 2022-07-01
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "ReputationArrow.h"

ReputationArrow::ReputationArrow(GameObject &associated, std::string sprite, int relativePos, float scaleX, float scaleY, float frameTime, int frameCount) : Component(associated)
{
#ifdef DEBUG
    this->speed = Vec2(1000, 0);
#endif
    Sprite *spriteItem = new Sprite(associated, sprite, frameCount, frameTime);
    this->endPoint = 710;
    spriteItem->SetScale(scaleX, scaleY);
    associated.AddComponent(spriteItem);
    associated.AddComponent(new Collider(associated));
    this->destinationPoint = relativePos * (this->endPoint - this->startPoint) / 100;
#ifdef DEBUG
    std::cout << "Destination point " << relativePos << "% on " << this->destinationPoint << "\n";
#endif
}

void ReputationArrow::Update(float dt)
{
    if (this->currentPoint >= this->destinationPoint)
    {
        // TODO: change here when reputation starts to change
        this->speed = this->speed * 0;
    }
    // To avoid big jumps when beginning session
    if (dt > 0.1)
    {
        dt = 0.034;
    }
    // Update associated box location correctly
    // associated.box += (speed * dt);
    associated.box = associated.box + (speed * dt);
    this->currentPoint += (Vec2::Mag(speed * dt));
}

void ReputationArrow::Render()
{
}

void ReputationArrow::NotifyCollision(GameObject &other)
{
}

bool ReputationArrow::Is(std::string type)
{
    return (type == ReputationArrow::type);
}
