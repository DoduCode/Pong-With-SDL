#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Entity.hpp"

Entity::Entity(int p_x, int p_y, int p_w, int p_h)
:x(p_x), y(p_y), w(p_w), h(p_h)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
}

int Entity::getX()
{
	return x;
}
int Entity::getY()
{
	return y;
}
int Entity::getW()
{
	return w;
}
int Entity::getH()
{
	return h;
}

void Entity::setY(int yval)
{
    y = yval;
}

void Entity::setX(int xval)
{
    x = xval;
}
