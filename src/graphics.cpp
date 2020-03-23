#include "graphics.h"

void setupGraphics(engineData *engData){
    engData->windowWidth = 640;
    engData->windowHeight = 480;

    //Start up SDL and make sure it went ok
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		logError("Failed SDL_Init");
	}

	//Setup our window and renderer
	engData->window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, engData->windowWidth, engData->windowHeight, SDL_WINDOW_SHOWN);
	if (engData->window == NULL) {
		logError("Failed SDL_CreateWindow");
		SDL_Quit();
	}
	SDL_UpdateWindowSurface(engData->window);
	engData->renderer = SDL_CreateRenderer(engData->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (engData->renderer == NULL) {
		logError("Failed SDL_CreateRenderer");
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

void refreshGraphicsSettings(engineData *engData){
	SDL_SetWindowSize(engData->window, engData->windowWidth, engData->windowHeight);
}

void drawRect(engineData *engData, double x, double y, double width, double height, int drwColor[4]){
	SDL_SetRenderDrawColor(engData->renderer, drwColor[0], drwColor[1], drwColor[2], drwColor[3]);
	SDL_Rect tile;
	tile.x = x;
	tile.y = y;
	tile.w = width;
	tile.h = height;
	SDL_RenderFillRect(engData->renderer, &tile);
}

void drawText(std::string text, engineData *engData, double x, double y, int width, int height){
	/*x = x * engData->windowWidth;
	y = y * engData->windowHeight;
	int char_w = 0;
	int x_offset = 0;
	drawRect(engData, x, y, width, height, engData->defaultGuiBkgColor);
	SDL_QueryTexture(char_texture_map['A'], NULL, NULL, &char_w, NULL);
	for(char ch : text){
		renderTexture(char_texture_map[ch], engData->renderer, x + x_offset, 0);
		x_offset += char_w;
	}*/
}