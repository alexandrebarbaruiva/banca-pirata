/**
 * @file Sprite.h
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief Sprite class header file
 * @version 0.1
 * @date 2022-06-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef SPRITE_HEADER
#define SPRITE_HEADER
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "Component.h"
#include <string>

class Sprite : public Component
{
private:
    SDL_Texture *texture;
    int width;
    int height;
    SDL_Rect clipRect;

public:
    Sprite(GameObject &associated);
    Sprite(GameObject &associated, std::string file);

    ~Sprite();

    std::string type = "Sprite";

    void Open(std::string file);
    void SetClip(int x, int y, int w, int h);
    void Render();
    int GetWidth();
    int GetHeight();
    bool IsOpen();

    void Update(float dt);
    bool Is(std::string type);
};
#endif

// Links
// https://www.geeksforgeeks.org/inheritance-in-c/