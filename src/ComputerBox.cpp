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
#include "GameData.h"
#include "GameRecorderButton.h"
#include "Text.h"
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
    computerWindowGO->AddComponent(new Sprite(*computerWindowGO, SCREEN2_PATH + "Tela2- Janela fundo.png"));
    computerWindowGO->box.SetOrigin(1150, 170);
    state->AddObject(computerWindowGO);

    // Icone pra mudar tela
    gameRecorderButton = new GameObject();
    gameRecorderButton->AddComponent(new GameRecorderButton(*gameRecorderButton));
    gameRecorderButton->box.SetOrigin(1655, 600);
    state->AddObject(gameRecorderButton);

    ComputerBox::UpdateTab();
    ComputerBox::UpdateTabIcon();
    ComputerBox::UpdateGameIcon();
}

void ComputerBox::Update(float dt)
{
    State *state = &Game::GetInstance().GetCurrentState();
    std::string tabAsset = SCREEN2_PATH + "Tela2- Janela aba";

    // GameTab is clicked
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
                ComputerBox::UpdateGameSelector();
            }
        }
    }
    if (this->changedTab)
    {
        this->changedTab = false;
        ComputerBox::UpdateTabIcon();
    }

    // GameIcon is clicked
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
                this->selectedGamePosition[this->selectedTab - 1] = gameIcon.lock()->box.Center();

                ComputerBox::UpdateGameSelector();
                ComputerBox::UpdateTabIcon();
                ComputerBox::UpdateGameCover();
                ComputerBox::UpdateGameText();
            }
        }
    }
    if (this->selectedGame[0] != -1 and this->selectedGame[1] != -1 and this->selectedGame[2] != -1)
    {
        if (gameRecorderButton->GetComponent("GameRecorderButton"))
        {
            GameRecorderButton *grButton = (GameRecorderButton *)gameRecorderButton->GetComponent("GameRecorderButton");
            grButton->clickable = true;
        }
    }
}

void ComputerBox::UpdateTab()
{
    GameObject *gameTabGO;

    State *state = &Game::GetInstance().GetCurrentState();
    std::string tabAsset = SCREEN2_PATH + "Tela2- Janela aba";

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
        gameAsset = ICONS_PATH + "Icone-bloqueado.png";

        if (selectedGame[tab - 1] >= 0)
        {
            gameAsset = (ICONS_PATH + "Icone-" + GameData::availableGames[selectedGame[tab - 1]] + ".png");
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
            gameAsset = ICONS_PATH + "Icone-bloqueado.png";
            bool isClickable = false;

            for (int i = 0; i < (int)GameData::ownedGames.size(); i++)
            {
                if (GameData::availableGames[column + (row * 5)] == GameData::ownedGames.at(i))
                {
                    gameAsset = (ICONS_PATH + "Icone-" + GameData::availableGames[column + (row * 5)] + ".png");
                    isClickable = true;
                }
            }
            gameIconGO = new GameObject();
            gameIconGO->AddComponent(new GameAssetIcon(*gameIconGO, gameAsset, isClickable));
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
        if (selectedGame[coverLayer] >= 0)
        {
            gameAsset = (GAMES_PATH + "Asset-" +
                         GameData::availableGames[selectedGame[coverLayer]] +
                         "-" + coverOptions[coverLayer] +
                         ".png");
            gameCoverGO = new GameObject();
            gameCoverGO->AddComponent(new Sprite(*gameCoverGO, gameAsset));
            gameCoverGO->box.SetOrigin(780, 180);
            gameCoverArray.push_back(state->AddObject(gameCoverGO));
        }
    }
}

void ComputerBox::UpdateGameText()
{
    GameObject *dialogTextGO;
    std::string gameText = "";
    State *state = &Game::GetInstance().GetCurrentState();

    for (auto dialogText : gameTextArray)
    {
        if (dialogText.lock() != nullptr)
        {
            dialogText.lock()->RequestDelete();
        }
    }
    gameTextArray.clear();

    for (int row = 0; row < 3; row++)
    {
        if (selectedGame[row] != -1)
        {
            gameText = GameData::gameAssetTypes[GameData::availableGames[selectedGame[row]]][row];
            dialogTextGO = new GameObject();
            dialogTextGO->AddComponent(new Text(*dialogTextGO, "assets/font/up.ttf", 30, Text::BLENDED, gameText, {255, 255, 255, SDL_ALPHA_OPAQUE}, 200));
            dialogTextGO->box.SetOrigin(780, 620 + (40 * row));
            gameTextArray.push_back(state->AddObject(dialogTextGO));
        }
    }
}

void ComputerBox::UpdateGameSelector()
{
    if (selectedTab > 0 and (selectedGamePosition[selectedTab - 1] != Vec2(0, 0)))
    {
        State *state = &Game::GetInstance().GetCurrentState();

        selectedGameIcon = new GameObject();
        selectedGameIcon->AddComponent(new Sprite(*selectedGameIcon, SCREEN2_PATH + "tela2-Seletor.png"));
        selectedGameIcon->box.SetCenter(selectedGamePosition[selectedTab - 1]);

        state->AddObject(selectedGameIcon);
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
