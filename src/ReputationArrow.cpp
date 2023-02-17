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
#include "GameData.h"
#include "GameItem.h"

ReputationArrow::ReputationArrow(GameObject &associated, bool startAtZero, float scaleX, float scaleY, float frameTime, int frameCount) : Component(associated)
{
#ifdef DEBUG
    this->speed = Vec2(1000, 0);
#endif
    this->relativePos = GameData::currentRep;
    this->endPoint = 710;
    this->destinationPoint = (this->endPoint - this->startPoint) * GameData::currentRep / 100;

    this->currentPoint += destinationPoint;

    associated.AddComponent(new GameItem(associated, HUD_PATH + "Rep.png"));
    associated.box.SetOrigin(960, 0);
#ifdef DEBUG
    std::cout << (this->endPoint - this->startPoint) << "\n";
    std::cout << "Destination point " << GameData::currentRep << "% on " << this->destinationPoint << "\n";
#endif
}

void ReputationArrow::Start()
{
    State *state = &Game::GetInstance().GetCurrentState();

    arrowGO = new GameObject();
    arrowGO->AddComponent(new GameItem(*arrowGO, HUD_PATH + "Rep_seta.png"));
    arrowGO->box.SetOrigin(960 + this->currentPoint, 60);
    state->AddObject(arrowGO);
}

void ReputationArrow::Update(float dt)
{
    this->destinationPoint = (this->endPoint - this->startPoint) * GameData::currentRep / 100;
    arrowGO->box.x = 960 + this->destinationPoint;
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
