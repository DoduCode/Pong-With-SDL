#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Text.hpp"

Text::Text(const char* p_text, int p_x, int p_y, int p_w, int p_h)
:text(p_text), x(p_x), y(p_y), w(p_w), h(p_h)
{}

const char* Text::getText()
{
    return text;
}

void Text::setText(const char* tval)
{
    text = tval;
}