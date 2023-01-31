/**
 * @file ChangeScreen.cpp
 * @author João Paulo Vaz Mendes(170002934@aluno.unb.br)
 * @brief ChangeScreen class implementation file
 * @version 0.1
 * @date 2023-01-28
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "ChangeScreen.h"

ChangeScreen::ChangeScreen(GameObject &associated, bool clickable, std::string sprite, float scaleX, float scaleY, float frameTime, int frameCount) : Component(associated)
{
    Sprite *spriteItem = new Sprite(associated, sprite, frameCount, frameTime);
    spriteItem->SetScale(scaleX, scaleY);
    associated.AddComponent(spriteItem);
    std::cout << "Criou Icone" << std::endl;
#ifdef DEBUG
    associated.AddComponent(new Collider(associated));
    std::cout << "Chat box created\n";
#endif
}

void ChangeScreen::Update(float dt)
{
    InputManager input = InputManager::GetInstance();
    if (input.MousePress(LEFT_MOUSE_BUTTON) and associated.box.IsInside(input.GetMousePosition()))
    {
        std::cout << "Clicou Icone" << std::endl;
        associated.RequestDelete();
        this->isClicked = true;

        // Create Screen 3 here
        State *stage = new ThirdStageState();
        Game::GetInstance().Push(stage);
    }
}

void ChangeScreen::Render()
{
}

void ChangeScreen::NotifyCollision(GameObject &other)
{
}

bool ChangeScreen::Is(std::string type)
{
    return (type == ChangeScreen::type);
}
