/**
 * @file EndState.cpp
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief EndState class implementation file
 * @version 0.1
 * @date 2022-06-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "EndState.h"
#include "Sprite.h"
#include "Camera.h"
#include "InputManager.h"
#include "TitleState.h"
#include "Text.h"
#include "Game.h"
#include "CameraFollower.h"
#include "GameData.h"

EndState::EndState()
{
     GameObject *bg = new GameObject();
     Sprite *result;
     if (GameData::playerArrested)
     {
         result = new Sprite(*bg, BASE_ASSET_PATH + "derrota policial.png");
     }
     else
     {
         if (GameData::currentMoney >= 250)
         {
             result = new Sprite(*bg, BASE_ASSET_PATH + "Vitoria.png");
             // backgroundMusic = Music("assets/audio/endStateWin.ogg");
         }
         else
         {
             result = new Sprite(*bg, BASE_ASSET_PATH + "derrota agiota.png");
             // backgroundMusic = Music("assets/audio/endStateLose.ogg");
         }
     }
     bg->AddComponent(result);
     bg->box.SetOrigin({0, 0});
     AddObject(bg);

    GameObject *botaoContinuar = new GameObject();
    botaoContinuar->AddComponent(new Button(*botaoContinuar, "menu", 1.0 ,1 ,TITLE_PATH  + "botao menu longo.png"));
    botaoContinuar->box.SetCenter(GAME_SCREEN_WIDTH/2,1000);
    AddObject(botaoContinuar);

    GameObject *textoContinuar = new GameObject();
    textoContinuar->AddComponent(new Text(*textoContinuar,  FONTS_PATH + "up.ttf", 70, Text::SOLID, "MENU", {255, 255, 255, SDL_ALPHA_OPAQUE}));
    textoContinuar->box.SetCenter(GAME_SCREEN_WIDTH/2,1000);
    AddObject(textoContinuar);
}

void EndState::Update(float dt)
{
    UpdateArray(dt);

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

    if(pressedButton == "menu")
    {
        std::cout << "Menu" << std::endl;
        GameData::menuRequested = true;
        GameData::GameOver();
        this->Pause();
        popRequested = true;
        return;
    }
    //if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) or InputManager::GetInstance().QuitRequested())
    //{
    //    quitRequested = true;
    //}

    //if (InputManager::GetInstance().KeyPress(SPACE_KEY))
    //{
    //    popRequested = true;
    //}
}

EndState::~EndState()
{
    objectArray.clear();
}

void EndState::LoadAssets()
{
}

void EndState::Pause()
{
    backgroundMusic.Stop();
}

void EndState::Resume()
{
    backgroundMusic.Play();
    Camera::Reset();
}

void EndState::Start()
{
    Camera::Reset();
    LoadAssets();
    StartArray();
    started = true;
    backgroundMusic.Play();
}

void EndState::Render()
{
    RenderArray();
}
