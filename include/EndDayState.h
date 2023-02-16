/**
 * @file EndDayState.h
 * @author João Paulo Vaz Mendes (170002934@aluno.unb.br)
 * @brief EndDayState class header file
 * @version 0.1
 * @date 2023-02-15
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef ENDDAYSTATE_HEADER
#define ENDDAYSTATE_HEADER
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

class EndDayState : public State
{
private:
    Music backgroundMusic;
    //bool cartaFechada;
    Clock *stageClock;

public:

    EndDayState();
    ~EndDayState();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();
};
#endif