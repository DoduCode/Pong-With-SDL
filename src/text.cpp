#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Text.hpp"

Text::Text(const char *p_fontPath, int p_fontSize, const char *p_text, uint8_t p_r, uint8_t p_g, uint8_t p_b, int p_x, int p_y, int p_w, int p_h)
:fontPath(p_fontPath), fontSize(p_fontSize), text(p_text), r(p_r), g(p_g), b(p_b), x(p_x), y(p_y), w(p_w), h(p_h)
{}

const char* Text::getFontPath()
{
    return fontPath;
}

int Text::getFontSize()
{
    return fontSize;
}

const char* Text::getText()
{
    return text;
}

void Text::setText(const char* tval)
{
    text = tval;
}