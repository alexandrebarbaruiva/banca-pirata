/**
 * @file EndDayState.cpp
 * @author João Paulo Vaz Mendes (170002934@aluno.unb.br)
 * @brief EndDayState class header file
 * @version 0.1
 * @date 2023-02-09
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "EndDayState.h"
#include "CameraFollower.h"
#include "GameData.h"
#include "Calendar.h"
#include "ReputationArrow.h"
#include "SirenBox.h"
#include "EndState.h"

EndDayState::EndDayState() : State(), backgroundMusic(AUDIOS_PATH + "chill.ogg")
{
	// Background
	GameObject *bg = new GameObject();
	bg->AddComponent(new Sprite(*bg, BASE_ASSET_PATH + "Grade_Anim_Start.png", 1, 1.0));
	bg->AddComponent(new CameraFollower(*bg));
	bg->box.SetOrigin(0, 0);
	AddObject(bg);

	// Caixa HUD Sirene
	GameObject *caixaSireneGO = new GameObject();
	caixaSireneGO->AddComponent(new GameItem(*caixaSireneGO, SCREEN3_PATH + "Loja-fundo-suspeita.png", 1, 1));
	caixaSireneGO->box.SetOrigin(-50, 230);
	AddObject(caixaSireneGO);


    GameObject *fundoEndDay = new GameObject();
    fundoEndDay->AddComponent(new GameItem(*fundoEndDay, SCREEN3_PATH + "Resultados-fundo.png", 1.5, 1.5));
    fundoEndDay->box.SetCenter(GAME_SCREEN_WIDTH/2,500);
    //fundoPause->box.SetOrigin(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT/2);
    AddObject(fundoEndDay);

	GameObject *letreiroBalanco = new GameObject();
	letreiroBalanco->AddComponent(new Text(*letreiroBalanco,  FONTS_PATH + "up.ttf", 70, Text::SOLID, "BALANÇO DO DIA", {255, 255, 255, SDL_ALPHA_OPAQUE}));
	letreiroBalanco->box.SetCenter(GAME_SCREEN_WIDTH/2, 245);
	AddObject(letreiroBalanco);

	GameObject *letreiroTotal = new GameObject();
	letreiroTotal->AddComponent(new Text(*letreiroTotal, FONTS_PATH + "up.ttf", 70, Text::SOLID, "TOTAL", {255, 255, 255, SDL_ALPHA_OPAQUE}));
	letreiroTotal->box.SetCenter(GAME_SCREEN_WIDTH/2, 515);
	AddObject(letreiroTotal);

    GameObject *moeda1 = new GameObject();
    moeda1->AddComponent(new GameItem(*moeda1, SCREEN3_PATH + "moeda.png"));
    moeda1->box.SetCenter(750,600);
    AddObject(moeda1);

    GameObject *moeda2 = new GameObject();
    moeda2->AddComponent(new GameItem(*moeda2, SCREEN3_PATH + "moeda.png"));
    moeda2->box.SetCenter(1170,600);
    AddObject(moeda2);

	GameObject *letreiroREP = new GameObject();
	letreiroREP->AddComponent(new Text(*letreiroREP, FONTS_PATH + "up.ttf", 90, Text::SOLID, "REP:", {255,255,255, SDL_ALPHA_OPAQUE}));
	letreiroREP->box.SetCenter(800, 775);
	AddObject(letreiroREP);

    GameObject *botaoContinuar = new GameObject();
    botaoContinuar->AddComponent(new Button(*botaoContinuar, "finalizar", 1.0 ,1 ,TITLE_PATH  + "botao menu longo.png"));
    botaoContinuar->box.SetCenter(GAME_SCREEN_WIDTH/2,940);
    AddObject(botaoContinuar);

    GameObject *textoContinuar = new GameObject();
    textoContinuar->AddComponent(new Text(*textoContinuar,  FONTS_PATH + "up.ttf", 70, Text::SOLID, "PRÓXIMO DIA", {255, 255, 255, SDL_ALPHA_OPAQUE}));
    textoContinuar->box.SetCenter(GAME_SCREEN_WIDTH/2,940);
    AddObject(textoContinuar);
    GameData::continueMusic = false;
}

EndDayState::~EndDayState()
{
    objectArray.clear();
}

void EndDayState::LoadAssets()
{
}

void EndDayState::Pause()
{
    backgroundMusic.Stop(0);
}

void EndDayState::Resume()
{
    backgroundMusic.Play();
    Camera::Reset();
}

void EndDayState::Start()
{
    Camera::Reset();
    LoadAssets();
    StartArray();
    backgroundMusic.Play();
    started = true;
}

void EndDayState::Update(float dt)
{
	InputManager input = InputManager::GetInstance();
    std::string pressedButton;
    std::vector<std::weak_ptr<GameObject>> buttons = this->QueryObjectsByComponent("Button");
   //stageClock->AssertClock(); 
   //stageClock->Pause();

    // Elementos da tela que devem sempre atualizar

	// HUD Sirene
	GameObject *hudGOSirene = new GameObject();
	hudGOSirene->AddComponent(new SirenBox(*hudGOSirene));
	hudGOSirene->box.SetOrigin(0, 255);
	//hudGOSirene->box.SetOrigin(1800, 355);
	AddObject(hudGOSirene);

	GameObject *dinheiroVerde = new GameObject();
	dinheiroVerde->AddComponent(new Text(*dinheiroVerde, FONTS_PATH + "up.ttf", 100, Text::SOLID,"+ " + std::to_string(GameData::moneyInDay), {0,255,0, SDL_ALPHA_OPAQUE}));
	dinheiroVerde->box.SetCenter(1050, 345);
	AddObject(dinheiroVerde);

    if (GameData::moneySpent)
    {
        GameObject *dinheiroVermelho = new GameObject();
        dinheiroVermelho->AddComponent(new Text(*dinheiroVermelho, FONTS_PATH + "up.ttf", 100, Text::SOLID, "- " + std::to_string(30), {255, 0, 0, SDL_ALPHA_OPAQUE}));
        dinheiroVermelho->box.SetCenter(GAME_SCREEN_WIDTH / 2, 435);
        AddObject(dinheiroVermelho);

        GameObject *dinheiroBranco = new GameObject();
        dinheiroBranco->AddComponent(new Text(*dinheiroBranco, FONTS_PATH + "up.ttf", 100, Text::SOLID, std::to_string(GameData::currentMoney - GameData::moneyInDay + 30), {255, 255, 255, SDL_ALPHA_OPAQUE}));
        dinheiroBranco->box.SetCenter(850, 345);
        AddObject(dinheiroBranco);
    }
    else
    {
        GameObject *dinheiroBranco = new GameObject();
        dinheiroBranco->AddComponent(new Text(*dinheiroBranco, FONTS_PATH + "up.ttf", 100, Text::SOLID, std::to_string(GameData::currentMoney - GameData::moneyInDay), {255, 255, 255, SDL_ALPHA_OPAQUE}));
        dinheiroBranco->box.SetCenter(850, 345);
        AddObject(dinheiroBranco);
    }

    GameObject *dinheiroAmarelo = new GameObject();
	dinheiroAmarelo->AddComponent(new Text(*dinheiroAmarelo, FONTS_PATH + "up.ttf", 140, Text::SOLID, std::to_string(GameData::currentMoney), {255,255,0, SDL_ALPHA_OPAQUE}));
	dinheiroAmarelo->box.SetCenter(GAME_SCREEN_WIDTH/2, 590);
	AddObject(dinheiroAmarelo);

	GameObject *RepVerde = new GameObject();
    if(GameData::repInDay > 0)
    {
	    RepVerde->AddComponent(new Text(*RepVerde, FONTS_PATH + "up.ttf", 90, Text::SOLID, "+" + std::to_string(GameData::repInDay), {0,255,0, SDL_ALPHA_OPAQUE}));
    }
    else
    {
	    RepVerde->AddComponent(new Text(*RepVerde, FONTS_PATH + "up.ttf", 90, Text::SOLID, std::to_string(GameData::repInDay), {255,0,0, SDL_ALPHA_OPAQUE}));
    }
	RepVerde->box.SetCenter(1000, 775);
	AddObject(RepVerde);

    for (unsigned i = 0; i < buttons.size(); i++)
    {
        Button *button = ((Button *)(buttons[i].lock()->GetComponent("Button")));
        if (button->isClicked)
        {
            pressedButton = button->name;
            button->isClicked = false;
        }
    }

    //if (input.QuitRequested())
    //{
    //    quitRequested = true;
    //}

    //if(input.KeyPress(ESCAPE_KEY) or pressedButton == "continue")
    //{
    //    this->Pause();
    //    popRequested = true;
    //}

    if(pressedButton == "finalizar")
    {
            std::cout << "dia: " << GameData::currentDay << std::endl;
            if(GameData::currentDay > 7)
            {
                std::cout << "Acabou o jogo" << std::endl;
			    popRequested = true;
        	    State *stage = new EndState();
        	    Game::GetInstance().Push(stage);
            }
            GameData::moneySpent = false;
        	this->Pause();
			popRequested = true;
    }
    //if(pressedButton == "sair")
    //{
    //    //std::cout << "Sair" << std::endl;
    //    quitRequested = true;
    //}

    UpdateArray(dt);
}

void EndDayState::Render()
{
    RenderArray();
}