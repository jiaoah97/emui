#include <SDL2/SDL.h>
#include <stdio.h>
#include "emui.h"

#define SIZE 640 * 480 * sizeof(uint32_t)

int main()
{
	int quit = 0;
	SDL_Event e;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *win	= SDL_CreateWindow("emui", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
					   640,	480, 0);
	SDL_Renderer *r	= SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	SDL_Texture *tex = SDL_CreateTexture(r,	SDL_PIXELFORMAT_RGB888,	SDL_TEXTUREACCESS_STATIC,
					     640, 480);

	uint8_t *pixels = malloc(SIZE);

	em_ui_t ui;
	ui.width = 640;
	ui.height = 480;
	ui.buffer = pixels;
	ui.pixel_format = EM_RGB32;

	while (!quit)
	{
		SDL_WaitEvent(&e);

		switch (e.type)
		{
		case SDL_QUIT:
			quit = 1;
			break;
		}

		em_rect(&ui, 20, 20, 300, 440, (em_color_t){ 100, 255, 255 });
		em_drawstring(&ui, 40, 40, "Hello!", (em_color_t){ 0, 0, 0 });

		SDL_UpdateTexture(tex, NULL, pixels, 640 * sizeof(uint32_t));
		SDL_RenderClear(r);
		SDL_RenderCopy(r, tex, NULL, NULL);
		SDL_RenderPresent(r);
	}

	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(r);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
