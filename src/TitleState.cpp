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
#include "StageState.h"
#include "GameData.h"


TitleState::TitleState() : State(), backgroundMusic("assets/audio/abertura.ogg")
{
    // Background
    GameObject *bg = new GameObject();
    Sprite *spriteBackground = new Sprite(*bg, BASE_ASSET_PATH + "Grade_Anim_Start.png", 1, 1.0f);
    bg->AddComponent(spriteBackground);
    bg->box.x = 0;
    bg->box.y = 0;
    this->AddObject(bg);

    GameObject *titleTex = new GameObject();
    titleTex->AddComponent(new Text(*titleTex, "assets/font/up.ttf", 200, Text::BLENDED, "Banca Pirata", {255, 0, 0, SDL_ALPHA_OPAQUE}));
    titleTex->box.SetCenter(GAME_SCREEN_WIDTH / 2, 200);
    this->AddObject(titleTex);

    // Start Button
    Vec2 buttonPosition = Vec2(GAME_SCREEN_WIDTH / 2, 500);

    GameObject *startButton = new GameObject();
    startButton->AddComponent(new Button(*startButton, "startButton"));
    startButton->box.SetCenter(buttonPosition);
    this->AddObject(startButton);

    GameObject *startText = new GameObject();
    startText->AddComponent(new Text(*startText, "assets/font/up.ttf", 50, Text::BLENDED, "Start", {0, 0, 0, SDL_ALPHA_OPAQUE}));
    startText->box.SetCenter(buttonPosition);
    this->AddObject(startText);

    // Continue Button
    buttonPosition = Vec2(GAME_SCREEN_WIDTH / 2, 640);

    GameObject *continueButton = new GameObject();
    continueButton->AddComponent(new Button(*continueButton, "continueButton"));
    continueButton->box.SetCenter(buttonPosition);
    this->AddObject(continueButton);

    GameObject *continueText = new GameObject();
    continueText->AddComponent(new Text(*continueText, "assets/font/up.ttf", 50, Text::BLENDED, "Continue", {0, 0, 0, SDL_ALPHA_OPAQUE}));
    continueText->box.SetCenter(buttonPosition);
    this->AddObject(continueText);

    // Settings Button
    buttonPosition = Vec2(GAME_SCREEN_WIDTH / 2, 780);

    GameObject *settingsButton = new GameObject();
    settingsButton->AddComponent(new Button(*settingsButton, "settingsButton"));
    settingsButton->box.SetCenter(buttonPosition);
    this->AddObject(settingsButton);

    GameObject *settingsText = new GameObject();
    settingsText->AddComponent(new Text(*settingsText, "assets/font/up.ttf", 50, Text::BLENDED, "Settings", {0, 0, 0, SDL_ALPHA_OPAQUE}));
    settingsText->box.SetCenter(buttonPosition);
    this->AddObject(settingsText);

    // Exit Button
    buttonPosition = Vec2(GAME_SCREEN_WIDTH / 2, 920);

    GameObject *exitButton = new GameObject();
    exitButton->AddComponent(new Button(*exitButton, "exitButton"));
    exitButton->box.SetCenter(buttonPosition);
    this->AddObject(exitButton);

    GameObject *exitText = new GameObject();
    exitText->AddComponent(new Text(*exitText, "assets/font/up.ttf", 50, Text::BLENDED, "Exit", {0, 0, 0, SDL_ALPHA_OPAQUE}));
    exitText->box.SetCenter(buttonPosition);
    this->AddObject(exitText);
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
    backgroundMusic.Stop(0);
}

void TitleState::Resume()
{
    backgroundMusic.Play();
    Camera::Reset();
}

void TitleState::Start()
{
    Camera::Reset();
    LoadAssets();
    StartArray();
    backgroundMusic.Play();
    started = true;
}

void TitleState::Update(float dt)
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

    if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) or InputManager::GetInstance().QuitRequested() or pressedButton == "exitButton")
    {
        quitRequested = true;
    }

    if (InputManager::GetInstance().KeyPress(SPACE_KEY) or pressedButton == "startButton")
    {

        State *stage = new LetterState();
        Game::GetInstance().Push(stage);
        //State *stage = new StageState();
        //Game::GetInstance().Push(stage);
    }

    if (InputManager::GetInstance().KeyPress(SPACE_KEY) or pressedButton == "continueButton")
    {
        State *stage = new StageState(true);
        Game::GetInstance().Push(stage);
    }

    if (GameData::menuRequested)
    {
        GameData::menuRequested = false;
    }
}

void TitleState::Render()
{
    RenderArray();
}
