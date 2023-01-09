/**
 * @file GameData.cpp
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief GameData class implementation file
 * @version 0.1
 * @date 2022-06-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "GameData.h"

bool GameData::playerVictory;
int GameData::currentDay;
int GameData::currentMoney;
int GameData::currentRep;
int GameData::currentSus;

// Save file has the following structure.
// Currently doesn't check for existing saved games.
// Will generate massive save file over time
//
// [SAVE {int}]
// timestamp: {timestamp}
// dayInGame: {int}
// gameVersion: {float}
//
void GameData::Save(int dayInGame, int moneyInGame, int repInGame, int susInGame)
{
    // Append to file
    // std::ofstream SaveFile("savegame", std::ios::app);

    // Write to file
    std::ofstream saveFile("savegame");

    // Write dayInGame
    saveFile << "dayInGame " << dayInGame;
    saveFile << "\n";

    // Write moneyInGame
    saveFile << "moneyInGame " << moneyInGame;
    saveFile << "\n";

    // Write moneyInGame
    saveFile << "repInGame " << repInGame;
    saveFile << "\n";

    // Write moneyInGame
    saveFile << "susInGame " << susInGame;
    saveFile << "\n";

    saveFile.close();
}

void GameData::Load()
{
    std::ifstream saveFile("savegame");

    std::unordered_map<std::string, int> gameData;
    std::string name;
    int value;
    if (saveFile.is_open())
    {
        while (saveFile >> name >> value)
        {
            gameData[name] = value;
        }
    }

    GameData::currentDay = gameData["dayInGame"];
    GameData::currentMoney = gameData["moneyInGame"];
    GameData::currentRep = gameData["repInGame"];
    GameData::currentSus = gameData["susInGame"];

#ifdef DEBUG
    std::cout << "loaded Day " << GameData::currentDay << "\n";
    std::cout << "loaded Money " << GameData::currentMoney << "\n";
    std::cout << "loaded Rep " << GameData::currentRep << "\n";
    std::cout << "loaded Sus " << GameData::currentSus << "\n";
#endif
}
