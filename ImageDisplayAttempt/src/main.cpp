#include <SDL.h>        

// Global variables to store command-line arguments
int global_argc;
char** global_argv;



int main(int argc, char** argv)
{
	bool quit = false;
	SDL_Event event;

	SDL_Init( SDL_INIT_VIDEO );

	SDL_Window* window = SDL_CreateWindow( "SDL2 Displaying Image", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 400, 0 );

	SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, 0 );
	SDL_Surface* image = SDL_LoadBMP( "../resources/NittanyLion.bmp" );  //this depends on where you run the binary file...Do I have to do this??? Why can't it 
	SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, image );

	while ( !quit )
	{
		SDL_WaitEvent( &event );

		switch ( event.type )
		{
			case SDL_QUIT:
			quit = true;
			break;
		}

		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent( renderer );
	}

	SDL_DestroyTexture( texture );
	SDL_FreeSurface( image );
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );

	SDL_Quit();

	return 0;
}

