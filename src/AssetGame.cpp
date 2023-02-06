/**
 * @file AssetGame.cpp
 * @author João Paulo Vaz Mendes (170002934@aluno.unb.br)
 * @brief AssetGame class implementation file
 * @version 0.1
 * @date 2023-01-31
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "AssetGame.h"
#include "Text.h"

AssetGame::AssetGame(GameObject &associated, std::string game, std::string setCategory1,  std::string setCategory2, std::string setCategory3, int priceSet) : Component(associated) 
{
    price = priceSet;
    spriteName = "assets/img/Jogos/Capas combinadas/Capa " + game + ".png";
    category1 = setCategory1;
    category2 = setCategory2;
    category3 = setCategory3;

}

void AssetGame::Update(float dt)
{

}

void AssetGame::Render()
{
}

bool AssetGame::Is(std::string type)
{
    return (type == AssetGame::type);
}
