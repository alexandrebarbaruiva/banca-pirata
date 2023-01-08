/**
 * @file StageState.cpp
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief StageState class implementation file. Where happens the first part of the game.
 * @version 0.1
 * @date 2022-06-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "StageState.h"
#include "Sound.h"
#include "TileMap.h"
#include "Game.h"
#include "Text.h"
#include "Camera.h"
#include "InputManager.h"
#include "CameraFollower.h"
#include "Collision.cpp"
#include "TitleState.h"
#include "EndState.h"
#include "GameData.h"
#include "SaveHelper.h"
#include "ReputationArrow.h"

StageState::StageState(bool loadGame) : State(), backgroundMusic("assets/audio/chill.ogg")
{
	// Initialize game session variables
	int currentDay = 0;
	int currentMoney = 0;
	int currentRep = 0;
	int currentSus = 0;
	// SaveHelper::Save(currentDay, currentMoney, currentRep, currentSus);

	if (loadGame)
	{
		// Load from save file
		std::unordered_map<std::string, int> loadData = SaveHelper::Load();
		currentDay = loadData["dayInGame"];
		currentMoney = loadData["moneyInGame"];
		currentRep = loadData["repInGame"];
		currentSus = loadData["susInGame"];
#ifdef DEBUG
		std::cout << "loaded Day " << currentDay << "\n";
		std::cout << "loaded Money " << currentMoney << "\n";
		std::cout << "loaded Rep " << currentRep << "\n";
		std::cout << "loaded Sus " << currentSus << "\n";
#endif
	}

	// Background
	GameObject *bg = new GameObject();
	bg->AddComponent(new Sprite(*bg, "assets/img/placeholders/CenarioPixel.png", 1, 1.0));
	bg->AddComponent(new CameraFollower(*bg));
	bg->box.SetOrigin(0, 0);
	AddObject(bg);

	// HUD Dia + Dinheiro
	GameObject *hudGO = new GameObject();
	hudGO->AddComponent(new GameItem(*hudGO, "assets/img/placeholders/Tela 1-dia_dinheiro.png", 1, 1));
	hudGO->box.SetOrigin(0, 0);
	AddObject(hudGO);

	GameObject *dayHudText = new GameObject();
	dayHudText->AddComponent(new Text(*dayHudText, "assets/font/five.ttf", 40, Text::SOLID, ("Day " + std::to_string(currentDay)), {255, 255, 255, SDL_ALPHA_OPAQUE}));
	dayHudText->box.SetOrigin(115, 35);
	AddObject(dayHudText);

	GameObject *moneyHudText = new GameObject();
	moneyHudText->AddComponent(new Text(*moneyHudText, "assets/font/five.ttf", 40, Text::SOLID, ("R$ " + std::to_string(currentMoney)), {255, 255, 255, SDL_ALPHA_OPAQUE}));
	moneyHudText->box.SetOrigin(600, 35);
	AddObject(moneyHudText);

	// HUD Reputação
	GameObject *hudReputationGO2 = new GameObject();
	hudReputationGO2->AddComponent(new GameItem(*hudReputationGO2, "assets/img/placeholders/tela 1-Rep.png", 1, 1));
	hudReputationGO2->box.SetOrigin(960, 0);
	AddObject(hudReputationGO2);

	// HUD Seta da Reputação
	GameObject *hudReputationArrowGO = new GameObject();
	hudReputationArrowGO->AddComponent(new ReputationArrow(*hudReputationArrowGO, "assets/img/placeholders/tela 1-Rep_seta.png", currentRep, 1, 1));
	hudReputationArrowGO->box.SetOrigin(960, 60);
	AddObject(hudReputationArrowGO);

	// HUD Pause
	GameObject *hudPauseGO = new GameObject();
	hudPauseGO->AddComponent(new GameItem(*hudPauseGO, "assets/img/placeholders/Tela 1-Pause.png", 1, 1));
	hudPauseGO->box.SetOrigin(1800, 0);
	AddObject(hudPauseGO);

	// HUD Sirene 1
	GameObject *hudGOSirene1 = new GameObject();
	hudGOSirene1->AddComponent(new GameItem(*hudGOSirene1, "assets/img/placeholders/tela 1-sus-vazio.png", 1, 1));
	hudGOSirene1->box.SetOrigin(1800, 235);
	AddObject(hudGOSirene1);

	// HUD Sirene 2
	GameObject *hudGOSirene2 = new GameObject();
	hudGOSirene2->AddComponent(new GameItem(*hudGOSirene2, "assets/img/placeholders/tela 1-sus-vazio.png", 1, 1));
	hudGOSirene2->box.SetOrigin(1800, 355);
	AddObject(hudGOSirene2);

	// HUD Sirene 3
	GameObject *hudGOSirene3 = new GameObject();
	hudGOSirene3->AddComponent(new GameItem(*hudGOSirene3, "assets/img/placeholders/tela 1-sus-vazio.png", 1, 1));
	hudGOSirene3->box.SetOrigin(1800, 475);
	AddObject(hudGOSirene3);

	// HUD Sirene 4
	GameObject *hudGOSirene4 = new GameObject();
	hudGOSirene4->AddComponent(new GameItem(*hudGOSirene4, "assets/img/placeholders/tela 1-sus-vazio.png", 1, 1));
	hudGOSirene4->box.SetOrigin(1800, 595);
	AddObject(hudGOSirene4);

	// HUD Sirene 5
	GameObject *hudGOSirene5 = new GameObject();
	hudGOSirene5->AddComponent(new GameItem(*hudGOSirene5, "assets/img/placeholders/tela 1-sus.png", 1, 1));
	hudGOSirene5->box.SetOrigin(1800, 715);
	AddObject(hudGOSirene5);

	// Balcão
	GameObject *balcaoGO = new GameObject();
	balcaoGO->AddComponent(new GameItem(*balcaoGO, "assets/img/placeholders/balcão.png", 1, 1));
	balcaoGO->box.SetOrigin(0, 800);
	AddObject(balcaoGO);

	// Velho
	GameObject *velhoGO = new GameObject();
	velhoGO->AddComponent(new GameItem(*velhoGO, "assets/img/placeholders/velinho.png", 1, 1));
	velhoGO->box.SetOrigin(200, 320);
	AddObject(velhoGO);

	// GameObject *tileMap = new GameObject();
	// TileSet *tileSet = new TileSet(*tileMap, 64, 64, "assets/img/tileset.png");
	// tileMap->AddComponent(new TileMap(*tileMap, "assets/map/tileMap.txt", tileSet));
	// tileMap->box.x = 0;
	// tileMap->box.y = 0;
	// AddObject(tileMap);

	// GameObject *penguin = new GameObject();
	// PenguinBody *penguinBody = new PenguinBody(*penguin);
	// penguin->AddComponent(penguinBody);
	// penguin->box.x = 704;
	// penguin->box.y = 640;
	// AddObject(penguin);
	// Camera::Follow(penguin);

	// int newX;
	// int newY;

	// int maxAliens = (int)(((float)rand() / RAND_MAX) * (6 - 1) + 1);
	// float newOffset;
	// GameObject *alien;

	// for (int i = 0; i < maxAliens; i++)
	// {
	// 	alien = new GameObject();
	// 	newOffset = ((((float)rand()) / RAND_MAX) + i) / pow(10, i);
	// 	alien->AddComponent(new Alien(*alien, newOffset));
	// 	newX = (int)(((float)rand() / RAND_MAX) * (1340 + 40) - 40);
	// 	newY = (int)(((float)rand() / RAND_MAX) * (1280 + 10) - 10);
	// 	alien->box.x = newX - alien->box.w / 2;
	// 	alien->box.y = newY - alien->box.h / 2;
	// 	AddObject(alien);
	// }
}

StageState::~StageState()
{
	objectArray.clear();
}

void StageState::Start()
{
	LoadAssets();
	StartArray();
	backgroundMusic.Play();
	started = true;
}

void StageState::LoadAssets()
{
}

void StageState::Pause()
{
	backgroundMusic.Stop();
}

void StageState::Resume()
{
	backgroundMusic.Play();
}

void StageState::Update(float dt)
{
	// update camera
	Camera::Update(dt);

	InputManager input = InputManager::GetInstance();

	// check if quit was requested
	if (input.QuitRequested())
	{
		quitRequested = true;
	}

	if (input.KeyPress(ESCAPE_KEY))
	{
		this->Pause();
		popRequested = true;
	}

	if (input.MousePress(LEFT_MOUSE_BUTTON))
	{
#ifdef DEBUG
		std::cout << "X:" << input.GetMouseX() << " Y:" << input.GetMouseY() << "\n";
#endif
	}

	// Update every object
	UpdateArray(dt);

	srand(time(NULL));

	// check collidable objects
	// TODO: improve here
	// std::vector<std::weak_ptr<GameObject>> collidable = QueryObjectsByComponent("Collider");
	// for (unsigned i = 0; i < collidable.size(); i++)
	// {
	// 	for (unsigned j = i + 1; j < collidable.size(); j++)
	// 	{
	// 		if (Collision::IsColliding(collidable[i].lock()->box, collidable[j].lock()->box, collidable[i].lock()->angleDeg * PI / 180, collidable[j].lock()->angleDeg * PI / 180))
	// 		{
	// 			GameObject *g1 = collidable[i].lock().get();
	// 			GameObject *g2 = collidable[j].lock().get();
	// 			g1->NotifyCollision(*g2);
	// 			g2->NotifyCollision(*g1);
	// 		}
	// 	}
	// }

	// Check if object is dead
	// for (unsigned i = 0; i < objectArray.size(); i++)
	// {
	// 	if (objectArray[i]->IsDead())
	// 	{
	// 		objectArray.erase(objectArray.begin() + i);
	// 	}
	// }

	// if (Alien::alienCount <= 0)
	// {
	// 	GameData::playerVictory = true;
	// 	popRequested = true;
	// 	Game::GetInstance().Push(new EndState());
	// }

	// if (PenguinBody::player == nullptr)
	// {
	// 	GameData::playerVictory = false;
	// 	popRequested = true;
	// 	Game::GetInstance().Push(new EndState());
	// }
}

void StageState::Render()
{
	// Render every object
	RenderArray();
}
