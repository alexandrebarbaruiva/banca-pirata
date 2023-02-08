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
#include "Wallet.h"
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
#include "ComputerBox.h"

SecondStageState::SecondStageState() : State(), backgroundMusic("assets/audio/chill.ogg")
{
#ifdef DEBUG
	std::cout << "Loaded Second Screen\n";
#endif
	// Background
	GameObject *bg = new GameObject();
	bg->AddComponent(new Sprite(*bg, SCREEN2_PATH + "PlanoDeFundo_Tela2.png"));
	bg->box.SetOrigin(0, 0);
	AddObject(bg);

	// Mesa Tela
	GameObject *tableGO = new GameObject();
	tableGO->AddComponent(new Sprite(*tableGO, SCREEN2_PATH + "Mesa_Tela2.png"));
	tableGO->box.SetOrigin(0, 0);
	AddObject(tableGO);

	// Computador
	GameObject *computerBoxGO = new GameObject();
	computerBoxGO->AddComponent(new ComputerBox(*computerBoxGO));
	computerBoxGO->box.SetOrigin(1170, 170);
	AddObject(computerBoxGO);

	// Caixa diálogo
	GameObject *dialogBoxGO = new GameObject();
	dialogBoxGO->AddComponent(new Sprite(*dialogBoxGO, SCREEN2_PATH + "tela2-caixa de dialogo.png"));
	dialogBoxGO->box.SetBottom(0, GAME_SCREEN_HEIGHT);
	AddObject(dialogBoxGO);

	GameObject *chatText = new GameObject();
	Text *text = new Text(*chatText, "assets/font/up.ttf", 50, Text::BLENDED, "TESTE", {255, 255, 255, SDL_ALPHA_OPAQUE}, GAME_SCREEN_WIDTH - GAME_SCREEN_WIDTH / 8);
	text->SetText("Opa meu bacano, me ve um jogo de %s %s e %s Ah, voce tem troco pra nota de 100?", "suspense, luta aventura?");
	chatText->AddComponent(text);
	chatText->box.SetCenter(GAME_SCREEN_WIDTH / 2, (GAME_SCREEN_HEIGHT - GAME_SCREEN_HEIGHT / 6));
	AddObject(chatText);

	// HUD Dia + Dinheiro
	GameObject *hudGO = new GameObject();
	hudGO->AddComponent(new GameItem(*hudGO, HUD_PATH + "dia_dinheiro.png", 1, 1));
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
	moneyHudText->AddComponent(new Wallet(*moneyHudText, GameData::currentMoney));
	moneyHudText->box.SetOrigin(500, 35);
	AddObject(moneyHudText);

	// HUD Reputação
	GameObject *hudReputationArrowGO = new GameObject();
	hudReputationArrowGO->AddComponent(new ReputationArrow(*hudReputationArrowGO, GameData::currentRep, false));
	hudReputationArrowGO->box.SetOrigin(960, 0);
	AddObject(hudReputationArrowGO);

	// HUD Pause
	GameObject *hudPauseGO = new GameObject();
	hudPauseGO->AddComponent(new GameItem(*hudPauseGO, HUD_PATH + "Pause.png"));
	hudPauseGO->box.SetOrigin(1800, 0);
	AddObject(hudPauseGO);

	// Cliente frontal
	GameObject *clienteGO = new GameObject();
	clienteGO->AddComponent(new GameItem(*clienteGO, NPCS_PATH + GameData::currentClient + "t2.png"));
	clienteGO->box.SetBottom(0, dialogBoxGO->box.y);
	AddObject(clienteGO);

	

	gradeGO = nullptr;	

	gradeFechada = false;

}

SecondStageState::~SecondStageState()
{
	this->Pause();
	GameData::clientCanLeave = true;
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

	if(GameData::endDay && !gradeFechada )
	{
		if (gradeGO == nullptr)
		{
			// Grade fechando a loja
			gradeGO = new GameObject();
			gradeGO->AddComponent(new Sprite(*gradeGO, "assets/img/placeholders/Grade_Anim_Start.png", 1, 1.0));
			gradeGO->box.SetOrigin(0, -1080);
			AddObject(gradeGO);
		}
		stageClock->Pause();
		if(gradeGO->box.y <= 0) 
		{
			gradeGO->box = gradeGO->box + (speed * dt);
		}
		else
		{
			gradeFechada = true;
			//this->Pause();
        	State *stage3 = new ThirdStageState();
        	Game::GetInstance().Push(stage3);
			//popRequested = true;
		}
	}
	if(gradeFechada) 
	{

		popRequested = true;
		gradeGO->box.SetOrigin(0, -1080);
		if(gradeGO->box.y > -1080) 
		{
			gradeGO->box.SetOrigin(0, -1080);
			//std::cout << "pos grade: " << gradeGO->box.Center().y << std::endl;
		}
		else
		{
			gradeFechada = false;
		}
	}

	// Update de GOs do HUD
	std::vector<std::weak_ptr<GameObject>> calendarios = this->QueryObjectsByComponent("Calendar");
	for (unsigned i = 0; i < calendarios.size(); i++)
	{
		Calendar *calendario = ((Calendar *)(calendarios[i].lock()->GetComponent("Calendar")));
		calendario->Update(dt);
	}
	std::vector<std::weak_ptr<GameObject>> relogios = this->QueryObjectsByComponent("Clock");
	for (unsigned i = 0; i < relogios.size(); i++)
	{
		Clock *relogio = ((Clock *)(relogios[i].lock()->GetComponent("Clock")));
		relogio->AssertClock();
	}
	std::vector<std::weak_ptr<GameObject>> wallets = this->QueryObjectsByComponent("Wallet");
	for (unsigned i = 0; i < wallets.size(); i++)
	{
		Wallet *wallet = ((Wallet *)(wallets[i].lock()->GetComponent("Wallet")));
		wallet->Update(dt);
		//texto->SetText("R$ " + std::to_string(GameData::currentMoney));
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
