 #pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Entity.hpp"
#include "Text.hpp"
#include "Widgets.hpp"

class RenderWindow 
{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;

    public:
        RenderWindow(const char* title, int w, int h);
        void clear();
        void render(Entity& p_entity);
        void renderText(Text& p_text);
        void renderButton(Widgets::Button p_button);
        void display();
        void cleanUp();
};