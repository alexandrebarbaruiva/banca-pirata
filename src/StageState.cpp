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
#include "ThirdStageState.h"
#include "Constants.h"
#include "Sound.h"
#include "Text.h"
#include "Calendar.h"
#include "Wallet.h"
#include "Camera.h"
#include "InputManager.h"
#include "CameraFollower.h"
#include "ReputationArrow.h"
#include "Client.h"
#include "SirenBox.h"
#include "GameData.h"
#include "Button.h"
#include "PauseState.h"


StageState::StageState(bool loadGame) : State(), backgroundMusic("assets/audio/chill.ogg")
{
	// Remove any previous save data from state
	GameData::Reset();
	if (loadGame)
	{
		// Load from save file
		GameData::Load();
	}

	// Background
	GameObject *bg = new GameObject();
	bg->AddComponent(new Sprite(*bg, SCREEN1_PATH + "CenarioPixel.png", 1, 1.0));
	bg->AddComponent(new CameraFollower(*bg));
	bg->box.SetOrigin(0, 0);
	AddObject(bg);

	// HUD Dia + Hora + Dinheiro
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
	stageClock->Resume();
	timeHudText->AddComponent(stageClock);
	timeHudText->box.SetOrigin(300, 35);
	AddObject(timeHudText);

	GameObject *moneyHudText = new GameObject();
	//moneyHudText->AddComponent(new Text(*moneyHudText, "assets/font/five.ttf", 40, Text::SOLID, ("R$ " + std::to_string(GameData::currentMoney)), {255, 255, 255, SDL_ALPHA_OPAQUE}));
	moneyHudText->AddComponent(new Wallet(*moneyHudText, GameData::currentMoney));
	moneyHudText->box.SetOrigin(500, 35);
	AddObject(moneyHudText);

	// HUD Reputação
	GameObject *hudReputationArrowGO = new GameObject();
	hudReputationArrowGO->AddComponent(new ReputationArrow(*hudReputationArrowGO, GameData::currentRep));
	hudReputationArrowGO->box.SetOrigin(960, 0);
	AddObject(hudReputationArrowGO);

	// HUD Pause
	GameObject *hudPauseGO = new GameObject();
	//hudPauseGO->AddComponent(new GameItem(*hudPauseGO, "assets/img/placeholders/Tela 1-Pause.png", 1, 1));
	hudPauseGO->AddComponent(new Button(*hudPauseGO,"pause",1,1,"assets/img/placeholders/Tela 1-Pause.png"));
	hudPauseGO->box.SetOrigin(1800, 0);
	AddObject(hudPauseGO);

	// HUD Sirene
	GameObject *hudGOSirene = new GameObject();
	hudGOSirene->AddComponent(new SirenBox(*hudGOSirene));
	hudGOSirene->box.SetOrigin(1800, 355);
	AddObject(hudGOSirene);

	// Balcão
	GameObject *balcaoGO = new GameObject();
	balcaoGO->AddComponent(new GameItem(*balcaoGO, SCREEN1_PATH + "Balcao_Tela1.png", 1, 1));
	balcaoGO->box.SetOrigin(0, 0);
	AddObject(balcaoGO);

	// Lojeiro
	GameObject *lojeiroGO = new GameObject();
	lojeiroGO->AddComponent(new GameItem(*lojeiroGO, SCREEN1_PATH + "lojeiro.png", 1, 1));
	lojeiroGO->box.SetBottom(1290, 810);
	AddObject(lojeiroGO);


	gradeGO = nullptr;
	gradeFechada = false;
	//std::cout << "Games Loaded: ";
	//for (std::string i: GameData::ownedGames)
	//{
	//	std::cout << i << " ";
	//}
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
	backgroundMusic.Stop(0);
}

void StageState::Resume()
{
	backgroundMusic.Play();
}

void StageState::Update(float dt)
{
	// update camera
	Camera::Update(dt);

    std::string pressedButton;
    std::vector<std::weak_ptr<GameObject>> buttons = this->QueryObjectsByComponent("Button");
    for (unsigned i = 0; i < buttons.size(); i++)
    {
        Button *button = ((Button *)(buttons[i].lock()->GetComponent("Button")));
        if (button->isClicked)
        {
            pressedButton = button->name;
            button->isClicked = false;
        }
    }

	if (GameData::nextClient)
	{
		GameObject *cliente2GO = new GameObject();
		cliente2GO->AddComponent(new Client(*cliente2GO, NPCS_PATH + GameData::currentClient + "t1.png"));
		cliente2GO->box.SetBottom(0, GAME_SCREEN_HEIGHT);

		AddObject(cliente2GO);
	}

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

	if(pressedButton == "pause")
	{
		//std::cout << "Pause apertado" << std::endl;
        State *stage = new PauseState();
        Game::GetInstance().Push(stage);
	}
	if(gradeFechada) 
	{

		if(gradeGO->box.y > -1080) 
		{
			gradeGO->box = gradeGO->box - (speed * dt);
			//std::cout << "pos grade: " << gradeGO->box.Center().y << std::endl;
		}
		else
		{
			stageClock->Restart();
			stageClock->Resume();
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
	// Update every object
	UpdateArray(dt);

	srand(time(NULL));
}

void StageState::Render()
{
	// Render every object
	RenderArray();
}
