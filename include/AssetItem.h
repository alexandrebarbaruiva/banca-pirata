/**
 * @file AssetItem.h
 * @author João Paulo Vaz Mendes (170002934@aluno.unb.br)
 * @brief AssetItem class header file
 * @version 0.1
 * @date 2023-02-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef ASSETITEM_HEADER
#define ASSETITEM_HEADER
#include "Component.h"
#include "Sprite.h"
#include "Collider.h"
#include "Vec2.h"
#include "AssetGame.h"

class AssetItem : public Component
{
private:
public:
    AssetItem(GameObject &associated, AssetGame *gameLinked ,std::string sprite, float scaleX = 1, float scaleY = 1, bool moveable = false, float frameTime = 1.0, int frameCount = 1);

    std::string type = "AssetItem";
    std::string name;

    AssetGame *gameOrigin;

    bool moveable = false;
    float startPoint = 0;
    float currentPoint = 0;
    float endPoint = 100;
    Vec2 speed = Vec2(10, 0);

    bool clickable = false;
    bool isClicked = false;

    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void NotifyCollision(GameObject &other);
};

#endif
