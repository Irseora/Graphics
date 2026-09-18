
// SDL
#include <SDL3/SDL.h>

// standard
#include <iostream>
#include <sstream>

#include <cmath>
#include <vector>

using namespace std;

void drawPolygon(float r, float offsetx, float offsety, int sides, SDL_Renderer *ren)
{
	vector<float> xs;
	vector<float> ys;

	float step = (3.141592 * 2.0) / sides;

	for (size_t i = 0; i < sides; i++)
	{
		float alpha = i * step;
		float x = cos(alpha) * r + offsetx;
		float y = sin(alpha) * r + offsety;

		xs.push_back(x);
		ys.push_back(y);
	}

	xs.push_back(cos(0) * r + offsetx);
	ys.push_back(sin(0) * r + offsety);

	for (size_t i = 0; i < xs.size() - 1; i++)
	{
		float x1 = xs[i];
		float y1 = ys[i];

		float x2 = xs[i + 1];
		float y2 = ys[i + 1];

		SDL_RenderLine(ren, x1, y1, x2, y2);
	}
}

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

	SDL_Window *win = nullptr;
	win = SDL_CreateWindow("Hello SDL!", // window title
						   1280,		 // window width
						   720,			 // window height
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
	// Step 4: rendering/drawing
	//

	// Clear the window background, draw a line, and wait for 2 seconds

	// set black drawing color, clear the window's client area with the current drawing color
	SDL_SetRenderDrawColor(ren,	 // which renderer we are setting the current drawing color
						   0,	 // R -  red intensity
						   0,	 // G -  green intensity
						   0,	 // B -  blue intensity
						   255); // A -  transparency

	SDL_RenderClear(ren);

	// // set the current drawing color to green and draw a line
	// SDL_SetRenderDrawColor(ren,	 // which renderer we are setting the current drawing color
	// 					   0,	 // R -  red
	// 					   255,	 // G -  green
	// 					   0,	 // B -  blue
	// 					   255); // A -  transparency

	// SDL_RenderLine(ren,			 // which renderer we are using to draw
	// 			   10.0f, 10.f,	 // (x,y) coordinates of the start point
	// 			   10.0f, 60.f); // (x,y) coordinates of the end point

	// // display the back buffer
	// SDL_RenderPresent(ren);

	// // wait for 2 seconds
	// SDL_Delay(2000);

	// SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	// drawPolygon(100, 150, 150, 32, ren);
	// drawPolygon(100, 1000, 150, 32, ren);
	// drawPolygon(100, 150, 500, 32, ren);
	// drawPolygon(100, 1000, 500, 32, ren);

	// SDL_RenderPresent(ren);
	// SDL_Delay(2000);

	float centerx = 1280 / 2.0;
	float centery = 720 / 2.0;

	for (size_t i = 0; i < 100; i++)
	{
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		SDL_RenderClear(ren);

		float xoffset = cos(i / 5.0) * 50;

		SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
		drawPolygon(50, centerx + xoffset, centery, 12, ren);

		SDL_RenderPresent(ren);
		SDL_Delay(16);
	}

	// SDL_Delay(2000);

	//
	// Step 5: exit
	//

	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);

	return 0;
}