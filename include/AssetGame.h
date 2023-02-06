/**
 * @file AssetGame.h
 * @author João Paulo Vaz Mendes (170002934@aluno.unb.br)
 * @brief AssetGame class header file
 * @version 0.1
 * @date 2022-01-31
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef ASSETGAME_HEADER
#define ASSETGAME_HEADER
#include "Component.h"
#include "Sprite.h"
#include "Vec2.h"

class AssetGame : public Component
{
private:
public:
    AssetGame(GameObject &associated, std::string game, std::string setCategory1,  std::string setCategory2, std::string setCategory3, int priceSet);

    enum Game {
        dance=1,
        fifa=2,
        gta=3,
        kirby=4,
        MGear=5,
        MKombat=6,
        pokemon=7,
        PWAA=8,
        sims=9,
        sonic=0
    };

    Game gameName;


    std::string type = "AssetGame";
    std::string name;
    std::string spriteName;
    std::string category1;
    std::string category2;
    std::string category3;

    int price;


    bool clickable = false;
    bool isClicked = false;

    void Update(float dt);
    void Render();
    bool Is(std::string type);

};

#endif
