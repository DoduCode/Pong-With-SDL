#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace Widgets
{
    class Button
    {
        private:
            const char* text;
            const char* border;
            const char* bg;
            int x, y, w, h;

        public:
            Button(const char* p_text, const char* p_borderc, const char* p_bg, int p_x, int p_y, int p_w, int p_h);

            bool getIfClicked(int mousex, int mousey);

            const char* getText();
            const char* getBorder();
            const char* getBG();

            int getX();
            int getY();
            int getW();
            int getH();

    };

} // namespace Widgets
