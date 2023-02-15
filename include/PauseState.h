/**
 * @file PauseState.h
 * @author João Paulo Vaz Mendes (170002934@aluno.unb.br)
 * @brief PauseState class header file
 * @version 0.1
 * @date 2023-02-09
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef PAUSESTATE_HEADER
#define PAUSESTATE_HEADER
#include "State.h"
#include "Sprite.h"
#include "Button.h"
#include "Text.h"
#include "InputManager.h"
#include "StageState.h"
#include "Clock.h"
#include "Camera.h"
#include "Game.h"
#include "Music.h"

class PauseState : public State
{
private:
    Music backgroundMusic;
    bool cartaFechada;
    Clock *stageClock;

public:

    PauseState();
    ~PauseState();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();
};
#endif