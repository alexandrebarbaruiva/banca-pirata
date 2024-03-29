/**
 * @file TitleState.h
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief TitleState class header file
 * @version 0.1
 * @date 2022-07-11
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef TITLESTATE_HEADER
#define TITLESTATE_HEADER
#include "State.h"
#include "Sprite.h"
#include "Button.h"
#include "Text.h"
#include "InputManager.h"
#include "StageState.h"
#include "LetterState.h"
#include "Camera.h"
#include "Game.h"
#include "Music.h"

class TitleState : public State
{
private:
    Music backgroundMusic;

public:
    TitleState();
    ~TitleState();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();
};
#endif
