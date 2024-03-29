/**
 * @file GameRecorder.cpp
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief GameRecorder class implementation file
 * @version 0.1
 * @date 2022-07-01
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "GameRecorder.h"
#include "GameData.h"
#include "Sound.h"

GameRecorder::GameRecorder(GameObject &associated, std::string sprite, float scaleX, float scaleY, int frameCount, float frameTime, float secondsToSelfDestruct) : Component(associated)
{
    GameData::recordingGame = true;
    Sound *sound = new Sound(associated, (AUDIOS_PATH + "cdRecorder.ogg"));
    sound->Play();

    Sprite *spriteItem = new Sprite(associated, sprite, frameCount, frameTime, secondsToSelfDestruct);
    spriteItem->SetScale(scaleX, scaleY);
    associated.AddComponent(spriteItem);
    associated.AddComponent(new Collider(associated));
}

GameRecorder::~GameRecorder()
{
    GameData::currentMoney += (GameData::moneyInDay * GameData::currentRep / 100);
    GameData::currentRep += GameData::repInDay;
    if (GameData::currentRep > 100)
    {
        GameData::currentRep = 100;
    }

    State *state = &Game::GetInstance().GetCurrentState();
    state->RequestPop();
    GameData::recordingGame = false;
}

void GameRecorder::Update(float dt)
{
    if (not this->recorded)
    {
        this->recorded = true;
        State *state = &Game::GetInstance().GetCurrentState();
        std::vector<std::weak_ptr<GameObject>> cbs = state->QueryObjectsByComponent("ComputerBox");
        int selectedGame[3];
        for (unsigned i = 0; i < cbs.size(); i++)
        {
            ComputerBox *computerBox = ((ComputerBox *)(cbs[i].lock()->GetComponent("ComputerBox")));
            std::copy(computerBox->selectedGame, computerBox->selectedGame + 3, selectedGame);
        }
        std::vector<std::string> clientGameTypes = GameData::currentClientGameTypes;

        bool playCop = false;

        if (GameData::currentClient.substr(0, 3) == "pol" and ((selectedGame[0] != selectedGame[1]) or
                                                               (selectedGame[0] != selectedGame[2]) or
                                                               (selectedGame[1] != selectedGame[2])))
        {
            playCop = true;
            std::cout << "GANHOU SUSPEITA, EITAAA\n";
            GameData::currentSus += 20;
        }

        int moneyToAdd = 0;
        int repToAdd = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < (int)clientGameTypes.size(); j++)
            {
                std::string chosenGameType = GameData::gameAssetTypes[GameData::availableGames[selectedGame[i]]][i];
                if (chosenGameType == clientGameTypes[j])
                {
                    moneyToAdd += 10;
                    repToAdd += 1;
                    clientGameTypes.erase(clientGameTypes.begin() + j);
                    break;
                }
            }
        }
        repToAdd -= clientGameTypes.size();

        GameData::moneyInDay += moneyToAdd;
        GameData::repInDay += repToAdd;

#ifdef DEBUG
        std::cout << "DINHEIRO: " << moneyToAdd << "\n";
        std::cout << "REPUTAÇÂO: " << repToAdd << "\n";
        std::cout << "ERROS: " << clientGameTypes.size() << "\n";
#endif
        if (playCop)
        {
            GameObject *susSoundGO = new GameObject();
            Sound *susSound = new Sound(*susSoundGO, AUDIOS_PATH + "susRise.ogg");
            susSound->Play();
        }
    }
}

void GameRecorder::Render()
{
}

void GameRecorder::NotifyCollision(GameObject &other)
{
}

bool GameRecorder::Is(std::string type)
{
    return (type == GameRecorder::type);
}
