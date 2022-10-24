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

int RenderWindow::getRefreshRate()
{
	int displayIndex = SDL_GetWindowDisplayIndex( window );

	SDL_DisplayMode mode;

	SDL_GetDisplayMode(displayIndex, 0, &mode);

	return mode.refresh_rate;
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

void RenderWindow::renderText(Text &p_text)
{
	TTF_Font* Font = TTF_OpenFont(p_text.getFontPath(), p_text.getFontSize());
	SDL_Color color = {p_text.r, p_text.g, p_text.b, 255};
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Font, p_text.getText(), color); 
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	int texW = p_text.w;
	int texH = p_text.h;
	SDL_QueryTexture(Message, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect; 
	dstrect.x = p_text.x;
	dstrect.y = p_text.y;
	dstrect.w = texW;
	dstrect.h = texH;

		
	SDL_RenderCopy(renderer, Message, NULL, &dstrect);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

void RenderWindow::renderButton(Widgets::Button &p_button)
{
    SDL_Rect rrect;
    rrect.x = p_button.getX();
	rrect.y = p_button.getY();
    rrect.w = p_button.getW();
    rrect.h = p_button.getH();

    SDL_Rect fillrect;
    fillrect.x = p_button.getX() + p_button.getBorderLength();
	fillrect.y = p_button.getY() + p_button.getBorderLength();
    fillrect.w = p_button.getW() - int(p_button.getBorderLength() * 2);
    fillrect.h = p_button.getH() - int(p_button.getBorderLength() * 2);

	// Border Rect
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rrect);
	SDL_RenderFillRect(renderer, &rrect);

	// Fill Rect 
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &fillrect);
	SDL_RenderFillRect(renderer, &fillrect);

	// Text
	TTF_Font* Sans = TTF_OpenFont("res/gfx/OpenSans-Regular.ttf", 50);
	SDL_Color color = {255, 255, 255, 255};
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, p_button.getText(), color); 
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	int texW = p_button.getW();
	int texH = p_button.getH();
	SDL_QueryTexture(Message, NULL, NULL, &texW, &texH);

	int winw = 900;
	int winh = 500;

	SDL_Rect dstrect; 
	dstrect.x = int((winw - texW) / 2);
	dstrect.y = int((winh - texH) / 2);
	dstrect.w = texW;
	dstrect.h = texH;

	SDL_RenderCopy(renderer, Message, NULL, &dstrect);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}