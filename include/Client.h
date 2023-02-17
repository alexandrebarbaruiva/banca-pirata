/**
 * @file Client.h
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief Client class header file
 * @version 0.1
 * @date 2022-08-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef CLIENT_HEADER
#define CLIENT_HEADER
#include "Component.h"
#include "Sprite.h"
#include "Sound.h"
#include "Collider.h"
#include "Vec2.h"

class Client : public Component
{
private:
public:
    Client(GameObject &associated, std::string sprite, float scaleX = 1, float scaleY = 1, bool reachedEndpoint = false, float frameTime = 1.0, int frameCount = 1);
    ~Client();

    std::string type = "Client";
    std::string name;

    Sound *stepSound;
    bool stepPlaying = false;

    bool reachedEndpoint = false;
    float startPoint = 0;
    float currentPoint = 0;
    float endPoint = 1210;
    Vec2 speed = Vec2(50, 0);

    void PopChat();
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void NotifyCollision(GameObject &other);
};

#endif
