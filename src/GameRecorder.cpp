/**
 * @file GameRecorder.cpp
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief GameRecorder class implementation file
 * @version 0.1
 * @date 2022-07-01
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "GameRecorder.h"

GameRecorder::GameRecorder(GameObject &associated, std::string sprite, float scaleX, float scaleY, int frameCount, float frameTime, float secondsToSelfDestruct) : Component(associated)
{
    Sprite *spriteItem = new Sprite(associated, sprite, frameCount, frameTime, secondsToSelfDestruct);
    spriteItem->SetScale(scaleX, scaleY);
    associated.AddComponent(spriteItem);
    associated.AddComponent(new Collider(associated));
}

GameRecorder::~GameRecorder()
{
    State *state = &Game::GetInstance().GetCurrentState();
    state->RequestPop();
}

void GameRecorder::Update(float dt)
{
    if (not this->recorded)
    {
        this->recorded = true;
        State *state = &Game::GetInstance().GetCurrentState();
        std::vector<std::weak_ptr<GameObject>> cbs = state->QueryObjectsByComponent("ComputerBox");
        int selectedGame[3];
        for (unsigned i = 0; i < cbs.size(); i++)
        {
            ComputerBox *computerBox = ((ComputerBox *)(cbs[i].lock()->GetComponent("ComputerBox")));
            std::copy(computerBox->selectedGame, computerBox->selectedGame + 3, selectedGame);
        }
        std::cout << selectedGame[0] << " " << selectedGame[1] << " " << selectedGame[2] << "\n";
        // add reputation, sus and money

    }
}

void GameRecorder::Render()
{
}

void GameRecorder::NotifyCollision(GameObject &other)
{
}

bool GameRecorder::Is(std::string type)
{
    return (type == GameRecorder::type);
}
