/**
 * @file Button.cpp
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief Button class implementation file
 * @version 0.1
 * @date 2022-06-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "Button.h"
#include "Sprite.h"
#include "Collider.h"

Button::Button(GameObject &associated, std::string name, float scaleX, float scaleY, std::string sprite, bool clickable) : Component(associated)
{
    Sprite *spriteButton = new Sprite(associated, sprite, 1, 1.0);
    spriteButton->SetScale(scaleX, scaleY);
    associated.AddComponent(spriteButton);
#ifdef DEBUG
    associated.AddComponent(new Collider(associated));
    std::cout << RED;
    std::cout << "associated button size:\n";
    std::cout << RESET;
    std::cout << "X = " << associated.box.x << " Y = " << associated.box.y << "\n";
    std::cout << "W = " << associated.box.x + associated.box.w << " H = " << associated.box.y + associated.box.h << "\n";
#endif
    this->clickable = clickable;
    this->name = name;
    this->isClicked = false;
    this->isSelected = false;
    this->timesClicked = 0;
}

void Button::Update(float dt)
{
    InputManager input = InputManager::GetInstance();
    if (input.MousePress(LEFT_MOUSE_BUTTON) and this->clickable)
    {
        bool mouseInButton = associated.box.IsInside(input.GetMousePosition());
        if (mouseInButton)
        {
            this->isClicked = true;
            this->timesClicked++;
            Sound *sound = new Sound(associated, AUDIOS_PATH + "buttonClick.ogg");
            sound->Play();
#ifdef DEBUG
            Sound *duckSound = new Sound(associated, "assets/audio/quack.mp3");
            duckSound->Play();
            std::cout << GREEN;
            std::cout << this->name;
            std::cout << RESET;
            std::cout << " has been clicked " << this->timesClicked << " times.\n";
#endif
        }
    }
}

void Button::Render()
{
}

void Button::NotifyCollision(GameObject &other)
{
}

bool Button::Is(std::string type)
{
    return (type == Button::type);
}

int Button::GetHealth()
{
    return 0;
}
