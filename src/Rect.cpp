/**
 * @file Rect.cpp
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief Rect class implementation file
 * @version 0.1
 * @date 2022-07-01
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "Rect.h"
#include <iostream>

Rect::Rect()
{
    this->x = 0;
    this->y = 0;
    this->w = 0;
    this->h = 0;
}

Rect::Rect(float x, float y, float w, float h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

Vec2 Rect::Center()
{
    return Vec2((this->x + this->w / 2), (this->y + this->h / 2));
}

Vec2 Rect::Origin()
{
    return Vec2(this->x, this->y);
}

Vec2 Rect::End()
{
    return Vec2(this->w, this->h);
}

void Rect::SetOrigin(Vec2 vector)
{
    this->x = vector.x;
    this->y = vector.y;
}

void Rect::SetCenter(Vec2 vector)
{
    this->x = vector.x - this->w / 2;
    this->y = vector.y - this->h / 2;
}

Rect Rect::operator+(const Vec2 &vector) const
{
    return Rect(this->x + vector.x, this->y + vector.y, this->w, this->h);
}

Rect Rect::operator+=(const Vec2 &vector) const
{
    return *this + vector;
}

float Rect::Distance(Rect r1, Rect r2)
{
    return Vec2::Distance(r1.Center(), r2.Center());
}

bool Rect::IsInside(Vec2 vector)
{
    bool insideX = (this->x < vector.x) and (vector.x < (this->w + this->x));
    bool insideY = (this->y < vector.y) and (vector.y < (this->h + this->y));
#ifdef DEBUG
    std::cout << BLUE;
    std::cout << "Check if vector is inside Rect\n";
    std::cout << RESET;
    std::cout << "Rect\n";
    std::cout << "X = " << this->x << " Y = " << this->y << "\n";
    std::cout << "W = " << this->x + this->w << " H = " << this->y + this->h << "\n";
    std::cout << "Vector\n";
    std::cout << "X = " << vector.x << " Y = " << vector.y << "\n";
#endif
    return insideX and insideY;
}
