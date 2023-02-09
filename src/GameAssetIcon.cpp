/**
 * @file GameAssetIcon.cpp
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief GameAssetIcon class implementation file
 * @version 0.1
 * @date 2022-07-01
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "GameAssetIcon.h"

GameAssetIcon::GameAssetIcon(GameObject &associated, std::string sprite, bool isClickable, bool isClicked, float scaleX, float scaleY, float frameTime, int frameCount) : Component(associated)
{
    this->isClickable = isClickable;
    this->isClicked = isClicked;
    Sprite *spriteItem = new Sprite(associated, sprite, frameCount, frameTime);
    spriteItem->SetScale(scaleX, scaleY);
    associated.AddComponent(spriteItem);
    associated.AddComponent(new Collider(associated));
}

void GameAssetIcon::Update(float dt)
{
    InputManager input = InputManager::GetInstance();
    if (input.MousePress(LEFT_MOUSE_BUTTON) and associated.box.IsInside(input.GetMousePosition()))
    {
        this->isClicked = true;
    }
}

void GameAssetIcon::Render()
{
}

void GameAssetIcon::NotifyCollision(GameObject &other)
{
}

bool GameAssetIcon::Is(std::string type)
{
    return (type == GameAssetIcon::type);
}
