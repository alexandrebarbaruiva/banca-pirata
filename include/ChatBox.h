/**
 * @file ChatBox.h
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief ChatBox class header file
 * @version 0.1
 * @date 2022-08-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef CHATBOX_HEADER
#define CHATBOX_HEADER
#include "Component.h"
#include "Sprite.h"
#include "Collider.h"
#include "Vec2.h"

class ChatBox : public Component
{
private:
public:
    ChatBox(GameObject &associated, bool clickable = false, std::string sprite = SCREEN1_PATH + "Spritesheet-balao.png", float scaleX = 1, float scaleY = 1, float frameTime = 0.2, int frameCount = 5);

    std::string type = "ChatBox";

    bool clickable;
    bool isClicked = false;

    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void NotifyCollision(GameObject &other);
};

#endif
