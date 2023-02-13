/**
 * @file Carrinho.cpp
 * @author João Paulo Vaz Mendes (170002934@aluno.unb.br)
 * @brief Carrinho class implementation file
 * @version 0.1
 * @date 2023-02-06
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "Carrinho.h"
#include "GameData.h"

Carrinho::Carrinho(GameObject &associated, AssetGame *gameBuying , float scaleX, float scaleY) : Component(associated)
{
    spriteItem = new Sprite(associated, "assets/img/placeholders/UI/Loja-compra.png");
    //spriteItemHoover = new Sprite(associated, "assets/img/placeholders/UI/Loja-compra-click.png");
    spriteScale = Vec2(scaleX,scaleY);
    spriteItem->SetScale(spriteScale);
    //spriteItemHoover->SetScale(spriteScale);
    associated.AddComponent(spriteItem);
    associated.AddComponent(new Collider(associated));
    this->gameToBuy = gameBuying;
    this->name = gameBuying->name;
    this->clickable = true;
    this->isClicked = false;
    this->clickedTimes= 0;
}

Carrinho::~Carrinho()
{
}

void Carrinho::Update(float dt)
{
    InputManager input = InputManager::GetInstance();
    if (input.MousePress(LEFT_MOUSE_BUTTON) and this->clickable)
    {
        bool mouseInButton = associated.box.IsInside(input.GetMousePosition());
        if (mouseInButton)
        {
            isClicked = true;
            clickedTimes++;
            //GameData::currentMoney -= gameToBuy->price;
            //std::cout << "Total na carteira: " << GameData::currentMoney << std::endl;
            //associated.RequestDelete();
        }
    }
}

void Carrinho::Choosed()
{
    spriteItemHoover = new Sprite(associated, "assets/img/placeholders/UI/Loja-compra-click.png");
    spriteItemHoover->SetScale(spriteScale);
    associated.AddComponent(spriteItemHoover);
    gameToBuy->gameChoosed = true;
    clickable = false;
}

void Carrinho::UnChoosed()
{
    if(clickedTimes > 0)
    {
        associated.RemoveComponent(spriteItemHoover);
    }
    gameToBuy->gameChoosed = false;
    clickable = true;
}

void Carrinho::Render()
{
}

void Carrinho::NotifyCollision(GameObject &other)
{
}

bool Carrinho::Is(std::string type)
{
    return (type == Carrinho::type);
}
