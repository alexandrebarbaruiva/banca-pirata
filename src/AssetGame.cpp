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

    if(game == "sonic")
    {
        category1 = "Radical";
        category2 = "Casual";
        category3 = "Esportivo";
    }
    else if(game == "sims")
    {
        category1 = "Casual";
        category2 = "Inteligente";
        category3 = "Narrativo";
    }
    else if(game == "gta")
    {
        category1 = "Violento";
        category2 = "Deslocado";
        category3 = "Radical";
    }
    else if(game == "dance")
    {
        category1 = "Esportivo";
        category2 = "Musical";
        category3 = "Deslocado";
    }
    else if(game == "mkombat")
    {
        category1 = "Radical";
        category2 = "Violento";
        category3 = "Assustador";
    }
    else if(game == "kirby")
    {
        category1 = "Fofo";
        category2 = "Descolado";
        category3 = "Casual";
    }
    else if(game == "pwaa")
    {
        category1 = "Narrativo";
        category2 = "Descolado";
        category3 = "Inteligente";
    }
    else if(game == "fifa")
    {
        category1 = "Descolado";
        category2 = "Radical";
        category3 = "Esportivo";
    }
    else if(game == "mgear")
    {
        category1 = "Descolado";
        category2 = "Violento";
        category3 = "Narrativo";
    }
    else if(game == "pokemon")
    {
        category1 = "Fofo";
        category2 = "Esportivo";
        category3 = "Casual";
    }
    else
    {
        category1 = "Indisponivel";
        category2 = "Indisponivel";
        category3 = "Indisponivel";
    }
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
