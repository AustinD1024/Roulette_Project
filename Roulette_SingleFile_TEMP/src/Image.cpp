#include "image.h"

#include <SDL.h>   

#include <atomic>

extern std::atomic<bool> quit;

void Image(int argc, char** argv)
{
	//bool quit = false;
	SDL_Event event;

	SDL_Init( SDL_INIT_VIDEO );

	SDL_Window* window = SDL_CreateWindow( "SDL2 Displaying Image", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 1000, 0 );

	SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, 0 );
	//SDL_Surface* image = SDL_LoadBMP( "../resources/Roulette_Wheel_Image.bmp" );  //this depends on where you run the binary file
	SDL_Surface* image = SDL_LoadBMP("Roulette_Wheel_Image.bmp");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);

	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;
			default:
				break;
			}
		}

		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent( renderer );
	}


	SDL_DestroyTexture( texture );
	SDL_FreeSurface( image );
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow(window);

	SDL_Quit();

}



