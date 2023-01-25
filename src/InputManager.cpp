/**
 * @file InputManager.cpp
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief InputManager class implementation file
 * @version 0.1
 * @date 2022-07-01
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "InputManager.h"

InputManager::InputManager()
{
    for (int i = 0; i < 6; i++)
    {
        this->mouseUpdate[i] = 0;
        this->mouseState[i] = false;
    }
    this->updateCounter = 0;
    this->quitRequested = false;
    this->mouseX = 0;
    this->mouseY = 0;
    this->buttonManager = new ButtonManager();
}

InputManager::~InputManager()
{
}

InputManager &InputManager::GetInstance()
{
    static InputManager inputManager;
    return inputManager;
}

void InputManager::Update()
{
    SDL_Event event;

    SDL_GetMouseState(&mouseX, &mouseY);
    quitRequested = false;
    updateCounter++;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            if (event.key.repeat)
            {
                break;
            }
            curEvent = InputOptions::KEY_DOWN;
            keyState[event.key.keysym.sym] = true;
            keyUpdate[event.key.keysym.sym] = updateCounter;
            break;

        case SDL_KEYUP:
            curEvent = InputOptions::KEY_RELEASE;
            keyState[event.key.keysym.sym] = false;
            keyUpdate[event.key.keysym.sym] = updateCounter;
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (event.key.repeat)
            {
                break;
            }
            curEvent = InputOptions::MOUSE_DOWN;
            mouseState[event.button.button] = true;
            mouseUpdate[event.button.button] = updateCounter;
            break;

        case SDL_MOUSEBUTTONUP:
            curEvent = InputOptions::MOUSE_RELEASE;
            mouseState[event.button.button] = false;
            mouseUpdate[event.button.button] = updateCounter;
            break;

        case SDL_QUIT:
            curEvent = InputOptions::QUIT;
            quitRequested = true;
            break;

        default:
            break;
        }
    }
}

bool InputManager::KeyPress(int key)
{
    return keyState[key] == true and keyUpdate[key] == updateCounter;
}

bool InputManager::KeyRelease(int key)
{
    return keyState[key] == false and keyUpdate[key] == updateCounter;
}

bool InputManager::IsKeyDown(int key)
{
    return keyState[key];
}

bool InputManager::MousePress(int button)
{
    return mouseState[button] == true and mouseUpdate[button] == updateCounter;
}

bool InputManager::MouseRelease(int button)
{
    return mouseState[button] == false and mouseUpdate[button] == updateCounter;
}

bool InputManager::IsMouseDown(int button)
{
    return mouseState[button];
}

/// @brief Get mouse position relative to screen
/// @return Vec2 with (x,y)
Vec2 InputManager::GetMousePosition()
{
    return Vec2(this->mouseX, this->mouseY);
}

int InputManager::GetMouseX()
{
    return this->mouseX;
}

int InputManager::GetMouseY()
{
    return this->mouseY;
}

bool InputManager::QuitRequested()
{
    return this->quitRequested;
}