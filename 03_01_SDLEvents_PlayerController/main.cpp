
// SDL
#include <SDL3/SDL.h>

// standard
#include <iostream>
#include <sstream>
#include <array>
#include <cmath>

int main(int argc, char *args[])
{
	//
	// Step 1: initialize SDL
	//

	// configure SDL's logging
	SDL_SetLogPriority(SDL_LOG_CATEGORY_ERROR, SDL_LOG_PRIORITY_ERROR);

	// initialize only the graphical subsystem, on failure log it and exit
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		// log the error and terminate the program
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "[SDL initialization] Error during the SDL initialization: %s", SDL_GetError());
		return 1;
	}

	// After SDL Init runs, the subsystems should be shut down on exit
	// This way, it will run even if we exit due to some error
	std::atexit(SDL_Quit);

	//
	// Step 2: create a window
	//

	const int WindowW = 1280, WindowH = 720;
	SDL_Window *win = nullptr;
	win = SDL_CreateWindow("Hello SDL!", // window title
						   WindowW,		 // window width
						   WindowH,		 // window height
						   0);			 // display properties

	// if the window creation failed, log the error and exit
	if (win == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "[Window creation] Error during the SDL initialization: %s", SDL_GetError());
		return 1;
	}

	//
	// Step 3: create a renderer
	//

	SDL_Renderer *ren = nullptr;
	ren = SDL_CreateRenderer(win, // for which window we are creating the renderer
							 nullptr);

	if (ren == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "[Renderer creation] Error during the creation of an SDL renderer: %s", SDL_GetError());
		SDL_DestroyWindow(win);
		return 1;
	}

	// Turn on v-sync
	SDL_SetRenderVSync(ren, 1);

	//
	// step 4: start the main event handler loop
	//

	bool quit = false; // should the program exit?

	float mouseX = 0, mouseY = 0; // the mouse cursor's X and Y coordinates

	float heroX = WindowW / 2.0f;
	float heroY = WindowH / 2.0f;
	float heroSpeed = 300.0;
	float heroVertical = 0.0f;
	float heroHorizontal = 0.0f;

	float oldTime = 0;

	while (!quit)
	{
		// the event to be processed goes here
		SDL_Event ev;
		// while there are still events to be processed, keep processing them:
		while (SDL_PollEvent(&ev))
		{
			switch (ev.type)
			{
			case SDL_EVENT_QUIT:
				quit = true;
				break;
			case SDL_EVENT_KEY_DOWN:
				if (ev.key.key == SDLK_ESCAPE)
					quit = true;

				if (!ev.key.repeat) // otherwise waits before moving
				{
					if (ev.key.key == SDLK_W)
						heroVertical = -1.0f;

					if (ev.key.key == SDLK_S)
						heroVertical = 1.0f;

					if (ev.key.key == SDLK_A)
						heroHorizontal = -1.0f;

					if (ev.key.key == SDLK_D)
						heroHorizontal = 1.0f;
				}

				break;
			case SDL_EVENT_KEY_UP:
				if (ev.key.key == SDLK_W)
					heroVertical = 0.0f;
				if (ev.key.key == SDLK_S)
					heroVertical = 0.0f;
				if (ev.key.key == SDLK_A)
					heroHorizontal = 0.0f;
				if (ev.key.key == SDLK_D)
					heroHorizontal = 0.0f;
				if (ev.key.key == SDLK_R)
				{
					heroX = WindowW / 2.0f;
					heroY = WindowH / 2.0f;
				}

				break;
			case SDL_EVENT_MOUSE_MOTION:
				mouseX = ev.motion.x;
				mouseY = ev.motion.y;
				break;
			}
		}

		float time = SDL_GetTicks() / 1000.0f;
		float deltaTime = time - oldTime; // how much time passed since last frame
		oldTime = time;

		heroY += deltaTime * heroVertical * heroSpeed;
		heroX += deltaTime * heroHorizontal * heroSpeed;

		// SDL_Delay(32);	// fake lag

		float heroRed = (sin(time * 10) + 1.0) / 2.0 * 255.0;

		// mod(x,5) / 5 * 255
		float bgRed = fmodf(time, 2) / 2.0 * 255.0;

		// clear the background with white
		SDL_SetRenderDrawColor(ren, bgRed, 255, 255, 255);
		SDL_RenderClear(ren);

		SDL_FRect heroBox;
		heroBox.h = 50;
		heroBox.w = 50;
		heroBox.x = heroX - heroBox.w / 2;
		heroBox.y = heroY - heroBox.h / 2;

		SDL_SetRenderDrawColor(ren, heroRed, 0, 255, 255);
		SDL_RenderFillRect(ren, &heroBox);

		// display the back buffer
		SDL_RenderPresent(ren);
	}

	//
	// Step 5: exit
	//

	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);

	return 0;
}