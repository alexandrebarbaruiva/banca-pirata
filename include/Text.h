/**
 * @file Text.h
 * @author Alexandre Augusto de Sá dos Santos (150056940@aluno.unb.br)
 * @brief Text class header file
 * @version 0.1
 * @date 2022-06-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef TEXT_HEADER
#define TEXT_HEADER
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "Component.h"
#include "Collider.h"
#include "Timer.h"
#include <memory>

class Text : public Component
{
public:
    enum TextStyle
    {
        SOLID,
        SHADED,
        BLENDED
    };

    Text(GameObject &associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, Uint32 sizeWrapped = 0, float blinkTime = 0, float secondsToSelfDestruct = 0);
    ~Text();

    std::string type = "Text";

    virtual void Update(float dt);
    void Render();
    bool Is(std::string type);

    void SetText(std::string text, bool hasArgs = false, std::string args = "");
    void SetColor(SDL_Color color);
    void SetStyle(TextStyle style);
    void SetFontFile(std::string fontFile);
    void SetFontSize(int fontSize);
    void SetWrappedSize(Uint32 wrappedSize);
    virtual void ResetTexture();
private:
    std::shared_ptr<TTF_Font> font;
    std::string text;
    SDL_Texture *texture;
    TextStyle style;

    std::string fontFile;
    int fontSize;
    SDL_Color color;
    Uint32 sizeWrapped;

    Timer cooldown;
    float blinkTime;

    float secondsToSelfDestruct;
    Timer selfDestructCount;

    bool showText;
};
#endif