/**
 * @file Text.cpp
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief Text class implementation file
 * @version 0.1
 * @date 2022-07-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "Text.h"
#include "Camera.h"
#include "Game.h"
#include "Resources.h"

#include <sstream>

Text::Text(GameObject &associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, Uint32 sizeWrapped, float blinkTime, float secondsToSelfDestruct) : Component(associated)
{
    this->texture = nullptr;
    this->fontFile = fontFile;
    this->fontSize = fontSize;
    this->style = style;
    this->text = text;
    this->color = color;
    this->showText = true;
    this->blinkTime = blinkTime;
    this->secondsToSelfDestruct = secondsToSelfDestruct;
    this->sizeWrapped = sizeWrapped;
    ResetTexture();
#ifdef DEBUG
    associated.AddComponent(new Collider(associated));
#endif
}

Text::~Text()
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
    }
}

void Text::Update(float dt)
{
    cooldown.Update(dt);
    if (cooldown.Get() > blinkTime and blinkTime != 0)
    {
        showText = !showText;
        cooldown.Restart();
    }
    if (this->secondsToSelfDestruct > 0)
    {
        selfDestructCount.Update(dt);
        if (selfDestructCount.Get() > secondsToSelfDestruct)
        {
            associated.RequestDelete();
        }
    }
}

void Text::Render()
{
    if (texture != nullptr and showText)
    {
        SDL_Rect src;
        SDL_Rect dst;

        src.x = 0;
        src.y = 0;
        src.w = associated.box.w;
        src.h = associated.box.h;

        dst.x = associated.box.x - Camera::pos.x;
        dst.y = associated.box.y - Camera::pos.y;
        dst.w = src.w;
        dst.h = src.h;

        SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &src, &dst, 0, nullptr, SDL_FLIP_NONE);
    }
}

bool Text::Is(std::string type)
{
    return (type == Text::type);
}

void Text::SetText(std::string text, std::string args)
{
    if (args != "")
    {
        std::stringstream textStream(text);
        std::stringstream argStream(args);
        std::string word;
        std::string replace;
        text = "";
        while (textStream >> word)
        {
            if (word != "%s")
            {
                text += word + " ";
            }
            else
            {
                argStream >> replace;
                text += replace + " ";
            }
        }
    }
    this->text = text;
    ResetTexture();
}

void Text::SetFontFile(std::string fontFile)
{
    this->fontFile = fontFile;
    ResetTexture();
}

void Text::SetColor(SDL_Color color)
{
    this->color = color;
    ResetTexture();
}
void Text::SetStyle(TextStyle style)
{
    this->style = style;
    ResetTexture();
}
void Text::SetFontSize(int fontSize)
{
    this->fontSize = fontSize;
    ResetTexture();
}

void Text::SetWrappedSize(Uint32 sizeWrapped)
{
    this->sizeWrapped = sizeWrapped;
    ResetTexture();
}

void Text::ResetTexture()
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
    }
    font = Resources::GetFont(fontFile, fontSize);
    //SDL_Surface *surf = TTF_RenderText_Blended_Wrapped(font.get(), text.c_str(), color, sizeWrapped);
    SDL_Surface *surf = TTF_RenderUTF8_Blended_Wrapped(font.get(), text.c_str(), color, sizeWrapped);
    texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surf);
    associated.box.w = surf->w;
    associated.box.h = surf->h;
    SDL_FreeSurface(surf);
}