 #pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Text
{
    private:
        const char* text;
        SDL_Rect textRect;
        SDL_Texture *tex;

    public:
        Text(const char* p_text, int p_x, int p_y, int p_w, int p_h);

        int x, y, w, h;

        const char* getText();

        void setText(const char* tval);
        // SDL_Texture* getTex();
        SDL_Rect getCurrentFrame();
};