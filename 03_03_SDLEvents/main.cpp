
// SDL
#include <SDL3/SDL.h>

// standard
#include <iostream>
#include <sstream>
#include <array>

int main(int argc, char* args[])
{
	//
	// Step 1: initialize SDL
	//

	// configure SDL's logging
	SDL_SetLogPriority(SDL_LOG_CATEGORY_ERROR, SDL_LOG_PRIORITY_ERROR);

	// initialize only the graphical subsystem, on failure log it and exit
	if ( !SDL_Init(SDL_INIT_VIDEO) )
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
	win = SDL_CreateWindow( "Hello SDL!",	// window title
							WindowW,		// window width
							WindowH,		// window height
							0);				// display properties


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
	ren = SDL_CreateRenderer( win,		 // for which window we are creating the renderer
							  nullptr );

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

	bool quit = false;	// should the program exit?

	float mouseX = 0, mouseY = 0; // the mouse cursor's X and Y coordinates

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
				if (ev.key.key == SDLK_ESCAPE) quit = true;
				break;
			case SDL_EVENT_MOUSE_MOTION:
				mouseX = ev.motion.x;
				mouseY = ev.motion.y;
				break;
			case SDL_EVENT_MOUSE_BUTTON_UP:
				// event of mouse button release; the released button is found in ev.button.button
				// possible buttons: SDL_BUTTON_LEFT, SDL_BUTTON_MIDDLE, SDL_BUTTON_RIGHT
				break;
			}
		}



		// clear the background with white
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		SDL_RenderClear(ren);

		// set the current drawing color to green and draw a line
		SDL_SetRenderDrawColor(ren,	// which renderer we are setting the current drawing color
			0,		// R -  red
			255,	// G -  green
			0,		// B -  blue
			255);	// A -  transparency

		SDL_RenderLine(ren,	// which renderer we are using to draw
			0.0f, 0.0f,			// (x,y) coordinates of the start point
			mouseX, mouseY);	// (x,y) coordinates of the end point

		// define a 20x20 square centered at (mouseX, mouseY) with sides parallel to the axes:
		SDL_FRect cursor_rect;
		cursor_rect.x = mouseX - 10.0f;
		cursor_rect.y = mouseY - 10.0f;
		cursor_rect.w = 20.0f;
		cursor_rect.h = 20.0f;

		// set the fill color to red
		SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		SDL_RenderFillRect(ren, &cursor_rect);

		// Task 1: Periodically increase and decrease, according to the elapsed time, the size of the square,
		//         which was drawn from the centroid given by the mouse cursor's position

		// Task 2: If the user presses the left mouse button, set the square's color to red.
		//         If the right mouse button was pressed, set it to blue

		// Task 3 (can be handed in): Draw a circle around the mouse cursor with 50 radius
		// Hint: Use SDL_RenderLines()

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