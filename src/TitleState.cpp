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
#include <string>

TitleState::TitleState() : State()
{
    // Background
    GameObject *bg = new GameObject();
    bg->AddComponent(new Sprite(*bg, "assets/img/store.png", 1, 1.0f));
    bg->box.x = 0;
    bg->box.y = 0;
    this->AddObject(bg);

    // Add ButtonBox
    GameObject *boxContainer = new GameObject();
    this->buttonBox = new ButtonBox(*boxContainer, "ButtonBox");
    boxContainer->AddComponent(buttonBox);

    // Start Button
    Vec2 buttonPosition = Vec2(GAME_SCREEN_WIDTH / 2, 300);

    GameObject *startButton = new GameObject();
    startButton->AddComponent(new Button(*startButton, "startButton"));
    startButton->box.SetCenter(buttonPosition);
    this->AddObject(startButton);
    buttonBox->AddButton(startButton);

    GameObject *startText = new GameObject();
    startText->AddComponent(new Text(*startText, "assets/font/Call me maybe.ttf", 50, Text::BLENDED, "Start", {255, 0, 0, SDL_ALPHA_OPAQUE}));
    startText->box.SetCenter(buttonPosition);
    this->AddObject(startText);

    // Continue Button
    buttonPosition = Vec2(GAME_SCREEN_WIDTH / 2, 420);

    GameObject *continueButton = new GameObject();
    continueButton->AddComponent(new Button(*continueButton, "continueButton"));
    continueButton->box.SetCenter(buttonPosition);
    this->AddObject(continueButton);
    buttonBox->AddButton(continueButton);

    GameObject *continueText = new GameObject();
    continueText->AddComponent(new Text(*continueText, "assets/font/Call me maybe.ttf", 50, Text::BLENDED, "Continue", {255, 0, 0, SDL_ALPHA_OPAQUE}));
    continueText->box.SetCenter(buttonPosition);
    this->AddObject(continueText);

    // Settings Button
    buttonPosition = Vec2(GAME_SCREEN_WIDTH / 2, 540);

    GameObject *settingsButton = new GameObject();
    settingsButton->AddComponent(new Button(*settingsButton, "settingsButton"));
    settingsButton->box.SetCenter(buttonPosition);
    this->AddObject(settingsButton);
    buttonBox->AddButton(settingsButton);

    GameObject *settingsText = new GameObject();
    settingsText->AddComponent(new Text(*settingsText, "assets/font/Call me maybe.ttf", 50, Text::BLENDED, "Settings", {255, 0, 0, SDL_ALPHA_OPAQUE}));
    settingsText->box.SetCenter(buttonPosition);
    this->AddObject(settingsText);

    // Exit Button
    buttonPosition = Vec2(GAME_SCREEN_WIDTH / 2, 660);

    GameObject *exitButton = new GameObject();
    exitButton->AddComponent(new Button(*exitButton, "exitButton"));
    exitButton->box.SetCenter(buttonPosition);
    buttonBox->AddButton(exitButton);
    this->AddObject(exitButton);

    GameObject *exitText = new GameObject();
    exitText->AddComponent(new Text(*exitText, "assets/font/Call me maybe.ttf", 50, Text::BLENDED, "Exit", {255, 0, 0, SDL_ALPHA_OPAQUE}));
    exitText->box.SetCenter(buttonPosition);
    this->AddObject(exitText);

    // TODO: convert into Button
    GameObject *text = new GameObject();
    text->box.x = GAME_SCREEN_WIDTH / 2;
    text->box.y = 500;
    text->AddComponent(new Text(*text, "assets/font/Call me maybe.ttf", 50, Text::BLENDED, "Settings", {255, 0, 0, SDL_ALPHA_OPAQUE}));
    this->AddObject(text);
    
    this->AddObject(boxContainer);
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
    std::string pressedButton;
    std::vector<std::weak_ptr<GameObject>> buttons = this->buttonBox->GetArray();
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
        State *stage = new StageState();
        Game::GetInstance().Push(stage);
    }

    if (InputManager::GetInstance().KeyPress(SPACE_KEY) or pressedButton == "continueButton")
    {
        State *stage = new StageState(true);
        Game::GetInstance().Push(stage);
    }
}

void TitleState::Render()
{
    RenderArray();
}
