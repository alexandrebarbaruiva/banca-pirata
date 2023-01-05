/**
 * @file SaveHelper.h
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief SaveHelper class header file
 * @version 0.1
 * @date 2022-07-11
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef SAVEHELPER_HEADER
#define SAVEHELPER_HEADER
#include <iostream>
#include <fstream>
#include <ctime>
#include <unordered_map>

class SaveHelper
{
public:
    /// @brief Utility to write save data to save file
    /// @param saveNumber save counter
    /// @param dayInGame day in game when save method was called
    /// @param dayInGame money in game when save method was called
    static void Save(int dayInGame, int moneyInGame, int repInGame, int susInGame);

    static std::unordered_map<std::string, int> Load();
};

#endif
