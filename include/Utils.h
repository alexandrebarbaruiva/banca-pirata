/**
 * @file Utils.h
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief Utils class header file
 * @version 0.1
 * @date 2022-07-11
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef UTILS_HEADER
#define UTILS_HEADER
#include <iostream>
#include <fstream>
#include <ctime>

class Utils
{
public:
    /// @brief Utility to write save data to save file
    /// @param saveNumber save counter
    /// @param dayInGame day in game when save method was called
    static void Save(int saveNumber, int dayInGame);
};

#endif
