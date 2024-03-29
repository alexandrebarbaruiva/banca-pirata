/**
 * @file StageState.h
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief StageState class header file
 * @version 0.1
 * @date 2022-06-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef STAGESTATE_HEADER
#define STAGESTATE_HEADER
#include "Sprite.h"
#include "State.h"
#include "TileSet.h"
#include "GameItem.h"
#include "Music.h"
#include "Clock.h"

class StageState : public State
{
private:
    Music backgroundMusic;
    TileSet *tileSet;
    Clock *stageClock;
    GameObject *gradeGO;
    bool gradeFechada;

public:
    StageState(bool loadGame = false);
    ~StageState();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();
};

#endif
