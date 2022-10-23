 #pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Entity
{
    private:
        int x, y, w, h;
        SDL_Rect currentFrame;
        // SDL_Texture* tex;

    public:
        Entity(int p_x, int p_y, int p_w, int p_h);
        
        int points = 0;

        int getX();
        int getY();
        int getW();
        int getH();

        void setX(int xval);
        void setY(int yval);
        // SDL_Texture* getTex();
        SDL_Rect getCurrentFrame();
};
