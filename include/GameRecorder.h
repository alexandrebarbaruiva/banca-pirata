/**
 * @file GameRecorder.h
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief GameRecorder class header file
 * @version 0.1
 * @date 2022-08-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef GAMERECORDER_HEADER
#define GAMERECORDER_HEADER
#include "Component.h"
#include "ComputerBox.h"
#include "Sprite.h"
#include "Sound.h"
#include "Collider.h"
#include "Vec2.h"
#include <algorithm>

class GameRecorder : public Component
{
private:
public:
    GameRecorder(GameObject &associated, std::string sprite = SCREEN2_PATH + "tela2-Spritesheet-Barra de gravacao.png", float scaleX = 1, float scaleY = 1, int frameCount = 12, float frameTime = 0.2, float secondsToSelfDestruct = 2.4);
    ~GameRecorder();

    std::string type = "GameRecorder";
    std::string name;

    bool recorded = false;

    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void NotifyCollision(GameObject &other);
};

#endif
