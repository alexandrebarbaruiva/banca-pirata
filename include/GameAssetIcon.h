/**
 * @file GameAssetIcon.h
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief GameAssetIcon class header file
 * @version 0.1
 * @date 2022-08-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef GAME_ASSET_ICON_HEADER
#define GAME_ASSET_ICON_HEADER
#include "Component.h"
#include "Sprite.h"
#include "Collider.h"
#include "Vec2.h"

class GameAssetIcon : public Component
{
private:
public:
    GameAssetIcon(GameObject &associated, std::string sprite, bool isClickable = true, bool isClicked = false, float scaleX = 1, float scaleY = 1, float frameTime = 1.0, int frameCount = 1);

    std::string type = "GameAssetIcon";

    bool isClickable;
    bool isClicked;
    bool isOnTab;

    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void NotifyCollision(GameObject &other);
};

#endif
