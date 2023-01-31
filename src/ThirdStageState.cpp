/**
 * @file SecondStageState.cpp
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief SecondStageState class implementation file. Where happens the first part of the game.
 * @version 0.1
 * @date 2022-06-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "ThirdStageState.h"
#include "Constants.h"
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
#include "ReputationArrow.h"
#include "SirenBox.h"
#include "Client.h"

ThirdStageState::ThirdStageState() : State(), backgroundMusic("assets/audio/chill.ogg")
{
#ifdef DEBUG
	std::cout << "Loaded Second Screen\n";
#endif

	// Background
	GameObject *bg = new GameObject();
	bg->AddComponent(new Sprite(*bg, "assets/img/placeholders/Grade_Anim_Start.png", 1, 1.0));
	// bg->AddComponent(new CameraFollower(*bg));
	bg->box.SetOrigin(0, 0);
	AddObject(bg);

	// HUD Dia + Dinheiro
	GameObject *hudGO = new GameObject();
	hudGO->AddComponent(new GameItem(*hudGO, "assets/img/placeholders/Tela 1-dia_dinheiro.png", 1, 1));
	hudGO->box.SetOrigin(0, 0);
	AddObject(hudGO);

	GameObject *dayHudText = new GameObject();
	dayHudText->AddComponent(new Text(*dayHudText, "assets/font/five.ttf", 40, Text::SOLID, ("Day " + std::to_string(GameData::currentDay)), {255, 255, 255, SDL_ALPHA_OPAQUE}));
	dayHudText->box.SetOrigin(115, 35);
	AddObject(dayHudText);

	GameObject *moneyHudText = new GameObject();
	moneyHudText->AddComponent(new Text(*moneyHudText, "assets/font/five.ttf", 40, Text::SOLID, ("R$ " + std::to_string(GameData::currentMoney)), {255, 255, 255, SDL_ALPHA_OPAQUE}));
	moneyHudText->box.SetOrigin(500, 35);
	AddObject(moneyHudText);

	// HUD Reputação
	GameObject *hudReputationGO2 = new GameObject();
	hudReputationGO2->AddComponent(new GameItem(*hudReputationGO2, "assets/img/placeholders/tela 1-Rep.png", 1, 1));
	hudReputationGO2->box.SetOrigin(960, 0);
	AddObject(hudReputationGO2);

	// HUD Seta da Reputação
	GameObject *hudReputationArrowGO = new GameObject();
	hudReputationArrowGO->AddComponent(new ReputationArrow(*hudReputationArrowGO, "assets/img/placeholders/tela 1-Rep_seta.png", GameData::currentRep, 1, 1));
	hudReputationArrowGO->box.SetOrigin(960, 60);
	AddObject(hudReputationArrowGO);

	// HUD Pause
	GameObject *hudPauseGO = new GameObject();
	hudPauseGO->AddComponent(new GameItem(*hudPauseGO, "assets/img/placeholders/Tela 1-Pause.png", 1, 1));
	hudPauseGO->box.SetOrigin(1800, 0);
	AddObject(hudPauseGO);

	// HUD Sirene
	GameObject *hudGOSirene = new GameObject();
	hudGOSirene->AddComponent(new SirenBox(*hudGOSirene));
	hudGOSirene->box.SetOrigin(0, 355);
	AddObject(hudGOSirene);

	// Computador
	GameObject *computadorGO = new GameObject();
	computadorGO->AddComponent(new GameItem(*computadorGO, "assets/img/placeholders/Mesa_Tela2.png", 1, 1));
	computadorGO->box.SetOrigin(0, 0);
	AddObject(computadorGO);
	
	// Tela de Fundo do PC
	GameObject *fundoPcGO = new GameObject();
	fundoPcGO->AddComponent(new GameItem(*fundoPcGO, "assets/img/placeholders/Loja-fundo-site.png", 1, 0.97, false, 1, 1));
	fundoPcGO->box.SetOrigin(732, 160);
	AddObject(fundoPcGO);
	
	// Caixa HUD Sirene
	GameObject *caixaSireneGO = new GameObject();
	caixaSireneGO->AddComponent(new GameItem(*caixaSireneGO, "assets/img/placeholders/Loja-fundo-suspeita.png", 1, 1));
	caixaSireneGO->box.SetOrigin(-50, 330);
	AddObject(caixaSireneGO);

	// Capa simples placeholder
	GameObject *capaGO = new GameObject();
	capaGO->AddComponent(new GameItem(*capaGO, "assets/img/placeholders/capa-placeholder.png" ,0.8 ,0.8 ,false , 1, 1));
	capaGO->box.SetOrigin(800, 200);
	AddObject(capaGO);

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

ThirdStageState::~ThirdStageState()
{
	objectArray.clear();
}

void ThirdStageState::Start()
{
	LoadAssets();
	StartArray();
	backgroundMusic.Play();
	started = true;
}

void ThirdStageState::LoadAssets()
{
}

void ThirdStageState::Pause()
{
	backgroundMusic.Stop();
}

void ThirdStageState::Resume()
{
	backgroundMusic.Play();
}

void ThirdStageState::Update(float dt)
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

void ThirdStageState::Render()
{
	// Render every object
	RenderArray();
}
