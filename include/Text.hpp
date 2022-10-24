#include <iostream>

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Text
{
    private:
        const char* fontPath;
        int fontSize;
        const char* text;
        SDL_Rect textRect;
        SDL_Texture *tex;

    public:
        Text(const char* p_fontPath, int p_fontSize, const char* p_text, std::uint8_t p_r, std::uint8_t p_g, std::uint8_t p_b, int p_x, int p_y, int p_w, int p_h);

        std::uint8_t r, g, b;
        int x, y, w, h;

        const char* getFontPath();
        int getFontSize();
        const char* getText();

        void setText(const char* tval);
        // SDL_Texture* getTex();
        SDL_Rect getCurrentFrame();
};