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

AssetGame::AssetGame(GameObject &associated, std::string game, int priceSet) : Component(associated)
{
    price = priceSet;
    spriteName = COVERS_PATH + "Capa-" + game + ".png";
    name = game;
    category1 = GameData::gameAssetTypes[name][0];
    category2 = GameData::gameAssetTypes[name][1];
    category3 = GameData::gameAssetTypes[name][2];
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
