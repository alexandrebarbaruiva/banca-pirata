/**
 * @file Client.cpp
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief Client class implementation file
 * @version 0.1
 * @date 2022-07-01
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "Client.h"
#include "ChatBox.h"
#include "GameData.h"

Client::Client(GameObject &associated, std::string sprite, float scaleX, float scaleY, bool reachedEndpoint, float frameTime, int frameCount) : Component(associated)
{
    GameData::nextClient = false;
    Sprite *spriteItem = new Sprite(associated, sprite, frameCount, frameTime);
    this->endPoint = 710;
    this->speed = Vec2(600, 0);
#ifdef DEBUG
    this->speed = Vec2(600, 0);
#endif
    spriteItem->SetScale(scaleX, scaleY);
    associated.AddComponent(spriteItem);
    associated.AddComponent(new Collider(associated));
#ifdef DEBUG
    std::cout << "Client destination point on " << this->endPoint << "\n";
#endif
}

void Client::Update(float dt)
{
    if (this->currentPoint >= this->endPoint and not this->reachedEndpoint)
    {
        this->speed = this->speed * 0;
        Client::PopChat();
        this->reachedEndpoint = true;
        std::cout << "Reached endpoint.\n";
    }
    else if (GameData::clientCanLeave)
    {
        this->speed = Vec2(600, 0);
        if (this->currentPoint > GAME_SCREEN_WIDTH)
        {
            associated.RequestDelete();
            GameData::changeCurrentClient();
            GameData::clientCanLeave = false;
            GameData::nextClient = true;
        }
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

void Client::PopChat()
{
    GameObject *chatGO = new GameObject();
    chatGO->AddComponent(new ChatBox(*chatGO));
    chatGO->box.SetBottom(
        (associated.box.x),
        associated.box.y);
    Game::GetInstance().GetCurrentState().AddObject(chatGO);
}

void Client::Render()
{
}

void Client::NotifyCollision(GameObject &other)
{
}

bool Client::Is(std::string type)
{
    return (type == Client::type);
}
