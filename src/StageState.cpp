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

StageState::StageState() : State(), backgroundMusic("assets/audio/chill.ogg")
{
	// Background
	GameObject *bg = new GameObject();
	bg->AddComponent(new Sprite(*bg, "assets/img/placeholders/background.png", 1, 1.0));
	bg->AddComponent(new CameraFollower(*bg));
	bg->box.SetOrigin(0, 0);
	AddObject(bg);

	// HUD
	GameObject *hudGO = new GameObject();
	hudGO->AddComponent(new GameItem(*hudGO, "assets/img/placeholders/hud.png"));
	hudGO->box.SetOrigin(0, 0);
	AddObject(hudGO);

	// Counter
	GameObject *counterGO = new GameObject();
	counterGO->AddComponent(new GameItem(*counterGO, "assets/img/placeholders/counter.png"));
	counterGO->box.SetOrigin(0, 450);
	AddObject(counterGO);

	// Client
	GameObject *clientGO = new GameObject();
	clientGO->AddComponent(new GameItem(*clientGO, "assets/img/placeholders/client.png"));
	clientGO->box.SetOrigin(100, 300);
	AddObject(clientGO);

	// Player
	GameObject *playerGO = new GameObject();
	playerGO->AddComponent(new GameItem(*playerGO, "assets/img/placeholders/player.png"));
	playerGO->box.SetOrigin(800, 215);
	AddObject(playerGO);

	// PC
	GameObject *pcGO = new GameObject();
	pcGO->AddComponent(new GameItem(*pcGO, "assets/img/placeholders/pc.png"));
	pcGO->box.SetOrigin(500, 290);
	AddObject(pcGO);

	// Cases
	for (int i = 0; i < 5; i++)
	{
		GameObject *gameCaseGO = new GameObject();
		gameCaseGO->AddComponent(new GameItem(*gameCaseGO, "assets/img/placeholders/gamecase.png"));
		gameCaseGO->box.SetOrigin((430 + (100 * i)), 485);
		AddObject(gameCaseGO);
	}

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
	// std::vector<std::weak_ptr<GameObject>> collidable = QueryObjectsBy("Collider");
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
