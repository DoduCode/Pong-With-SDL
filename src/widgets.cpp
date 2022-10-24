#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Widgets.hpp"
#include "Text.hpp"

Widgets::Button::Button(const char *p_text, const char *p_borderc, int p_borderLength, const char *p_bg, int p_x, int p_y, int p_w, int p_h)
:text(p_text), border(p_borderc), borderLength(p_borderLength), bg(p_bg), x(p_x), y(p_y), w(p_w), h(p_h)
{}

bool Widgets::Button::getIfClicked(int mousex, int mousey)
{
    if (  mousex >= x && mousex <= x + w && mousey >= y && mousey <= y + h )
<<<<<<< HEAD
    {
=======
>>>>>>> 19a27a2593ff1e0bdf7b9c5d788c63e755ad9c15
        return true;

    else
        return false;
}

const char* Widgets::Button::getText()
{
    return text;
}

const char* Widgets::Button::getBorder()
{
    return border;
}

int Widgets::Button::getBorderLength()
{
    return borderLength;
}

const char* Widgets::Button::getBG()
{
    return bg;
}


int Widgets::Button::getX()
{
    return x;
}

int Widgets::Button::getY()
{
    return y;
}

int Widgets::Button::getW()
{
    return w;
}

int Widgets::Button::getH()
{
    return h;
}