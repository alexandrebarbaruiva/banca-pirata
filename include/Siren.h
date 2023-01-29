/**
 * @file Siren.h
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief Siren class header file
 * @version 0.1
 * @date 2022-08-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef SIREN_HEADER
#define SIREN_HEADER
#include "Component.h"
#include "GameData.h"
#include "Sprite.h"
#include "Collider.h"
#include "Vec2.h"

class Siren : public Component
{
private:
public:
    Siren(GameObject &associated, int reputationScore, std::string spriteOn = "assets/img/placeholders/tela 1-sus.png", std::string spriteOff = "assets/img/placeholders/tela 1-sus-vazio.png", float scaleX = 1, float scaleY = 1, float frameTime = 1.0, int frameCount = 1);

    std::string type = "Siren";
    std::string spriteOn;
    std::string spriteOff;

    int reputationScore;

    bool isOn = false;

    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void NotifyCollision(GameObject &other);
};

#endif
