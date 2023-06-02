#include <iostream>
#include "SDL.h"

#pragma comment(lib, "SDL2")
#pragma comment(lib, "SDL2main")

int SDL_main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* MyWindow = SDL_CreateWindow("FirstWindow", 100, 100, 640, 480, SDL_WINDOW_OPENGL);
	SDL_Renderer* MyRenderer = SDL_CreateRenderer(MyWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	SDL_Event MyEvent;
	bool bIsRunning = true;
	int X = 100;
	int Y = 100;
	while (bIsRunning)
	{
		//Input
		SDL_PollEvent(&MyEvent);
		//Tick
		switch (MyEvent.type)
		{
		case SDL_QUIT:
			bIsRunning = false;
			break;
		case SDL_KEYDOWN:
			switch (MyEvent.key.keysym.sym)
			{
			case SDLK_a:
				X-=5;
				break;
			case SDLK_d:
				X += 5;
				break;
			case SDLK_w:
				Y -= 5;
				break;
			case SDLK_s:
				Y += 5;
				break;
			}
		}
		
		//Render
		SDL_SetRenderDrawColor(MyRenderer, 0, 0, 0, 0);
		SDL_RenderClear(MyRenderer);

		SDL_Rect MyRect = { X, Y, 100, 100 };
		SDL_SetRenderDrawColor(MyRenderer, 207, 255, 229, 0);
		//SDL_RenderDrawFillRect(MyRenderer, &MyRect);
		SDL_RenderFillRect(MyRenderer, &MyRect);

		SDL_RenderPresent(MyRenderer);
	}

	SDL_Quit();

	return 0;
}