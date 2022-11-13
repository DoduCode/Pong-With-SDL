#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Text.hpp"
#include "Widgets.hpp"
#include "Utils.hpp"

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) > 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

	if (TTF_Init() == -1)
		std::cout << "TTF_Init has failed. Error: " << std::endl;

	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) 
		std::cout << "Unable to initialize audio: " << Mix_GetError() << std::endl;

	int winw = 900;
	int winh = 500;
	RenderWindow window("Pong with SDL", winw, winh);   

	Entity player1(10, int(winh - 300), 5, 100);
	Entity player2(winw - 15, int(winh - 300), 5, 100);
	Entity ball(int(winw / 2), int((winh - 10) / 2), 10, 10);
	Entity line(int((winw - 10) / 2), 0, 10, 500);
	
	Text player1score("res/gfx/OpenSans-Regular.ttf", 75, "00", 52, 52, 52, 20, 0, 50, 50);
	Text player2score("res/gfx/OpenSans-Regular.ttf", 75, "00", 52, 52, 52, int(winw - 60), 0, 50, 50);

	Text startText("res/gfx/OpenSans-Regular.ttf", 50, "Click 'Start' to begin the game", 255, 255, 255, 5, 5, 100, 20);
	Widgets::Button start2Button("Start 2v2", "white", 1, "black", int((winw - 250) / 2), int((winh - 100) / 2), 250, 100);
	Widgets::Button startBButton("Start Bot", "white", 1, "black", int((winw - 250) / 2), int((winh - 175)), 250, 100);

	Widgets::Button newGameButton("New Game", "white", 1, "black", int((winw - 400) / 2), int((winh - 100) / 2), 400, 100);
	Text winPlayer("res/gfx/OpenSans-Regular.ttf", 50, "Player Wins", 255, 255, 255, int(winw - 200) / 2, 5, 200, 100);

	Mix_Chunk* bounce;
	Mix_Chunk* score;

	bounce = Mix_LoadWAV("res/sfx/bounce.wav");
	score = Mix_LoadWAV("res/sfx/score.wav");

	bool gameRunning = true;

	bool startScreen = true;
	bool winScreen = false;

	bool up = false;
	bool right = false;

	bool haveFriends;

	int mouseX;
	int mouseY;

	const float timeStep = 0.01f;
	float accumulator = 0.0f;
	float currentTime = utils::hireTimeInSeconds();

	SDL_Event event;

	while (gameRunning)
	{
		int startTicks = SDL_GetTicks();

		float newTime = utils::hireTimeInSeconds();
		float frameTime = newTime - currentTime;

		if (frameTime > 0.25f)
			frameTime = 0.25f;

		currentTime = newTime;
		accumulator += frameTime;
		
		while (accumulator >= timeStep)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					gameRunning = false;

				if (event.type == SDL_KEYDOWN && (!winScreen && !startScreen))
				{
					const Uint8 *state = SDL_GetKeyboardState(NULL);

					if (state[SDL_SCANCODE_S])
					{
						if (player1.getY() >= winh - 100)
							player1.setY(winh - 100);

						else
							player1.setY(player1.getY() + 10);
					}
					
					else if (state[SDL_SCANCODE_W])
					{
						if (player1.getY() <= 0)
							player1.setY(0);

						else
							player1.setY(player1.getY() - 10);
					}

					if (state[SDL_SCANCODE_DOWN] && haveFriends)
					{
						if (player2.getY() >= winh - 100)
							player2.setY(winh - 100);

						else
							player2.setY(player2.getY() + 10);
					}
					
					else if (state[SDL_SCANCODE_UP] && haveFriends)
					{
						if (player2.getY() <= 0)
							player2.setY(0);

						else
							player2.setY(player2.getY() - 10);
					}
				}
			
				if (event.type == SDL_MOUSEBUTTONUP)
				{
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						SDL_GetMouseState(&mouseX, &mouseY);
						if (startScreen)
						{
							if (start2Button.getIfClicked(mouseX, mouseY))
							{
								haveFriends = true;
								startScreen = false;
							}

							if (startBButton.getIfClicked(mouseX, mouseY))
							{
								haveFriends = false;
								startScreen = false;
							}
						}
					}

					if (winScreen)
					{
						if (newGameButton.getIfClicked(mouseX, mouseY))
						{
							player1.points = 0;
							player2.points = 0;
							player1.setX(10);
							player1.setY(int(winh - 300));
							player2.setX(winw - 15);
							player2.setY(int(winh - 300));
							ball.setX(int(winw / 2));
							ball.setY(int((winh - 10) / 2));
							winScreen = false;
						}
					}
				}
			}
		
			accumulator -= timeStep;
		}

		// ball movement
		if (!startScreen && !winScreen)
		{
			if (up == false)
			{
				ball.setY(ball.getY() + 5);
				if (ball.getY() >= winh - 10)
				{
					up = true;
					Mix_PlayChannel(2, bounce, 0);
				}	
			}

			if (up == true)
			{
				ball.setY(ball.getY() - 5);
				if (ball.getY() <= 0)
				{
					up = false;
					Mix_PlayChannel(2, bounce, 0);
				}	
			}

			if (right == false)
			{
				ball.setX(ball.getX() + 5);
				if (ball.getY() >= player2.getY() && ball.getY() <= player2.getY() + 100 && ball.getX() == player2.getX() - 10)
				{
					Mix_PlayChannel(1, bounce, 0);
					right = true;
				}

				if (ball.getX() >= winw - 10)
				{
					player1.points += 1;
					Mix_PlayChannel(1, score, 0);
					right = true;
				}
			}

			if (right == true)
			{
				ball.setX(ball.getX() - 5);
				if (ball.getY() >= player1.getY() && ball.getY() <= player1.getY() + 100 && ball.getX() == player1.getX() + 5)
				{	
					Mix_PlayChannel(1, bounce, 0);
					right = false;
				}

				if (ball.getX() <= 0)
				{
					player2.points += 1;
					Mix_PlayChannel(1, score, 0);
					right = false;
				}
			}
		}

		// If you have no friends movement
		if (!startScreen && !winScreen && !haveFriends)
			{
				if (!up)
					player2.setY(ball.getY() - 50);
				
				else if (up)
					player2.setY(ball.getY() - 50);
			}


		if (player1.points == 10 || player2.points == 10)
			winScreen = true;

		const char* p1score = std::to_string(player1.points).c_str();
		const char* p2score = std::to_string(player2.points).c_str();

		player1score.setText(p1score);
		player2score.setText(p2score);

		window.clear();

		if (startScreen)
		{
			window.renderText(startText);
			window.renderButton(start2Button);
			window.renderButton(startBButton);
		}

		if (!startScreen && !winScreen) 
		{
			window.render(player1);
			window.render(player2);
			window.render(ball);
			window.render(line);

			window.renderText(player1score);
			window.renderText(player2score);
		}

		if (winScreen)
		{
			if (player1.points == 10)
				winPlayer.setText("Player 1 Wins");

			else
				winPlayer.setText("Player 2 Wins");

			window.renderText(winPlayer);
			window.renderButton(newGameButton);
		} 

		window.display();

		int frameTicks = SDL_GetTicks() - startTicks;

		if (frameTicks < 1000 / window.getRefreshRate() )
			SDL_Delay(1000 / window.getRefreshRate() - frameTicks); 
	}

	window.cleanUp();

	Mix_FreeChunk(bounce);
	Mix_FreeChunk(score);

	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();

	return 0;
}