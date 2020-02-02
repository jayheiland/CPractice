#include "graphics.h"

void setupGraphics(engineData *engData){
    engData->windowWidth = 640;
    engData->windowHeight = 480;

    //Start up SDL and make sure it went ok
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		logError("setupGraphics", "Failed SDL_Init");
	}

	//Setup our window and renderer
	engData->window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, engData->windowWidth, engData->windowHeight, SDL_WINDOW_SHOWN);
	if (engData->window == NULL) {
		logError("setupGraphics", "Failed SDL_CreateWindow");
		SDL_Quit();
	}
	SDL_UpdateWindowSurface(engData->window);
	engData->renderer = SDL_CreateRenderer(engData->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (engData->renderer == NULL) {
		logError("setupGraphics", "Failed SDL_CreateRenderer");
		SDL_DestroyWindow(engData->window);
		SDL_Quit();
	}
}

void drawGraphics(engineData *engData, worldData *wData){
    SDL_SetRenderDrawColor(engData->renderer, 0, 0, 0, 255);
    SDL_RenderClear(engData->renderer);

    //draw everything

    SDL_RenderPresent(engData->renderer);
}

void shutdownGraphics(engineData *engData){
    SDL_DestroyRenderer(engData->renderer);
    SDL_DestroyWindow(engData->window);
}