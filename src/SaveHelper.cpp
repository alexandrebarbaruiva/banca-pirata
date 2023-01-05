/**
 * @file SaveHelper.cpp
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief SaveHelper class implementation file
 * @version 0.1
 * @date 2022-07-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "SaveHelper.h"

// Save file has the following structure.
// Currently doesn't check for existing saved games.
// Will generate massive save file over time
//
// [SAVE {int}]
// timestamp: {timestamp}
// dayInGame: {int}
// gameVersion: {float}
//
void SaveHelper::Save(int dayInGame, int moneyInGame, int repInGame, int susInGame)
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

std::unordered_map<std::string, int> SaveHelper::Load()
{
    std::ifstream saveFile("savegame");

    std::unordered_map<std::string, int> gameData;
    std::string name;
    int value;
    if (saveFile.is_open())
    {
        while (saveFile >> name >> value)
        {
            std::cout << name << " "<< value << "\n";
            gameData[name] = value;
        }
        
    }
    return gameData;
}
