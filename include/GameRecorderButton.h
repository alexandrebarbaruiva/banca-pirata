/**
 * @file GameRecorderButton.h
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief GameRecorderButton class header file
 * @version 0.1
 * @date 2022-08-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef GAMERECORDERBUTTON_HEADER
#define GAMERECORDERBUTTON_HEADER
#include "Component.h"
#include "Sprite.h"
#include "Collider.h"
#include "Vec2.h"
#include "GameRecorder.h"

class GameRecorderButton : public Component
{
private:
public:
    GameRecorderButton(GameObject &associated, float scaleX = 1, float scaleY = 1, float frameTime = 1.0, int frameCount = 1);

    std::string type = "GameRecorderButton";
    std::string name;

    bool clickable = false;

    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void NotifyCollision(GameObject &other);
};

#endif
