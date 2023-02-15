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
#include <cstdlib>
#include <ctime>

/* save file */
bool GameData::playerVictory;
int GameData::currentMinute;
int GameData::currentHour;
int GameData::currentDay;
int GameData::currentMoney;
int GameData::currentRep;
int GameData::currentSus;
bool GameData::endDay;
std::vector<std::string> GameData::ownedGames;
bool GameData::menuRequested;

/* game functions */
bool GameData::clientCanLeave;
bool GameData::nextClient;

std::string GameData::currentClient;
int GameData::currentClientPos;
std::vector<std::string> GameData::currentClientGameTypes;

std::vector<std::string> GameData::clientNames{"emo1", "emo2", "emo3", "exe1", "exe2", "exe3", "pol1", "pol2", "pol3", "pol4"};
std::vector<std::string> GameData::allGames = {
    "dance",
    "fifa",
    "gta",
    "kirby",
    "mgear",
    "mkombat",
    "pokemon",
    "pwaa",
    "sims",
    "sonic",
};

std::vector<std::string> GameData::gameTypes = {
    "assustador",
    "casual",
    "descolado",
    "esportivo",
    "fofo",
    "inteligente",
    "musical",
    "narrativo",
    "radical",
    "violento",
};

std::map<std::string, std::vector<std::string>> GameData::gameAssetTypes = {
    {"dance", {"descolado", "esportivo", "musical"}},
    {"fifa", {"esportivo", "descolado", "radical"}},
    {"gta", {"radical", "violento", "descolado"}},
    {"kirby", {"casual", "fofo", "descolado"}},
    {"mgear", {"narrativo", "descolado", "violento"}},
    {"mkombat", {"assustador", "radical", "violento"}},
    {"pokemon", {"casual", "fofo", "esportivo"}},
    {"pwaa", {"inteligente", "narrativo", "descolado"}},
    {"sims", {"narrativo", "casual", "inteligente"}},
    {"sonic", {"esportivo", "radical", "casual"}},
};

/* game constant paths */
std::string BASE_ASSET_PATH = "assets/img/";
std::string TITLE_PATH = "assets/img/Titulo/";
std::string SCREEN1_PATH = "assets/img/Tela 1/";
std::string SCREEN2_PATH = "assets/img/Tela 2/";
std::string SCREEN3_PATH = "assets/img/Tela 3/";
std::string HUD_PATH = "assets/img/HUD/";
std::string GAMES_PATH = "assets/img/Jogos/";
std::string COVERS_PATH = "assets/img/Jogos/Capas/";
std::string ICONS_PATH = "assets/img/Jogos/Icones/";
std::string NPCS_PATH = "assets/img/NPCs/";
std::string DIALOGS_PATH = "assets/dialogs/";
std::string AUDIOS_PATH = "assets/audio/";
std::string FONTS_PATH = "assets/font/";

// TODO: change to allGames and start saving available games on save
std::string GameData::availableGames[10] = {"sonic", "fifa", "kirby", "mkombat", "pwaa", "dance", "gta", "mgear", "pokemon", "sims"};

// Save file has the following structure.
// Currently doesn't check for existing saved games.
// Will generate massive save file over time
//
// [SAVE {int}]
// timestamp: {timestamp}
// dayInGame: {int}
// gameVersion: {float}
//
void GameData::Save(int minuteInGame, int hourInGame, int dayInGame, int moneyInGame, int repInGame, int susInGame, std::vector<std::string> ownedGamesInGame)
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

    // TODO ownedGames save
    //  Write ownedGames
    saveFile << "ownedGamesInGame ";
    // for (std::string i: ownedGamesInGame)
    //{
    //     saveFile << i << " ";
    // }
    for (unsigned i = 0; i < ownedGamesInGame.size(); i++)
    {
        saveFile << ownedGamesInGame[i] << " ";
    }
    // saveFile << "\n";

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
    GameData::ownedGames = {"fifa", "kirby", "mgear"};

    GameData::clientCanLeave = false;
    GameData::nextClient = true;

    GameData::LoadClients();
}

void GameData::LoadClients()
{
    // get names from txt file
    // add to vector clients
    // set random client
    GameData::changeCurrentClient();
}

void GameData::changeCurrentClient()
{
    // set up next client
    srand(time(0));
    int newClient = rand() % GameData::clientNames.size();
    while (GameData::currentClientPos == newClient)
    {
        newClient = rand() % GameData::clientNames.size();
    }

    GameData::currentClient = GameData::clientNames.at(newClient);
}

void GameData::Load()
{
    std::ifstream saveFile("savegame");

    std::unordered_map<std::string, int> gameData;
    std::string name;
    std::stringstream jogos;
    int value;
    if (saveFile.is_open())
    {
        while (saveFile >> name >> value)
        {
            // std::cout << "Variavel : " << name << std::endl;
            gameData[name] = value;
        }
        jogos << saveFile.rdbuf();
        // std::cout << "Depois : " << jogos.str() << std::endl;
    }

    GameData::currentMinute = gameData["minuteInGame"];
    GameData::currentHour = gameData["hourInGame"];
    GameData::currentDay = gameData["dayInGame"];
    GameData::currentMoney = gameData["moneyInGame"];
    GameData::currentRep = gameData["repInGame"];
    GameData::currentSus = gameData["susInGame"];

    // Load ownedGames
    GameData::ownedGames.clear();
    std::string aux = "";
    for (unsigned i = 0; i < jogos.str().length(); ++i)
    {

        if (jogos.str()[i] == ' ')
        {
            GameData::ownedGames.push_back(aux);
            aux = "";
        }
        else
        {
            aux.push_back(jogos.str()[i]);
        }
    }
    GameData::ownedGames.push_back(aux);

    // TODO ownedGames Load

#ifdef DEBUG
    std::cout << "loaded Minute " << GameData::currentMinute << "\n";
    std::cout << "loaded Hour " << GameData::currentHour << "\n";
    std::cout << "loaded Day " << GameData::currentDay << "\n";
    std::cout << "loaded Money " << GameData::currentMoney << "\n";
    std::cout << "loaded Rep " << GameData::currentRep << "\n";
    std::cout << "loaded Sus " << GameData::currentSus << "\n";
#endif
}
