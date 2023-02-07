/**
 * @file ThirdStageState.cpp
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief ThirdStageState class implementation file. Where happens the first part of the game.
 * @version 0.1
 * @date 2022-06-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "ThirdStageState.h"
#include "Constants.h"
#include "Game.h"
#include "Text.h"
#include "Camera.h"
#include "InputManager.h"
#include "CameraFollower.h"
#include "GameData.h"
#include "ReputationArrow.h"
#include "SirenBox.h"
#include "Client.h"
#include "Clock.h"
#include "Calendar.h"
#include "Carrinho.h"
#include "AssetGame.h"
#include "ChangeScreen.h"

ThirdStageState::ThirdStageState() : State(), backgroundMusic("assets/audio/chill.ogg")
{
#ifdef DEBUG
	std::cout << "Loaded Second Screen\n";
#endif

	// Background
	GameObject *bg = new GameObject();
	bg->AddComponent(new Sprite(*bg, BASE_ASSET_PATH + "Grade_Anim_Start.png"));
	bg->box.SetOrigin(0, 0);
	AddObject(bg);

	

	// HUD Dia + Dinheiro
	GameObject *hudGO = new GameObject();
	hudGO->AddComponent(new GameItem(*hudGO, HUD_PATH + "dia_dinheiro.png"));
	hudGO->box.SetOrigin(0, 0);
	AddObject(hudGO);

	GameObject *dayHudText = new GameObject();
	dayHudText->AddComponent(new Calendar(*dayHudText, GameData::currentDay));
	dayHudText->box.SetOrigin(115, 35);
	AddObject(dayHudText);

	GameObject *timeHudText = new GameObject();
	stageClock = new Clock(*timeHudText, GameData::currentHour, GameData::currentMinute);
    GameData::currentMinute = 0;
    GameData::currentHour = 8;
	GameData::currentDay++;
	stageClock->Pause();
	timeHudText->AddComponent(stageClock);
	timeHudText->box.SetOrigin(300, 35);
	AddObject(timeHudText);

	GameObject *moneyHudText = new GameObject();
	moneyHudText->AddComponent(new Text(*moneyHudText, "assets/font/five.ttf", 40, Text::SOLID, ("R$ " + std::to_string(GameData::currentMoney)), {255, 255, 255, SDL_ALPHA_OPAQUE}));
	moneyHudText->box.SetOrigin(500, 35);
	AddObject(moneyHudText);

	// HUD Reputação
	GameObject *hudReputationGO2 = new GameObject();
	hudReputationGO2->AddComponent(new GameItem(*hudReputationGO2, HUD_PATH + "Rep.png", 1, 1));
	hudReputationGO2->box.SetOrigin(960, 0);
	AddObject(hudReputationGO2);

	// HUD Seta da Reputação
	GameObject *hudReputationArrowGO = new GameObject();
	hudReputationArrowGO->AddComponent(new ReputationArrow(*hudReputationArrowGO, GameData::currentRep, 1, 1));
	hudReputationArrowGO->box.SetOrigin(960, 60);
	AddObject(hudReputationArrowGO);

	// HUD Pause
	GameObject *hudPauseGO = new GameObject();
	hudPauseGO->AddComponent(new GameItem(*hudPauseGO, HUD_PATH + "Pause.png", 1, 1));
	hudPauseGO->box.SetOrigin(1800, 0);
	AddObject(hudPauseGO);

	// HUD Sirene
	GameObject *hudGOSirene = new GameObject();
	hudGOSirene->AddComponent(new SirenBox(*hudGOSirene));
	hudGOSirene->box.SetOrigin(0, 355);
	AddObject(hudGOSirene);

	// Computador
	GameObject *computadorGO = new GameObject();
	computadorGO->AddComponent(new GameItem(*computadorGO, SCREEN2_PATH + "Mesa_Tela2.png"));
	computadorGO->box.SetOrigin(0, 0);
	AddObject(computadorGO);

	// Tela de Fundo do PC
	GameObject *fundoPcGO = new GameObject();
	fundoPcGO->AddComponent(new GameItem(*fundoPcGO, SCREEN3_PATH + "Loja-fundo-site.png", 1, 0.97, false, 1, 1));
	fundoPcGO->box.SetOrigin(732, 160);
	AddObject(fundoPcGO);

	// Caixa HUD Sirene
	GameObject *caixaSireneGO = new GameObject();
	caixaSireneGO->AddComponent(new GameItem(*caixaSireneGO, SCREEN3_PATH + "Loja-fundo-suspeita.png", 1, 1));
	caixaSireneGO->box.SetOrigin(-50, 330);
	AddObject(caixaSireneGO);

	// GameAsset 1
	GameObject *gameAsset1GO = new GameObject();
	AssetGame *assetGame1 = new AssetGame(*gameAsset1GO, COVERS_PATH + "capa-placeholder.png", "Violento", "Radical", "Esportivo", 30);
	// gameAsset1GO->AddComponent(assetGame1);

	// Capa Game 1
	GameObject *capaGO = new GameObject();
	capaGO->AddComponent(new GameItem(*capaGO, assetGame1->spriteName, 0.8, 0.8, false, 1, 1));
	capaGO->box.SetOrigin(800, 220);
	AddObject(capaGO);

	// Marcador de Preço Game 1
	GameObject *marcaPrecoGame1GO = new GameObject();
	marcaPrecoGame1GO->AddComponent(new GameItem(*marcaPrecoGame1GO, SCREEN3_PATH + "Loja-fundo preco.png", 1, 1));
	marcaPrecoGame1GO->box.SetOrigin(1000, 200);
	AddObject(marcaPrecoGame1GO);

	// Preço Game 1
	GameObject *precoGame1GO = new GameObject();
	precoGame1GO->AddComponent(new Text(*precoGame1GO, "assets/font/five.ttf", 40, Text::SOLID, ("$" + std::to_string(assetGame1->price)), {0, 0, 0, SDL_ALPHA_OPAQUE}));
	precoGame1GO->box.SetOrigin(1015, 220);
	AddObject(precoGame1GO);

	// Categoria 1 Game 1
	GameObject *categoria1Game1GO = new GameObject();
	categoria1Game1GO->AddComponent(new Text(*categoria1Game1GO, "assets/font/five.ttf", 30, Text::SOLID, assetGame1->category1, {255, 0, 0, SDL_ALPHA_OPAQUE}));
	categoria1Game1GO->box.SetOrigin(800, 570);
	AddObject(categoria1Game1GO);

	// Categoria 2 Game 1
	GameObject *categoria2Game1GO = new GameObject();
	categoria2Game1GO->AddComponent(new Text(*categoria2Game1GO, "assets/font/five.ttf", 30, Text::SOLID, assetGame1->category2, {0, 0, 255, SDL_ALPHA_OPAQUE}));
	categoria2Game1GO->box.SetOrigin(800, 620);
	AddObject(categoria2Game1GO);

	// Categoria 3 Game 1
	GameObject *categoria3Game1GO = new GameObject();
	categoria3Game1GO->AddComponent(new Text(*categoria3Game1GO, "assets/font/five.ttf", 30, Text::SOLID, assetGame1->category3, {0, 255, 0, SDL_ALPHA_OPAQUE}));
	categoria3Game1GO->box.SetOrigin(800, 670);
	AddObject(categoria3Game1GO);

	// Carrinho Game 1
	GameObject *carrinho1GO = new GameObject();
	carrinho1GO->AddComponent(new GameItem(*carrinho1GO, SCREEN3_PATH + "Loja-compra.png", 0.6, 0.6, false, 1, 1));
	carrinho1GO->box.SetOrigin(1020, 610);
	AddObject(carrinho1GO);

	// Alternativa de Asset
	GameObject *textoAlternativaGO = new GameObject();
	textoAlternativaGO->AddComponent(new Text(*textoAlternativaGO, "assets/font/five.ttf", 80, Text::SOLID, "OU", {255, 191, 0, SDL_ALPHA_OPAQUE}));
	textoAlternativaGO->box.SetOrigin(1200, 400);
	AddObject(textoAlternativaGO);

	// GameAsset 2
	GameObject *gameAsset2GO = new GameObject();
	AssetGame *assetGame2 = new AssetGame(*gameAsset2GO, COVERS_PATH + "Capa kirby.png", "Fofo", "Casual", "Radical", 20);
	// gameAsset1GO->AddComponent(assetGame1);

	// Capa Game 2
	GameObject *capa2GO = new GameObject();
	capa2GO->AddComponent(new GameItem(*capa2GO, assetGame2->spriteName, 0.8, 0.8, false, 1, 1));
	capa2GO->box.SetOrigin(1400, 220);
	AddObject(capa2GO);

	// Marcador de Preço Game 2
	GameObject *marcaPrecoGame2GO = new GameObject();
	marcaPrecoGame2GO->AddComponent(new GameItem(*marcaPrecoGame2GO, SCREEN3_PATH + "Loja-fundo preco.png", 1, 1));
	marcaPrecoGame2GO->box.SetOrigin(1600, 200);
	AddObject(marcaPrecoGame2GO);

	// Preço Game 2
	GameObject *precoGame2GO = new GameObject();
	precoGame2GO->AddComponent(new Text(*precoGame2GO, "assets/font/five.ttf", 40, Text::SOLID, ("$" + std::to_string(assetGame2->price)), {0, 0, 0, SDL_ALPHA_OPAQUE}));
	precoGame2GO->box.SetOrigin(1615, 220);
	AddObject(precoGame2GO);

	// Categoria 1 Game 2
	GameObject *categoria1Game2GO = new GameObject();
	categoria1Game2GO->AddComponent(new Text(*categoria1Game2GO, "assets/font/five.ttf", 30, Text::SOLID, assetGame2->category1, {255, 0, 191, SDL_ALPHA_OPAQUE}));
	categoria1Game2GO->box.SetOrigin(1400, 570);
	AddObject(categoria1Game2GO);

	// Categoria 2 Game 2
	GameObject *categoria2Game2GO = new GameObject();
	categoria2Game2GO->AddComponent(new Text(*categoria2Game2GO, "assets/font/five.ttf", 30, Text::SOLID, assetGame2->category2, {191, 0, 255, SDL_ALPHA_OPAQUE}));
	categoria2Game2GO->box.SetOrigin(1400, 620);
	AddObject(categoria2Game2GO);

	// Categoria 3 Game 2
	GameObject *categoria3Game2GO = new GameObject();
	categoria3Game2GO->AddComponent(new Text(*categoria3Game2GO, "assets/font/five.ttf", 30, Text::SOLID, assetGame2->category3, {255, 128, 0, SDL_ALPHA_OPAQUE}));
	categoria3Game2GO->box.SetOrigin(1400, 670);
	AddObject(categoria3Game2GO);

	// Carrinho Game 2
	GameObject *carrinho2GO = new GameObject();
	carrinho2GO->AddComponent(new GameItem(*carrinho2GO, SCREEN3_PATH + "Loja-compra.png", 0.6, 0.6, false, 1, 1));
	carrinho2GO->box.SetOrigin(1620, 610);
	AddObject(carrinho2GO);

	// End Of Day Post-it
	GameObject *postItGO = new GameObject();
	postItGO->AddComponent(new GameItem(*postItGO, SCREEN3_PATH + "Loja-postit.png", 1.0, 1.0, false, 1, 1));
	postItGO->box.SetOrigin(1745, 620);
	AddObject(postItGO);

	// Botao Desligar PC
	GameObject *iconeGO = new GameObject();
	iconeGO->AddComponent(new ChangeScreen(*iconeGO));
	iconeGO->box.SetOrigin(1800, 745);
	AddObject(iconeGO);
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

	// Update every object
	UpdateArray(dt);

	// update camera
	Camera::Update(dt);

	InputManager input = InputManager::GetInstance();
    std::string pressedButton;

    std::vector<std::weak_ptr<GameObject>> buttons = this->QueryObjectsByComponent("ChangeScreen");
    for (unsigned i = 0; i < buttons.size(); i++)
    {
		ChangeScreen *button = ((ChangeScreen *) (buttons[i].lock()->GetComponent("ChangeScreen")));
        if (button->isClicked)
        {
            button->isClicked = false;
            pressedButton = button->type;

        	//associated.RequestDelete();
        	//this->isClicked = true;
        }
    }
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

	if(pressedButton == "ChangeScreen")
	{

        	// Change to StageState
        	//State *stage = &Game::GetInstance().GetCurrentState();
        	//State *stage = new StageState(true);
        	this->Pause();
			popRequested = true;
        	//Game::GetInstance().Push(stage);
	}

	srand(time(NULL));

}

void ThirdStageState::Render()
{
	// Render every object
	RenderArray();
}
