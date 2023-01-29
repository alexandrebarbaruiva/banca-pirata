/**
 * @file SirenBox.h
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief SirenBox class header file
 * @version 0.1
 * @date 2022-08-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef SIRENBOX_HEADER
#define SIRENBOX_HEADER
#include "Component.h"
#include "Sprite.h"
#include "State.h"
#include "Siren.h"
#include "Collider.h"

class SirenBox : public Component
{
private:
    std::vector<std::weak_ptr<GameObject>> sirenArray;

public:
    SirenBox(GameObject &associated);

    std::string type = "SirenBox";

    void Start();
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void NotifyCollision(GameObject &other);
};

#endif
