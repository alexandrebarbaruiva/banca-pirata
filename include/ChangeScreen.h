/**
 * @file ChangeScreen.h
 * @author João Paulo Vaz Mendes (170002934@aluno.unb.br)
 * @brief ChangeScreen class header file
 * @version 0.1
 * @date 2023-01-28
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef CHANGESCREEN_HEADER
#define CHANGESCREEN_HEADER
#include "Component.h"
#include "StageState.h"
#include "Sprite.h"
#include "Collider.h"
#include "Vec2.h"

class ChangeScreen : public Component
{
private:
public:
    ChangeScreen(GameObject &associated, bool clickable = false, std::string sprite = SCREEN3_PATH + "Loja-desliga.png", float scaleX = 1, float scaleY = 1, float frameTime = 1.0, int frameCount = 1);

    std::string type = "ChangeScreen";

    bool clickable;
    bool isClicked = false;

    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void NotifyCollision(GameObject &other);
};

#endif
