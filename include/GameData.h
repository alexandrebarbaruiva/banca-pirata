/**
 * @file GameData.h
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief GameData class header file
 * @version 0.1
 * @date 2022-07-01
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef GAMEDATA_HEADER
#define GAMEDATA_HEADER
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <unordered_map>
#include <vector>
#include <map>

class GameData
{
private:
    /* data */
public:
    /* save file */
    static bool playerVictory;
    static int currentMinute;
    static int currentHour;
    static int currentDay;
    static int currentMoney;
    static int currentRep;
    static int currentSus;
    static bool endDay;
    static std::vector<std::string> ownedGames;
    static bool menuRequested;
    static bool playerArrested;

    /* game functions */
    static bool clientCanLeave;
    static bool nextClient;

    static std::string currentClient;
    static int currentClientPos;
    static std::vector<std::string> currentClientGameTypes;

    /* constants */
    // All client variations
    static std::vector<std::string> clientNames;
    // All available games
    static std::string availableGames[10];
    static std::vector<std::string> allGames;
    static std::vector<std::string> gameTypes;
    static std::map<std::string, std::vector<std::string>> gameAssetTypes;

    /// @brief Utility to write save data to save file
    /// @param saveNumber save counter
    /// @param dayInGame day in game when save method was called
    /// @param dayInGame money in game when save method was called
    static void Save(int minuteInGame, int hourInGame, int dayInGame, int moneyInGame, int repInGame, int susInGame, std::vector<std::string> ownedGamesInGame);

    static void Reset();

    static void LoadClients();

    static void changeCurrentClient();

    static void Load();
};

#endif
