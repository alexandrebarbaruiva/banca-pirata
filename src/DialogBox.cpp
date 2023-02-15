/**
 * @file DialogBox.cpp
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief DialogBox class implementation file
 * @version 0.1
 * @date 2022-07-01
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "DialogBox.h"
#include "SecondStageState.h"
#include "GameData.h"

DialogBox::DialogBox(GameObject &associated) : Component(associated)
{
    associated.AddComponent(new Sprite(associated, SCREEN2_PATH + "tela2-caixa de dialogo.png"));
    associated.box.SetBottom(0, GAME_SCREEN_HEIGHT);

#ifdef DEBUG
    associated.AddComponent(new Collider(associated));
    std::cout << "Chat box created\n";
#endif
}

void DialogBox::Start()
{
    State *state = &Game::GetInstance().GetCurrentState();

    dialogText = new GameObject();
    Text *text = new Text(*dialogText, "assets/font/up.ttf", 50, Text::BLENDED, "A", {255, 255, 255, SDL_ALPHA_OPAQUE}, GAME_SCREEN_WIDTH - GAME_SCREEN_WIDTH / 8);
    text->SetText(DialogBox::GetCurrentDialog(), DialogBox::GetCurrentGameTypes());
    dialogText->AddComponent(text);
    dialogText->box.SetCenter(GAME_SCREEN_WIDTH / 2, (GAME_SCREEN_HEIGHT - GAME_SCREEN_HEIGHT / 7));
    state->AddObject(dialogText);
}

DialogBox::~DialogBox()
{
    dialogText->RequestDelete();
}

std::string DialogBox::GetCurrentDialog()
{
    std::ifstream dialogFile(DIALOGS_PATH + GameData::currentClient.substr(0, 3) + ".txt");
    std::string line;
    std::vector<std::string> dialogOptions;
    while (std::getline(dialogFile, line))
    {
        dialogOptions.emplace_back(line);
    }
    std::string chosenDialog = dialogOptions.at(rand() % dialogOptions.size());
    return chosenDialog;
}

std::string DialogBox::GetCurrentGameTypes()
{
    GameData::currentClientGameTypes.clear();
    std::string currentGameTypes = "";
    if (GameData::currentClient.substr(0, 3) == "pol")
    {
        std::string chosenGame = GameData::allGames.at(rand() % GameData::allGames.size());
        for (int i = 0; i < 3; i++)
        {
            GameData::currentClientGameTypes.push_back(GameData::gameAssetTypes[chosenGame][i]);
            currentGameTypes = (GameData::gameAssetTypes[chosenGame][i] + " ") + currentGameTypes;
        }
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            std::string gameType = GameData::gameTypes.at(rand() % GameData::gameTypes.size());
            GameData::currentClientGameTypes.push_back(gameType);
            currentGameTypes += (gameType + " ");
        }
    }

    return currentGameTypes;
}

void DialogBox::Update(float dt)
{
}

void DialogBox::Render()
{
}

void DialogBox::NotifyCollision(GameObject &other)
{
}

bool DialogBox::Is(std::string type)
{
    return (type == DialogBox::type);
}
