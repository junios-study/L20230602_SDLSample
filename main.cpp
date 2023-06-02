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

	SDL_Surface*  MyBG;
	MyBG = SDL_LoadBMP("data/_Map.bmp");
	SDL_Texture* MyBGTexture = SDL_CreateTextureFromSurface(MyRenderer, MyBG);

	//Loading
	SDL_Surface* MySurface[3];
	SDL_Texture* MyTexture[3];

	for (int i = 0; i < 3; ++i)
	{
		char Buffer[1024] = { 0, };
		sprintf_s(Buffer, "data/Stand_L_0%d.bmp", (i + 1));
		MySurface[i] = SDL_LoadBMP(Buffer);
		SDL_SetColorKey(MySurface[i], 1, SDL_MapRGB(MySurface[i]->format, 255, 255, 255));
		MyTexture[i] = SDL_CreateTextureFromSurface(MyRenderer, MySurface[i]);
	}
	//SDL_FreeSurface(MySurface);
	int Index = 0;
	int Frame = 0;

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
			case SDLK_ESCAPE:
				bIsRunning = false;
				break;
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

		SDL_RenderCopy(MyRenderer, MyBGTexture, nullptr, nullptr);

		SDL_Rect MyRect = { X, Y, MySurface[Index]->w, MySurface[Index]->h};
		//SDL_SetRenderDrawColor(MyRenderer, 207, 255, 229, 0);
		//SDL_RenderFillRect(MyRenderer, &MyRect);
		SDL_RenderCopy(MyRenderer, MyTexture[Index], nullptr, &MyRect);

		SDL_RenderPresent(MyRenderer);

		if (Frame >= 59)
		{
			Index++;
			Index = Index % 3;
			Frame = Frame % 60;
		}
		Frame++;
	}

	SDL_Quit();

	return 0;
}