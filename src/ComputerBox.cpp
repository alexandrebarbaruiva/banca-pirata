/**
 * @file ComputerBox.cpp
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief ComputerBox class implementation file
 * @version 0.1
 * @date 2022-07-01
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "ComputerBox.h"
#include "GameAssetIcon.h"
#include <algorithm>
#include <string>

ComputerBox::ComputerBox(GameObject &associated) : Component(associated)
{
    selectedGameIcon = new GameObject();
    associated.AddComponent(new Collider(associated));
}

void ComputerBox::Start()
{
    State *state = &Game::GetInstance().GetCurrentState();

    GameObject *computerWindowGO = new GameObject();
    computerWindowGO->AddComponent(new Sprite(*computerWindowGO, "assets/img/placeholders/Tela2- Janela fundo.png"));
    computerWindowGO->box.SetOrigin(1150, 170);

    state->AddObject(computerWindowGO);

    // Icone pra mudar tela
    GameObject *iconeGO = new GameObject();
    iconeGO->AddComponent(new Sprite(*iconeGO, "assets/img/placeholders/tela2-Botao gravar hover.png"));
    iconeGO->box.SetOrigin(1655, 600);
    state->AddObject(iconeGO);

    ComputerBox::UpdateTab();
    ComputerBox::UpdateTabIcon();
    ComputerBox::UpdateGameIcon();
}

void ComputerBox::Update(float dt)
{
    State *state = &Game::GetInstance().GetCurrentState();
    std::string tabAsset = "assets/img/placeholders/Tela2- Janela aba";
    for (auto tabIcon : tabIconArray)
    {
        if (tabIcon.lock()->GetComponent("GameAssetIcon") != nullptr)
        {
            GameAssetIcon *tabAssetIcon = (GameAssetIcon *)tabIcon.lock()->GetComponent("GameAssetIcon");
            if (tabAssetIcon->isClicked)
            {
                tabAssetIcon->isClicked = false;
                this->changedTab = true;
                this->selectedTab = (int)((tabIcon.lock()->box.x - 1020) / 160);

                ComputerBox::UpdateTab();

                // Add selected tab to top
                GameObject *gameTabGO = new GameObject();
                gameTabGO->AddComponent(new Sprite(*gameTabGO, (tabAsset + std::to_string(this->selectedTab) + ".png")));
                gameTabGO->box.SetOrigin(1150, 170);
                tabArray.push_back(state->AddObject(gameTabGO));

                ComputerBox::UpdateGameIcon();
            }
        }
    }
    if (this->changedTab)
    {
        this->changedTab = false;
        ComputerBox::UpdateTabIcon();
    }

    for (auto gameIcon : gameIconArray)
    {
        if (gameIcon.lock()->GetComponent("GameAssetIcon") != nullptr)
        {
            GameAssetIcon *gameAssetIcon = (GameAssetIcon *)gameIcon.lock()->GetComponent("GameAssetIcon");
            if (gameAssetIcon->isClicked)
            {
                if (selectedGameIcon->GetComponent("Sprite") != nullptr)
                {
                    selectedGameIcon->RequestDelete();
                }

                gameAssetIcon->isClicked = false;
                // gameIconGO->box.SetOrigin(1170 + (125 * column), 270 + (150 * row));
                int gamePositionX = (int)((gameIcon.lock()->box.x - 1170) / 125);      // Alternates between 0, 1, 2, 3, 4 and 5
                int gamePositionY = (int)((gameIcon.lock()->box.y - 270) / (150 / 5)); // Alternates between 0 and 5
                this->selectedGame[this->selectedTab - 1] = gamePositionX + gamePositionY;

                selectedGameIcon = new GameObject();
                selectedGameIcon->AddComponent(new Sprite(*selectedGameIcon, "assets/img/placeholders/Seletor.png"));
                selectedGameIcon->box.SetCenter(gameIcon.lock()->box.Center());
                state->AddObject(selectedGameIcon);

                ComputerBox::UpdateTabIcon();
                ComputerBox::UpdateGameCover();
            }
        }
    }
}

void ComputerBox::UpdateTab()
{
    GameObject *gameTabGO;

    State *state = &Game::GetInstance().GetCurrentState();
    std::string tabAsset = "assets/img/placeholders/Tela2- Janela aba";

    for (auto tab : tabArray)
    {
        if (tab.lock() != nullptr)
        {
            tab.lock()->RequestDelete();
        }
    }
    tabArray.clear();

    for (int tab = 3; tab > 0; tab--)
    {
        gameTabGO = new GameObject();
        gameTabGO->AddComponent(new Sprite(*gameTabGO, tabAsset + std::to_string(tab) + ".png"));
        gameTabGO->box.SetOrigin(1150, 170);
        tabArray.push_back(state->AddObject(gameTabGO));
    }
}

void ComputerBox::UpdateTabIcon()
{
    GameObject *gameIconGO;
    std::string gameAsset;
    State *state = &Game::GetInstance().GetCurrentState();

    for (auto tabIcon : tabIconArray)
    {
        if (tabIcon.lock() != nullptr)
        {
            tabIcon.lock()->RequestDelete();
        }
    }
    tabIconArray.clear();

    for (int tab = 3; tab > 0; tab--)
    {
        gameAsset = "assets/img/placeholders/tela2-games/Icone-bloqueado.png";

        if (selectedGame[tab - 1] >= 0)
        {
            gameAsset = ("assets/img/placeholders/tela2-games/Icone-" + GameData::availableGames[selectedGame[tab - 1]] + ".png");
        }

        gameIconGO = new GameObject();
        gameIconGO->AddComponent(new GameAssetIcon(*gameIconGO, gameAsset));
        gameIconGO->box.SetOrigin(1020 + (160 * (tab)), 590);
        tabIconArray.push_back(state->AddObject(gameIconGO));
    }
}

void ComputerBox::UpdateGameIcon()
{
    GameObject *gameIconGO;
    std::string gameAsset;
    State *state = &Game::GetInstance().GetCurrentState();

    for (auto gameIcon : gameIconArray)
    {
        if (gameIcon.lock() != nullptr)
        {
            gameIcon.lock()->RequestDelete();
        }
    }
    gameIconArray.clear();

    for (int row = 0; row < 2; row++)
    {
        for (int column = 0; column < 5; column++)
        {
            gameAsset = ("assets/img/placeholders/tela2-games/Icone-" + GameData::availableGames[column + (row * 5)] + ".png");
            gameIconGO = new GameObject();
            gameIconGO->AddComponent(new GameAssetIcon(*gameIconGO, gameAsset));
            gameIconGO->box.SetOrigin(1170 + (125 * column), 270 + (150 * row));
            gameIconArray.push_back(state->AddObject(gameIconGO));
        }
    }
}

void ComputerBox::UpdateGameCover()
{
    GameObject *gameCoverGO;
    std::string gameAsset;
    State *state = &Game::GetInstance().GetCurrentState();

    for (auto gameCover : gameCoverArray)
    {
        if (gameCover.lock() != nullptr)
        {
            gameCover.lock()->RequestDelete();
        }
    }
    gameCoverArray.clear();

    for (int coverLayer = 0; coverLayer < 3; coverLayer++)
    {
        gameAsset = "assets/img/placeholders/tela2-games/Placeholder-IconesAssets1.png";

        if (selectedGame[coverLayer] >= 0)
        {
            gameAsset = ("assets/img/placeholders/Jogos/Asset-" +
                         GameData::availableGames[selectedGame[coverLayer]] +
                         "-" + coverOptions[coverLayer] +
                         ".png");
            gameCoverGO = new GameObject();
            gameCoverGO->AddComponent(new Sprite(*gameCoverGO, gameAsset));
            gameCoverGO->box.SetOrigin(780, 200);
            gameCoverArray.push_back(state->AddObject(gameCoverGO));
        }
    }
}

void ComputerBox::Render()
{
}

void ComputerBox::NotifyCollision(GameObject &other)
{
}

bool ComputerBox::Is(std::string type)
{
    return (type == ComputerBox::type);
}
