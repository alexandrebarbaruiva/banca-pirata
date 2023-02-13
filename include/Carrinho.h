/**
 * @file Carrinho.h
 * @author João Paulo Vaz Mendes (170002934@aluno.unb.br)
 * @brief Carrinho class header file
 * @version 0.1
 * @date 2023-02-06
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef CARRINHO_HEADER
#define CARRINHO_HEADER
#include "Component.h"
#include "Sprite.h"
#include "Collider.h"
#include "AssetGame.h"
#include "Vec2.h"

class Carrinho : public Component
{
private:
public:
    Carrinho(GameObject &associated, AssetGame *gameBuying ,float scaleX = 1, float scaleY = 1);
    ~Carrinho();

    std::string type = "Carrinho";
    std::string name;

    Sprite *spriteItem;
    Sprite *spriteItemHoover;
    Vec2 spriteScale;

    AssetGame *gameToBuy;

    bool clickable;
    bool isClicked;
    int clickedTimes = 0;

    void Choosed();
    void UnChoosed();

    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void NotifyCollision(GameObject &other);
};

#endif
