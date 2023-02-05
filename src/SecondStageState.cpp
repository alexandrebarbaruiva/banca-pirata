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
#include "SecondStageState.h"
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
#include "Client.h"
#include "Calendar.h"
#include "ChangeScreen.h"

SecondStageState::SecondStageState() : State(), backgroundMusic("assets/audio/chill.ogg")
{
#ifdef DEBUG
	std::cout << "Loaded Second Screen\n";
#endif
	// Background
	GameObject *bg = new GameObject();
	bg->AddComponent(new Sprite(*bg, "assets/img/placeholders/Tela2-ui.png", 1, 1.0));
	bg->box.SetOrigin(0, 0);
	AddObject(bg);

	GameObject *chatText = new GameObject();
	Text *text = new Text(*chatText, "assets/font/up.ttf", 50, Text::BLENDED, "TESTE", {255, 255, 255, SDL_ALPHA_OPAQUE}, GAME_SCREEN_WIDTH - GAME_SCREEN_WIDTH / 8);
	text->SetText("Opa meu bacano, me ve um jogo de %s %s e %s Ah, voce tem troco pra nota de 100?", "suspense, luta aventura?");
	chatText->AddComponent(text);
	chatText->box.SetCenter(GAME_SCREEN_WIDTH / 2, (GAME_SCREEN_HEIGHT - GAME_SCREEN_HEIGHT / 6));
	AddObject(chatText);

	// HUD Dia + Dinheiro
	GameObject *hudGO = new GameObject();
	hudGO->AddComponent(new GameItem(*hudGO, "assets/img/placeholders/Tela 1-dia_dinheiro.png", 1, 1));
	hudGO->box.SetOrigin(0, 0);
	AddObject(hudGO);

	GameObject *dayHudText = new GameObject();
	dayHudText->AddComponent(new Calendar(*dayHudText, GameData::currentDay));
	dayHudText->box.SetOrigin(115, 35);
	AddObject(dayHudText);

	GameObject *timeHudText = new GameObject();
	stageClock = new Clock(*timeHudText, GameData::currentHour, GameData::currentMinute);
	timeHudText->AddComponent(stageClock);
	timeHudText->box.SetOrigin(300, 35);
	AddObject(timeHudText);

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

	// Cliente frontal
	GameObject *clienteGO = new GameObject();
	clienteGO->AddComponent(new GameItem(*clienteGO, "assets/img/placeholders/cliente_placeholder.png", 1, 1));
	clienteGO->box.SetOrigin(120, 300);
	AddObject(clienteGO);

	// Capa simples placeholder
	GameObject *capaGO = new GameObject();
	capaGO->AddComponent(new GameItem(*capaGO, "assets/img/placeholders/capa-placeholder.png", 1, 1));
	capaGO->box.SetOrigin(800, 200);
	AddObject(capaGO);

	//Grade fechando a loja
	gradeGO = new GameObject();	
	gradeGO->AddComponent(new Sprite(*gradeGO, "assets/img/placeholders/Grade_Anim_Start.png", 1, 1.0));
	gradeGO->box.SetOrigin(0, -1080);
	AddObject(gradeGO);

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

SecondStageState::~SecondStageState()
{
	objectArray.clear();
}

void SecondStageState::Start()
{
	LoadAssets();
	StartArray();
	backgroundMusic.Play();
	started = true;
}

void SecondStageState::LoadAssets()
{
}

void SecondStageState::Pause()
{
	backgroundMusic.Stop();
}

void SecondStageState::Resume()
{
	backgroundMusic.Play();
}

void SecondStageState::Update(float dt)
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

	//Mecanismo para terminar o dia
	Vec2 speed = Vec2(0,600);

	if(GameData::currentHour == 17 && GameData::currentMinute == 59)
	{
		stageClock->Pause();
		if(gradeGO->box.y <= 0) 
		{
			gradeGO->box = gradeGO->box + (speed * dt);
		}
		else
		{
        	State *stage3 = new ThirdStageState();
        	Game::GetInstance().Push(stage3);
		}
	}

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

void SecondStageState::Render()
{
	// Render every object
	RenderArray();
}
