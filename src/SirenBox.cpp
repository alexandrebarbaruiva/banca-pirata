/**
 * @file SirenBox.cpp
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief SirenBox class implementation file
 * @version 0.1
 * @date 2022-07-01
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "SirenBox.h"

SirenBox::SirenBox(GameObject &associated) : Component(associated)
{
    associated.AddComponent(new Collider(associated));
}

void SirenBox::Start()
{
    GameObject *sirenGO;
    Siren *siren;
    State *state = &Game::GetInstance().GetCurrentState();

    for (int step = 0; step < 100; step = step + 20)
    {
        sirenGO = new GameObject();
        siren = new Siren(*sirenGO, (100 - step));
        sirenGO->AddComponent(siren);
        sirenGO->box.SetOrigin(associated.box.x, (associated.box.y + 6 * step));
        sirenArray.push_back(state->AddObject(sirenGO));
    }
}

void SirenBox::Update(float dt)
{
}

void SirenBox::Render()
{
}

void SirenBox::NotifyCollision(GameObject &other)
{
}

bool SirenBox::Is(std::string type)
{
    return (type == SirenBox::type);
}
