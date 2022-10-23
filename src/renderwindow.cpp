#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char* title, int w, int h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity)
{
    SDL_Rect rect;
    rect.x = p_entity.getX();
	rect.y = p_entity.getY();
    rect.w = p_entity.getW();
    rect.h = p_entity.getH();

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);
	SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void RenderWindow::renderText(Text& p_text)
{
	TTF_Font* Sans = TTF_OpenFont("res/gfx/OpenSans-Regular.ttf", 75);
	SDL_Color color = {28, 28, 28, 255};
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, p_text.getText(), color); 
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	int texW = p_text.w;
	int texH = p_text.h;
	SDL_QueryTexture(Message, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { p_text.x, p_text.y, texW, texH };

		
	SDL_RenderCopy(renderer, Message, NULL, &dstrect);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

void RenderWindow::renderButton(Widgets::Button p_button)
{
	SDL_Color = color;

	if (p_button == 'white')
		color = {255, 255, 255}

		
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}