/**
 * @file PauseState.cpp
 * @author João Paulo Vaz Mendes (170002934@aluno.unb.br)
 * @brief PauseState class header file
 * @version 0.1
 * @date 2023-02-09
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "PauseState.h"
#include "CameraFollower.h"
#include "GameData.h"
#include "Calendar.h"
#include "ReputationArrow.h"
#include "SirenBox.h"

PauseState::PauseState() : State()
{
    // Background
    GameObject *bg = new GameObject();
    bg->AddComponent(new Sprite(*bg, BASE_ASSET_PATH + "Grade_Anim_Start.png", 1, 1.0));
    bg->AddComponent(new CameraFollower(*bg));
    bg->box.SetOrigin(0, 0);
    AddObject(bg);

    // HUD Dia + Hora + Dinheiro
    GameObject *hudGO = new GameObject();
    hudGO->AddComponent(new GameItem(*hudGO, HUD_PATH + "dia_dinheiro.png", 1, 1));
    hudGO->box.SetOrigin(0, 0);
    AddObject(hudGO);

    GameObject *dayHudText = new GameObject();
    dayHudText->AddComponent(new Text(*dayHudText, FONTS_PATH + "five.ttf", 40, Text::SOLID, ("Day " + std::to_string(GameData::currentDay)), {255, 255, 255, SDL_ALPHA_OPAQUE}));
    dayHudText->box.SetOrigin(115, 35);
    AddObject(dayHudText);

    GameObject *timeHudText = new GameObject();
    stageClock = new Clock(*timeHudText, GameData::currentHour, GameData::currentMinute);
    stageClock->Pause();
    timeHudText->AddComponent(stageClock);
    // timeHudText->AddComponent(new Text(*timeHudText, "assets/font/five.ttf", 40, Text::SOLID, (stageClock->GetClock()), {255, 255, 255, SDL_ALPHA_OPAQUE}));
    timeHudText->box.SetOrigin(300, 35);
    AddObject(timeHudText);

    GameObject *moneyHudText = new GameObject();
    moneyHudText->AddComponent(new Text(*moneyHudText, FONTS_PATH + "five.ttf", 40, Text::SOLID, ("R$ " + std::to_string(GameData::currentMoney)), {255, 255, 255, SDL_ALPHA_OPAQUE}));
    moneyHudText->box.SetOrigin(500, 35);
    AddObject(moneyHudText);

    // HUD Reputação
    GameObject *hudReputationArrowGO = new GameObject();
    hudReputationArrowGO->AddComponent(new ReputationArrow(*hudReputationArrowGO, GameData::currentRep));
    hudReputationArrowGO->box.SetOrigin(960, 0);
    AddObject(hudReputationArrowGO);

    // HUD Pause
    GameObject *hudPauseGO = new GameObject();
    // hudPauseGO->AddComponent(new GameItem(*hudPauseGO, "assets/img/placeholders/Tela 1-Pause.png", 1, 1));
    hudPauseGO->AddComponent(new Button(*hudPauseGO, "pause", 1, 1, HUD_PATH + "Pause-press.png"));
    hudPauseGO->box.SetOrigin(1800, 0);
    AddObject(hudPauseGO);

    // Caixa HUD Sirene
    GameObject *caixaSireneGO = new GameObject();
    caixaSireneGO->AddComponent(new GameItem(*caixaSireneGO, SCREEN3_PATH + "Loja-fundo-suspeita.png", 1, 1));
    caixaSireneGO->box.SetOrigin(-50, 330);
    AddObject(caixaSireneGO);

    // HUD Sirene
    GameObject *hudGOSirene = new GameObject();
    hudGOSirene->AddComponent(new SirenBox(*hudGOSirene));
    hudGOSirene->box.SetOrigin(0, 355);
    // hudGOSirene->box.SetOrigin(1800, 355);
    AddObject(hudGOSirene);

    GameObject *letreiroPause = new GameObject();
    letreiroPause->AddComponent(new Text(*letreiroPause, FONTS_PATH + "up.ttf", 120, Text::SOLID, "Pausado", {255, 255, 255, SDL_ALPHA_OPAQUE}));
    letreiroPause->box.SetCenter(GAME_SCREEN_WIDTH / 2, 350);
    AddObject(letreiroPause);

    // GameObject *fundoPause = new GameObject();
    // fundoPause->AddComponent(new Sprite(*fundoPause, "assets/img/placeholders/config fundo.png", 1));
    // fundoPause->box.SetCenter(GAME_SCREEN_WIDTH/2,650);
    ////fundoPause->box.SetOrigin(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT/2);
    // AddObject(fundoPause);

    GameObject *botaoContinuar = new GameObject();
    botaoContinuar->AddComponent(new Button(*botaoContinuar, "continue", 0.8, 1, TITLE_PATH + "botao menu longo.png"));
    botaoContinuar->box.SetCenter(GAME_SCREEN_WIDTH / 2, 500);
    AddObject(botaoContinuar);

    GameObject *textoContinuar = new GameObject();
    textoContinuar->AddComponent(new Text(*textoContinuar, FONTS_PATH + "up.ttf", 70, Text::SOLID, "Continuar", {255, 255, 255, SDL_ALPHA_OPAQUE}));
    textoContinuar->box.SetCenter(GAME_SCREEN_WIDTH / 2, 500);
    AddObject(textoContinuar);

    GameObject *botaoMenu = new GameObject();
    botaoMenu->AddComponent(new Button(*botaoMenu, "menu", 0.8, 1, TITLE_PATH + "botao menu longo.png"));
    botaoMenu->box.SetCenter(GAME_SCREEN_WIDTH / 2, 650);
    AddObject(botaoMenu);

    GameObject *textoMenu = new GameObject();
    textoMenu->AddComponent(new Text(*textoMenu, FONTS_PATH + "up.ttf", 70, Text::SOLID, "Menu", {255, 255, 255, SDL_ALPHA_OPAQUE}));
    textoMenu->box.SetCenter(GAME_SCREEN_WIDTH / 2, 650);
    AddObject(textoMenu);

    GameObject *botaoSair = new GameObject();
    botaoSair->AddComponent(new Button(*botaoSair, "sair", 0.8, 1, TITLE_PATH + "botao menu longo.png"));
    botaoSair->box.SetCenter(GAME_SCREEN_WIDTH / 2, 800);
    AddObject(botaoSair);

    GameObject *textoSair = new GameObject();
    textoSair->AddComponent(new Text(*textoSair, FONTS_PATH + "up.ttf", 70, Text::SOLID, "Sair", {255, 255, 255, SDL_ALPHA_OPAQUE}));
    textoSair->box.SetCenter(GAME_SCREEN_WIDTH / 2, 800);
    AddObject(textoSair);
}

PauseState::~PauseState()
{
    objectArray.clear();
}

void PauseState::LoadAssets()
{
}

void PauseState::Pause()
{
}

void PauseState::Resume()
{
    Camera::Reset();
}

void PauseState::Start()
{
    Camera::Reset();
    LoadAssets();
    StartArray();
    started = true;
}

void PauseState::Update(float dt)
{
    InputManager input = InputManager::GetInstance();
    std::string pressedButton;
    std::vector<std::weak_ptr<GameObject>> buttons = this->QueryObjectsByComponent("Button");
    stageClock->AssertClock();
    if (not stageClock->paused)
    {
        stageClock->Pause();
    }

    for (unsigned i = 0; i < buttons.size(); i++)
    {
        Button *button = ((Button *)(buttons[i].lock()->GetComponent("Button")));
        if (button->isClicked)
        {
            pressedButton = button->name;
            button->isClicked = false;
        }
    }

    if (input.QuitRequested())
    {
        quitRequested = true;
    }

    if (input.KeyPress(ESCAPE_KEY) or pressedButton == "continue")
    {
        popRequested = true;
    }

    if (pressedButton == "menu")
    {
        std::cout << "Menu" << std::endl;
        GameData::menuRequested = true;
        popRequested = true;
    }
    if (pressedButton == "sair")
    {
        // std::cout << "Sair" << std::endl;
        quitRequested = true;
    }

    UpdateArray(dt);
}

void PauseState::Render()
{
    RenderArray();
}