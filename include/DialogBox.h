/**
 * @file DialogBox.h
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief DialogBox class header file
 * @version 0.1
 * @date 2022-08-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef DIALOGBOX_HEADER
#define DIALOGBOX_HEADER
#include "Component.h"
#include "Sprite.h"
#include "Collider.h"
#include "Vec2.h"
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <time.h>

class DialogBox : public Component
{
private:
public:
    DialogBox(GameObject &associated);
    ~DialogBox();

    GameObject *dialogText;
    std::string type = "DialogBox";

    std::string GetCurrentDialog();
    std::string GetCurrentGameTypes();

    void Start();
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void NotifyCollision(GameObject &other);
};

#endif
