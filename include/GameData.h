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
#include <ctime>
#include <unordered_map>

class GameData
{
private:
    /* data */
public:
    static bool playerVictory;
    static int currentDay;
    static int currentMoney;
    static int currentRep;
    static int currentSus;

    /// @brief Utility to write save data to save file
    /// @param saveNumber save counter
    /// @param dayInGame day in game when save method was called
    /// @param dayInGame money in game when save method was called
    static void Save(int dayInGame, int moneyInGame, int repInGame, int susInGame);

    static void Reset();

    static void Load();
};

#endif
