/**
 * @file GameRecorderButton.cpp
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief GameRecorderButton class implementation file
 * @version 0.1
 * @date 2022-07-01
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "GameRecorderButton.h"

GameRecorderButton::GameRecorderButton(GameObject &associated, float scaleX, float scaleY, float frameTime, int frameCount) : Component(associated)
{
    Sprite *spriteItem = new Sprite(associated, SCREEN2_PATH + "tela2-Botao gravar.png", frameCount, frameTime);
    spriteItem->SetScale(scaleX, scaleY);
    associated.AddComponent(spriteItem);
    associated.AddComponent(new Collider(associated));
}

void GameRecorderButton::Update(float dt)
{

    InputManager input = InputManager::GetInstance();
    if (input.MousePress(LEFT_MOUSE_BUTTON) and associated.box.IsInside(input.GetMousePosition()) and clickable and not GameData::endDay)
    {
        // change clicked disc
        associated.RemoveComponent(associated.GetComponent("Sprite"));
        associated.AddComponent(new Sprite(associated, SCREEN2_PATH + "tela2-Botao gravar hover.png", 1, 1));

        // create record img
        State *state = &Game::GetInstance().GetCurrentState();
        GameObject *recordedGO = new GameObject();
        recordedGO->AddComponent(new GameRecorder(*recordedGO));
        recordedGO->box.SetCenter(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2);
        state->AddObject(recordedGO);
    }
}

void GameRecorderButton::Render()
{
}

void GameRecorderButton::NotifyCollision(GameObject &other)
{
}

bool GameRecorderButton::Is(std::string type)
{
    return (type == GameRecorderButton::type);
}
