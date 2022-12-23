/**
 * @file TitleState.cpp
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief TitleState class implementation file
 * @version 0.1
 * @date 2022-07-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "TitleState.h"

TitleState::TitleState() : State()
{
    // Background
    GameObject *bg = new GameObject();
    bg->AddComponent(new Sprite(*bg, "assets/img/store.png", 1, 1.0f));
    bg->box.x = 0;
    bg->box.y = 0;
    this->AddObject(bg);

    // TODO: convert into Button
    GameObject *gtext = new GameObject();
    gtext->box.x = GAME_SCREEN_WIDTH / 2;
    gtext->box.y = 300;
    // gtext->AddComponent(new Box)
    gtext->AddComponent(new Text(*gtext, "assets/font/Call me maybe.ttf", 50, Text::BLENDED, "Start", {255, 0, 0, SDL_ALPHA_OPAQUE}));
    this->AddObject(gtext);

    // TODO: convert into Button
    GameObject *ntext = new GameObject();
    ntext->box.x = GAME_SCREEN_WIDTH / 2;
    ntext->box.y = 400;
    ntext->AddComponent(new Text(*ntext, "assets/font/Call me maybe.ttf", 50, Text::BLENDED, "Load", {255, 0, 0, SDL_ALPHA_OPAQUE}));
    this->AddObject(ntext);

    // TODO: convert into Button
    GameObject *text = new GameObject();
    text->box.x = GAME_SCREEN_WIDTH / 2;
    text->box.y = 500;
    text->AddComponent(new Text(*text, "assets/font/Call me maybe.ttf", 50, Text::BLENDED, "Settings", {255, 0, 0, SDL_ALPHA_OPAQUE}));
    this->AddObject(text);
}

TitleState::~TitleState()
{
    objectArray.clear();
}

void TitleState::LoadAssets()
{
}

void TitleState::Pause()
{
}

void TitleState::Resume()
{
    Camera::Reset();
}

void TitleState::Start()
{
    Camera::Reset();
    LoadAssets();
    StartArray();
    started = true;
}

void TitleState::Update(float dt)
{
    UpdateArray(dt);
    if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested())
    {
        quitRequested = true;
    }

    if (InputManager::GetInstance().KeyPress(SPACE_KEY))
    {
        State *stage = new StageState();
        Game::GetInstance().Push(stage);
    }
}

void TitleState::Render()
{
    RenderArray();
}
