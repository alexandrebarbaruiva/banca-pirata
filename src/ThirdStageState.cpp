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
#include "AssetItem.h"
#include "ChangeScreen.h"
#include <algorithm>
#include <iterator>
#include <iostream>
#include "PauseState.h"
#include "EndDayState.h"

ThirdStageState::ThirdStageState() : State(), backgroundMusic(AUDIOS_PATH + "thirdStage.ogg")
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
	stageClock = new Clock(*timeHudText, 18, 0);
	GameData::currentMinute = 0;
	GameData::currentHour = 8;
	stageClock->Pause();
	timeHudText->AddComponent(stageClock);
	timeHudText->box.SetOrigin(300, 35);
	AddObject(timeHudText);

	GameObject *moneyHudText = new GameObject();
	moneyHudText->AddComponent(new Text(*moneyHudText, "assets/font/five.ttf", 40, Text::SOLID, ("R$ " + std::to_string(GameData::currentMoney)), {255, 255, 255, SDL_ALPHA_OPAQUE}));
	moneyHudText->box.SetOrigin(500, 35);
	AddObject(moneyHudText);

	// HUD Reputação
	GameObject *hudReputationArrowGO = new GameObject();
	hudReputationArrowGO->AddComponent(new ReputationArrow(*hudReputationArrowGO));
	hudReputationArrowGO->box.SetOrigin(960, 0);
	AddObject(hudReputationArrowGO);

	// HUD Pause
	GameObject *hudPauseGO = new GameObject();
	// hudPauseGO->AddComponent(new GameItem(*hudPauseGO, HUD_PATH + "Pause.png", 1, 1));
	hudPauseGO->AddComponent(new Button(*hudPauseGO, "pause", 1, 1, HUD_PATH + "Pause.png"));
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

	assetGame1 = nullptr;
	carrinho1 = nullptr;

	// Alternativa de Asset
	GameObject *textoAlternativaGO = new GameObject();
	textoAlternativaGO->AddComponent(new Text(*textoAlternativaGO, "assets/font/five.ttf", 80, Text::SOLID, "OU", {255, 191, 0, SDL_ALPHA_OPAQUE}));
	textoAlternativaGO->box.SetOrigin(1200, 400);
	AddObject(textoAlternativaGO);

	assetGame2 = nullptr;
	carrinho2 = nullptr;

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
	if (GameData::menuRequested)
	{
		this->Pause();
		popRequested = true;
		return;
	}
	backgroundMusic.Play();
}

void ThirdStageState::Update(float dt)
{
	// Logica de jogos disponiveis na loja
	if (GameData::endDay)
	{
		std::vector<std::string> jogosParaVenda;
		std::vector<std::string> jogosComprados = GameData::ownedGames;
		std::vector<std::string> todosJogos = GameData::allGames;
		int jogoInt1;
		int jogoInt2;
		std::string jogoStr1, jogoStr2;
		std::sort(todosJogos.begin(), todosJogos.end());
		std::sort(jogosComprados.begin(), jogosComprados.end());
		std::set_difference(todosJogos.begin(), todosJogos.end(), jogosComprados.begin(), jogosComprados.end(), std::back_inserter(jogosParaVenda));

		// std::cout << "Jogos para a loja: ";
		// for (std::string i : jogosParaVenda)
		//{
		//	std::cout << i << " ";
		// }
		if (jogosParaVenda.size() > 0)
		{
			jogoInt1 = rand() % jogosParaVenda.size();
			jogoStr1 = jogosParaVenda[jogoInt1];
			jogosParaVenda.erase(jogosParaVenda.begin() + jogoInt1);
			// std::cout << "Jogo 1: " << jogoStr1 << std::endl;
			//  GameAsset 1
			GameObject *gameAsset1GO = new GameObject();
			assetGame1 = new AssetGame(*gameAsset1GO, jogoStr1, 30);
			gameAsset1GO->AddComponent(assetGame1);
			AddObject(gameAsset1GO);

			// Capa Game 1
			GameObject *capaGO = new GameObject();
			capaGO->AddComponent(new AssetItem(*capaGO, assetGame1, assetGame1->spriteName, 0.8, 0.8, false, 1, 1));
			capaGO->box.SetOrigin(800, 220);
			AddObject(capaGO);

			// Marcador de Preço Game 1
			GameObject *marcaPrecoGame1GO = new GameObject();
			marcaPrecoGame1GO->AddComponent(new AssetItem(*marcaPrecoGame1GO, assetGame1, SCREEN3_PATH + "Loja-fundo preco.png", 1, 1));
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
			carrinho1 = new Carrinho(*carrinho1GO, assetGame1);
			carrinho1GO->AddComponent(carrinho1);
			carrinho1GO->box.SetOrigin(1010, 600);
			AddObject(carrinho1GO);
		}
		else
		{
			// Tratamento se não tiver mais jogos
		}
		if (jogosParaVenda.size() > 0)
		{
			jogoInt2 = rand() % jogosParaVenda.size();
			jogoStr2 = jogosParaVenda[jogoInt2];
			jogosParaVenda.erase(jogosParaVenda.begin() + jogoInt2);
			// std::cout << "Jogo 2: " << jogoStr2 << std::endl;
			//  GameAsset 2
			GameObject *gameAsset2GO = new GameObject();
			AssetGame *assetGame2 = new AssetGame(*gameAsset2GO, jogoStr2, 30);
			gameAsset2GO->AddComponent(assetGame2);
			AddObject(gameAsset2GO);

			// Capa Game 2
			GameObject *capa2GO = new GameObject();
			capa2GO->AddComponent(new AssetItem(*capa2GO, assetGame2, assetGame2->spriteName, 0.8, 0.8, false, 1, 1));
			capa2GO->box.SetOrigin(1400, 220);
			AddObject(capa2GO);

			// Marcador de Preço Game 2
			GameObject *marcaPrecoGame2GO = new GameObject();
			marcaPrecoGame2GO->AddComponent(new AssetItem(*marcaPrecoGame2GO, assetGame2, SCREEN3_PATH + "Loja-fundo preco.png", 1, 1));
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
			carrinho2 = new Carrinho(*carrinho2GO, assetGame2);
			carrinho2GO->AddComponent(carrinho2);
			carrinho2GO->box.SetOrigin(1610, 600);
			AddObject(carrinho2GO);
		}
		else
		{
			// Tratamento se só tiver um jogo
		}

		// Terminou o ajuste
		GameData::endDay = false;
	}

	// Update every object
	UpdateArray(dt);

	// update camera
	Camera::Update(dt);

	InputManager input = InputManager::GetInstance();
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
	if (pressedButton == "pause")
	{
		// std::cout << "Pause apertado" << std::endl;
		State *stage = new PauseState();
		Game::GetInstance().Push(stage);
	}

	std::vector<std::weak_ptr<GameObject>> carrinhos = this->QueryObjectsByComponent("Carrinho");
	for (unsigned i = 0; i < carrinhos.size(); i++)
	{
		for (unsigned j = i + 1; j < carrinhos.size(); j++)
		{
			Carrinho *carrinho1 = ((Carrinho *)(carrinhos[i].lock()->GetComponent("Carrinho")));
			Carrinho *carrinho2 = ((Carrinho *)(carrinhos[j].lock()->GetComponent("Carrinho")));
			if (GameData::currentMoney >= 30)
			{
				if (carrinho1->clickable && carrinho1->isClicked)
				{
					carrinho1->Choosed();
					carrinho2->UnChoosed();
					carrinho1->isClicked = false;
					// std::cout << "Jogo do carrinho 1: " << carrinho1->gameToBuy->name << std::endl;
				}
				if (carrinho2->clickable && carrinho2->isClicked)
				{
					carrinho2->Choosed();
					carrinho1->UnChoosed();
					carrinho2->isClicked = false;
					// std::cout << "Jogo do carrinho 2: " << carrinho2->gameToBuy->name << std::endl;
				}
			}
		}
	}

	std::vector<std::weak_ptr<GameObject>> powerbuttons = this->QueryObjectsByComponent("ChangeScreen");
	for (unsigned i = 0; i < powerbuttons.size(); i++)
	{
		ChangeScreen *powerbutton = ((ChangeScreen *)(powerbuttons[i].lock()->GetComponent("ChangeScreen")));
		if (powerbutton->isClicked)
		{

			std::vector<std::weak_ptr<GameObject>> games = this->QueryObjectsByComponent("AssetGame");
			for (unsigned a = 0; a < games.size(); a++)
			{
				AssetGame *game = ((AssetGame *)(games[a].lock()->GetComponent("AssetGame")));
				if (game->gameChoosed)
				{

					// std::cout << "Tudo certo comprando o jogo: " << game->name << std::endl;
					// TODO adicionar jogas ao save
					GameData::ownedGames.emplace_back(game->name);
					GameData::currentMoney -= 30;
					GameData::moneySpent = true;
				}
			}
			powerbutton->isClicked = false;
			pressedButton = powerbutton->type;

			// associated.RequestDelete();
			// this->isClicked = true;
		}
	}
	// check if quit was requested
	if (input.QuitRequested())
	{
		quitRequested = true;
	}

	if (input.KeyPress(ESCAPE_KEY))
	{
		State *stage = new PauseState();
		// State *stage = new EndDayState();
		Game::GetInstance().Push(stage);
	}

	if (input.MousePress(LEFT_MOUSE_BUTTON))
	{
#ifdef DEBUG
		std::cout << "X:" << input.GetMouseX() << " Y:" << input.GetMouseY() << "\n";
#endif
	}

	if (pressedButton == "ChangeScreen")
	{

		// Change to StageState
		// State *stage = &Game::GetInstance().GetCurrentState();
		// State *stage = new StageState(true);
		// GameData::endDay = false;
		GameData::currentDay++;
		// Save Game
		GameData::Save(GameData::currentMinute, GameData::currentHour, GameData::currentDay, GameData::currentMoney, GameData::currentRep, GameData::currentSus, GameData::ownedGames);
		this->Pause();
		popRequested = true;
		State *stage = new EndDayState();
		Game::GetInstance().Push(stage);
	}

	srand(time(NULL));
}

void ThirdStageState::Render()
{
	// Render every object
	RenderArray();
}
