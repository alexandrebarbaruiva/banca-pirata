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
int GameData::currentMinute;
int GameData::currentHour;
int GameData::currentDay;
int GameData::currentMoney;
int GameData::currentRep;
int GameData::currentSus;
bool GameData::endDay;
std::vector<std::string> GameData::ownedGames;

// Save file has the following structure.
// Currently doesn't check for existing saved games.
// Will generate massive save file over time
//
// [SAVE {int}]
// timestamp: {timestamp}
// dayInGame: {int}
// gameVersion: {float}
//
void GameData::Save(int minuteInGame, int hourInGame, int dayInGame, int moneyInGame, int repInGame, int susInGame)
{
    // Append to file
    // std::ofstream SaveFile("savegame", std::ios::app);

    // Write to file
    std::ofstream saveFile("savegame");

    // Write minuteInGame
    saveFile << "minuteInGame " << minuteInGame;
    saveFile << "\n";

    // Write hourInGame
    saveFile << "hourInGame " << hourInGame;
    saveFile << "\n";

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

    //TODO ownedGames save

    saveFile.close();
}

void GameData::Reset()
{
    GameData::currentMinute = 0;
    GameData::currentHour = 8;
    GameData::currentDay = 1;
    GameData::currentMoney = 0;
    GameData::currentRep = 50;
    GameData::currentSus = 0;
    GameData::ownedGames.clear();
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

    GameData::currentMinute = gameData["minuteInGame"];
    GameData::currentHour = gameData["hourInGame"];
    GameData::currentDay = gameData["dayInGame"];
    GameData::currentMoney = gameData["moneyInGame"];
    GameData::currentRep = gameData["repInGame"];
    GameData::currentSus = gameData["susInGame"];
    //TODO ownedGames Load

#ifdef DEBUG
    std::cout << "loaded Minute " << GameData::currentMinute << "\n";
    std::cout << "loaded Hour " << GameData::currentHour << "\n";
    std::cout << "loaded Day " << GameData::currentDay << "\n";
    std::cout << "loaded Money " << GameData::currentMoney << "\n";
    std::cout << "loaded Rep " << GameData::currentRep << "\n";
    std::cout << "loaded Sus " << GameData::currentSus << "\n";
#endif
}
