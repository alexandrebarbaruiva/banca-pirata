/**
 * @file LetterState.h
 * @author João Paulo Vaz Mendes (170002934@aluno.unb.br)
 * @brief LetterState class header file
 * @version 0.1
 * @date 2023-02-09
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef LETTERSTATE_HEADER
#define LETTERSTATE_HEADER
#include "State.h"
#include "Sprite.h"
#include "Button.h"
#include "Text.h"
#include "InputManager.h"
#include "StageState.h"
#include "Camera.h"
#include "Game.h"
#include "Music.h"

class LetterState : public State
{
private:
    Music backgroundMusic;
    bool cartaFechada;

public:

    LetterState();
    ~LetterState();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();
};
#endif