/**
 * @file ReputationArrow.h
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief ReputationArrow class header file
 * @version 0.1
 * @date 2022-08-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef REPUTATION_HEADER
#define REPUTATION_HEADER
#include "Component.h"
#include "Sprite.h"
#include "Collider.h"
#include "Vec2.h"

class ReputationArrow : public Component
{
private:
public:
    ReputationArrow(GameObject &associated, std::string sprite, int relativePos, float scaleX = 1, float scaleY = 1, float frameTime = 1.0, int frameCount = 1);

    std::string type = "ReputationArrow";
    std::string name;

    float startPoint = 0;
    float currentPoint = 0;
    float destinationPoint = 0;
    float endPoint = 720;
    Vec2 speed = Vec2(100, 0);

    bool clickable = false;
    bool isClicked = false;

    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void NotifyCollision(GameObject &other);
};

#endif
