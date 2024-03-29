/**
 * @file Siren.cpp
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief Siren class implementation file
 * @version 0.1
 * @date 2022-07-01
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "Siren.h"
#include "GameData.h"

Siren::Siren(GameObject &associated, int reputationScore, float scaleX, float scaleY, float frameTime, int frameCount) : Component(associated), reputationScore(reputationScore)
{
    this->spriteOn = HUD_PATH + "sus.png";
    this->spriteOff = HUD_PATH + "sus-vazio.png";
    Sprite *spriteItem = new Sprite(associated, this->spriteOff, 1, 1.0);
    spriteItem->SetScale(scaleX, scaleY);
    associated.AddComponent(spriteItem);
    associated.AddComponent(new Collider(associated));
}

void Siren::Update(float dt)
{
    if (not isOn and (GameData::currentSus >= reputationScore))
    {
#ifdef DEBUG
        std::cout << "Turn on siren " << reputationScore << "\n";
        std::cout << "CurSus " << GameData::currentSus << "\n";
#endif
        this->isOn = true;
        associated.RemoveComponent(associated.GetComponent("Sprite"));
        Sprite *spriteItem = new Sprite(associated, this->spriteOn);
        // spriteItem->SetScale(scaleX, scaleY);
        associated.AddComponent(spriteItem);
    }
    else if (isOn and (GameData::currentSus < reputationScore))
    {
#ifdef DEBUG
        std::cout << "Turn off siren " << reputationScore << "\n";
        std::cout << "CurSus " << GameData::currentSus << "\n";
#endif
        this->isOn = false;
        associated.RemoveComponent(associated.GetComponent("Sprite"));
        Sprite *spriteItem = new Sprite(associated, this->spriteOff);
        // spriteItem->SetScale(scaleX, scaleY);
        associated.AddComponent(spriteItem);
    }
}

void Siren::Render()
{
}

void Siren::NotifyCollision(GameObject &other)
{
}

bool Siren::Is(std::string type)
{
    return (type == Siren::type);
}
