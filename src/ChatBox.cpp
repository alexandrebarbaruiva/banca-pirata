/**
 * @file ChatBox.cpp
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief ChatBox class implementation file
 * @version 0.1
 * @date 2022-07-01
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "ChatBox.h"
#include "SecondStageState.h"

ChatBox::ChatBox(GameObject &associated, bool clickable, std::string sprite, float scaleX, float scaleY, float frameTime, int frameCount) : Component(associated)
{
    Sprite *spriteItem = new Sprite(associated, sprite, frameCount, frameTime);
    spriteItem->SetScale(scaleX, scaleY);
    associated.AddComponent(spriteItem);
#ifdef DEBUG
    associated.AddComponent(new Collider(associated));
    std::cout << "Chat box created\n";
#endif
}

void ChatBox::Update(float dt)
{
    InputManager input = InputManager::GetInstance();
    if (input.MousePress(LEFT_MOUSE_BUTTON) and associated.box.IsInside(input.GetMousePosition()))
    {
        associated.RequestDelete();
        this->isClicked = true;

        // Create Screen 2 here
        State *stage = new SecondStageState();
        Game::GetInstance().Push(stage);
    }
}

void ChatBox::Render()
{
}

void ChatBox::NotifyCollision(GameObject &other)
{
}

bool ChatBox::Is(std::string type)
{
    return (type == ChatBox::type);
}
