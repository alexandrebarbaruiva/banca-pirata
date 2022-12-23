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
void SaveHelper::Save(int saveNumber, int dayInGame)
{
    std::ofstream SaveFile("savegame", std::ios::app);

    // Write header
    SaveFile << "\n[SAVE " << saveNumber << "]\n";

    // Timestamp
    // https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
    // current date/time based on current system
    std::time_t now = time(0);

    // convert now to string form
    char *timestamp = ctime(&now);

    // convert now to tm struct for UTC
    tm *gmtm = gmtime(&now);
    timestamp = asctime(gmtm);

    // Write timestamp
    SaveFile << "timestamp: " << timestamp;

    // Write dayInGame
    SaveFile << "dayInGame: " << dayInGame;

    SaveFile << "\n";

    SaveFile.close();
}
